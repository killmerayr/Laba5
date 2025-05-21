#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

// Структура для хранения информации о посетителе
struct Visitor {
    string ticket;
    int duration;
};

// Функция для генерации номера талона
string generateTicket() {
    static int counter = 0;
    counter++;
    // Генерируем номер в формате TXXX
    int num = 100 + rand() % 900;
    return "T" + to_string(num);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout << ">>> Введите количество окон" << endl;
    int window_count;
    cout << "<<< ";
    cin >> window_count;

    vector<Visitor> visitors; // очередь посетителей

    string command;
    while (cin >> command) {
        if (command == "ENQUEUE") {
            int duration;
            cin >> duration;
            string ticket = generateTicket();
            visitors.push_back({ticket, duration});
            cout << ">>> " << ticket << endl;
        }
        else if (command == "DISTRIBUTE") {
            // для каждого окна храним суммарное время и список талонов
            vector<int> window_time(window_count, 0);
            vector<vector<string>> window_tickets(window_count);

            // Сортируем посетителей по убыванию времени
            vector<Visitor> sorted_visitors = visitors;
            sort(sorted_visitors.begin(), sorted_visitors.end(), [](const Visitor& a, const Visitor& b){
                return a.duration > b.duration;
            });

            // Распределяем посетителей по окнам (каждого к окну с минимальной текущей загрузкой)
            for (const auto& v : sorted_visitors) {
                // Найти окно с минимальным временем
                auto min_it = min_element(window_time.begin(), window_time.end());
                size_t min_idx = distance(window_time.begin(), min_it);
                window_time[min_idx] += v.duration;
                window_tickets[min_idx].push_back(v.ticket);
            }

            // Выводим результат
            auto printDistribution = [](const vector<vector<string>>& window_tickets, const vector<int>& window_time) {
                int idx = 1;
                for (const auto& tickets : window_tickets) {
                    cout << ">>> Окно " << idx << " (" << window_time[idx - 1] << " минут): ";
                    bool first = true;
                    for (const auto& ticket : tickets) {
                        if (!first) cout << ", ";
                        cout << ticket;
                        first = false;
                    }
                    cout << endl;
                    ++idx;
                }
            };
            printDistribution(window_tickets, window_time);
            // Завершаем после распределения
            break;
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда" << endl;
            continue;
        }
    }
    return 0;
}
