#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// Глобальные переменные для склада
map<string, map<string, int>> warehouse; // Склад: адрес -> (товар -> количество)
vector<int> racks = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Стеллажи
vector<int> sections = {1, 2, 3, 4, 5, 6, 7}; // Секции
vector<int> shelves = {1, 2, 3, 4}; // Полки
const int MAX_IN_CELL= 10; // Максимум в ячейке

// Инициализация склада (создание всех ячеек)
void initWarehouse() {
    string zone = "A"; // Одна зона

    for (const auto& r : racks) {
        for (const auto& s : sections) {
            for (const auto& sh : shelves) {
                // Формируем адрес: A + номер стеллажа (2 цифры) + секция + полка
                string address = zone + 
                    (r < 10 ? "0" + to_string(r) : to_string(r)) + 
                    to_string(s) + 
                    to_string(sh);

                warehouse[address] = {}; // Инициализируем пустую ячейку
            }
        }
    }
}

// Добавление товара в ячейку склада
void addItem(const string& item, const string& address, int count){
    if(warehouse.find(address) == warehouse.end()){
        cout << "Ячейка" << address << "не найдена" << endl;
        return;
    }

    int total = 0;
    for(const auto& [name, quant] : warehouse[address]){
        total += quant;
    }

    if(total + count > MAX_IN_CELL){
        cout << "Нет места в ячейке" << address << endl;
        return;
    }

    warehouse[address][item] += count;
    cout << "Добавлен " << item << " в ячейку " << address << endl;
}

// Удаление товара из ячейки склада
void removeItem(const string& item, const string& address, int count){
    if(warehouse.find(address) == warehouse.end()){
        cout << "Ячейка " << address << " не найдена" << endl;
        return;
    }

    auto& cell = warehouse[address];
    if(cell.find(item) == cell.end()){
        cout << "Товар " << item << " не найден" << endl;
        return;
    }

    if (count <= cell[item]){
        cell[item] -= count;
        if(cell[item] == 0){
            cell.erase(item);
        }
        cout << "Товар " << item << " удален из ячейки " << address << " в количестве "
             << count << endl;
    } else {
        cout << "Число " << count << " больше, чем количество " << item << endl;
    }
}

// Информация о складе: загрузка, зоны, содержимое и пустые ячейки
void info(){
    int total_cells = warehouse.size();
    int total_capacity = total_cells * MAX_IN_CELL;
    int total_items = 0;
    map<string, int> zone_items;
    map<string, int> zone_cells;

    vector<string> empty_cells;

    for (const auto& [address, cell] : warehouse) {
        string zone = address.substr(0, 1);
        int cell_sum = 0;
        for (const auto& [item, count] : cell) {
            cell_sum += count;
        }
        total_items += cell_sum;
        zone_items[zone] += cell_sum;
        zone_cells[zone]++;

        if (cell_sum == 0) {
            empty_cells.push_back(address);
        } else {
            cout << "Ячейка " << address << ": ";
            for (const auto& [item, count] : cell) {
                cout << item << " (" << count << ") ";
            }
            cout << endl;
        }
    }

    if (total_capacity == 0) {
        cout << "Склад пуст, загрузка: 0%" << endl;
    } else {
        double warehouse_load = (100.0 * total_items / total_capacity);
        cout << fixed << setprecision(2);
        cout << "Загрузка склада: " << warehouse_load << "%" << endl;

        for (const auto& [zone, items] : zone_items) {
            int zone_capacity = zone_cells[zone] * MAX_IN_CELL;
            double zone_load = (zone_capacity == 0) ? 0 : (100.0 * items / zone_capacity);
            cout << "Загрузка зоны " << zone << ": " << zone_load << "%" << endl;
        }
    }

    cout << "Пустые ячейки:" << endl;
    for (const auto& addr : empty_cells) {
        cout << addr << " ";
    }
    cout << endl;
}

// Главная функция: меню пользователя
int main() {
    srand(static_cast<unsigned int>(time(0)));
    initWarehouse();

    vector<string> items = {"Молоко", "Хлеб", "Яблоко", "Сыр", "Мясо", "Банан", "Яблоко"};

    // Рандомно заполняем склад (range-based for)
    for (const auto& [address, _] : warehouse) {
        if (rand() % 2 == 0) continue; // Пропускаем часть ячеек для пустых
        string item = items[rand() % items.size()];
        int count = 1 + rand() % MAX_IN_CELL;
        addItem(item, address, count);
    }

    // Меню пользователя
    while (true) {
        cout << "\nВыберите действие: ADD, REMOVE, INFO, EXIT\n> ";
        string command;
        cin >> command;

        if (command == "ADD") {
            string item, address;
            int count;
            cout << "Введите товар, адрес и количество: ";
            cin >> item >> address >> count;
            addItem(item, address, count);
        } else if (command == "REMOVE") {
            string item, address;
            int count;
            cout << "Введите товар, адрес и количество: ";
            cin >> item >> address >> count;
            removeItem(item, address, count);
        } else if (command == "INFO") {
            info();
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Неизвестная команда!" << endl;
            continue;
        }
    }

    return 0;
}