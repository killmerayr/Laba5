#include <iostream>
#include <map>
#include "commands.hpp"

using namespace std;

// Главная функция для работы с регионами и административными центрами
int main() {
    map<string, string> regions;

    while (true) {
        string command = "NONE";
        cout << "Введите команду (CHANGE, RENAME, ABOUT, ALL, EXIT): ";
        cin >> command;

        if (command == "CHANGE") {
            string region = "NONE";
            string newCenter = "NONE";

            cin >> region >> newCenter;
            CHANGE(region, newCenter, regions);
        } else if (command == "RENAME") {
            string old_region = "NONE";
            string new_region = "NONE";

            cin >> old_region >> new_region;
            RENAME(old_region, new_region, regions);
        } else if (command == "ABOUT") {
            string region = "NONE";
            
            cin >> region;
            ABOUT(region, regions);
        } else if (command == "ALL") {
            ALL(regions);
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Некорректная команда. Попробуйте еще раз." << endl;
        }
    }
}