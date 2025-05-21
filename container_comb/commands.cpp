#include <iostream>
#include <map>
#include "commands.hpp"

using namespace std;

// Изменение административного центра региона
void CHANGE(string region, string newCenter, map<string, string>& regions) {
    // Проверка: нет ли уже такого административного центра у другого региона
    for (const auto& [reg, center] : regions) {
        if (center == newCenter && reg != region) {
            cerr << "Incorrect" << endl;
            return;
        }
    }

    auto it = regions.find(region);
    if (it != regions.end()) {
        cout << "Переименование названия административного (" << regions[region] << ") центра региона " << region << " в " << newCenter << endl;
    } else {
        cout << "Создание региона " << region << " с административным центром " << newCenter << endl;
    }
    regions[region] = newCenter;
}

// Переименование региона
void RENAME(string old_region, string new_region, map<string, string>& regions) {
    if (old_region == new_region){
        cerr << "Incorrect" << endl;
        return;
    }
    auto it = regions.find(old_region);
    if (it != regions.end()) {
        // Проверка: нет ли уже такого административного центра у другого региона
        string center = regions[old_region];
        for (const auto& [reg, cent] : regions) {
            if (reg != old_region && cent == center) {
                cerr << "Incorrect" << endl;
                return;
            }
        }

        cout << "Переименование региона со старым названием " << old_region << " в регион с новым названием " << new_region << endl;
        regions[new_region] = regions[old_region];
        regions.erase(old_region);
    } else {
        cerr << "Incorrect" << endl;
    }
}

// Информация о регионе
void ABOUT(string region, map<string, string>& regions) {
    auto it = regions.find(region);
    if (it != regions.end()) {
        cout << "Регион " << region << " имеет административный центр " << regions[region] << endl;
    } else {
        cerr << "Incorrect" << endl;
    }
}

// Вывод всех регионов и их административных центров
void ALL(map<string, string>& regions) {
    for (const auto& region : regions) {
        cout << "Регион: " << region.first << ", Административный центр: " << region.second << endl;
    }
    cout << endl;
}