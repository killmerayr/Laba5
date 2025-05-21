#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
#include "commands.hpp"

using namespace std;

TR StringToTR(const string& str){
    static const unordered_map<string, TR> tr_map = {
        {"CREATE_TRAM", TR::CREATE_TRAM},
        {"TRAM_IN_STOP", TR::TRAM_IN_STOP},
        {"STOPS_IN_TRAM", TR::STOPS_IN_TRAM},
        {"TRAMS", TR::TRAMS}
    };

    for (const auto& [key, value] : tr_map){
        if (key == str){
            return value;
        }
    }
    return TR::UNKNOWN_COMMAND;
}

// Пропуск команды и ключевого слова
vector<string> ParseWords(const string& str, size_t skip) {
    istringstream ss(str);
    vector<string> words;
    string word;
    size_t count = 0;
    while(ss >> word){
        if (count >= skip){
            words.push_back(word);
        }
        count ++;
    }
    return words;
}

void CREATE_TRAM(const string& input, map<string, vector<string>>& stops_in_tram, map<string, vector<string>>& tram_in_stops){
    vector<string> all_words = ParseWords(input, 0);

    if (all_words.size() < 2){
        cout << "Недостаточно аргументов" << endl;
        return;
    }

    string tram = all_words[1];
    vector<string> stops = ParseWords(input, 2);

    // Запрещаем пересоздание трамвая с тем же именем
    if (tram_in_stops.count(tram) && !tram_in_stops[tram].empty()) {
        cout << "Трамвай " << tram << " уже существует, пересоздать нельзя" << endl;
        return;
    }

    // Теперь требуется минимум две остановки
    if (stops.size() < 2){
        cout << "Недостаточно кол-ва остановок" << endl;
        return;
    }

    // Проверка на дубликаты остановок внутри маршрута
    set<string> unique_stops(stops.begin(), stops.end());
    if (unique_stops.size() != stops.size()) {
        cout << "одинаковые остановки с " << tram << ", невозможно создать" << endl;
        return;
    }

    // Проверка: есть ли другой трамвай с двумя и более совпадающими остановками
    // for (const auto& [other_tram, other_stops] : tram_in_stops) {
    //     if (other_tram == tram) continue;
    //     int common = 0;
    //     for (const auto& stop : stops) {
    //         if (find(other_stops.begin(), other_stops.end(), stop) != other_stops.end()) {
    //             ++common;
    //             if (common >= 2) {
    //                 cout << "Маршрут " << tram << " совпадает по двум и более остановкам с " << other_tram << ", невозможно создать" << endl;
    //                 return;
    //             }
    //         }
    //     }
    // }

    tram_in_stops[tram].clear(); // Очистка старых остановок этого трамвая

    // Добавление остановок (игнорируем одинаковые элементы)
    for (const auto& stop : stops){
        if (count(tram_in_stops[tram].begin(), tram_in_stops[tram].end(), stop) == 0) {
            tram_in_stops[tram].push_back(stop); // Остановки к трамваю
        }
        if (count(stops_in_tram[stop].begin(), stops_in_tram[stop].end(), tram) == 0) {
            stops_in_tram[stop].push_back(tram); // Трамваи к остановкам
        }
    }
}

void STOPS_IN_TRAM(const string& input, const map<string, vector<string>>& tram_in_stops, const map<string, vector<string>>& stops_in_tram) {
    vector<string> all_words = ParseWords(input);
    if (all_words.size() < 2) {
        cout << "Недостаточно аргументов" << endl;
        return;
    }

    string tram = all_words[1];

    auto it = tram_in_stops.find(tram);
    if (it == tram_in_stops.end()) {
        cout << "Трамвай " << tram << " не найден" << endl;
        return;
    }

    const vector<string>& stops = it->second;

    for (const auto& stop : stops) {
        cout << "Остановка " << stop << ": ";
        bool found_other = false;
        auto sit = stops_in_tram.find(stop);
        if (sit != stops_in_tram.end()) {
            for (const auto& other_tram : sit->second) {
                if (other_tram != tram) {
                    cout << other_tram << " ";
                    found_other = true;
                }
            }
        }
        if (!found_other) {
            cout << "Нет других трамваев";
        }
        cout << endl;
    }
}

void TRAM_IN_STOP(const string& input, const map<string, vector<string>>& stops_in_tram){
    vector<string> all_words = ParseWords(input);

    if (all_words.size() < 2){
        cout << "Недостаточно аргументов" << endl;
        return;
    }

    string stop = all_words[1];

    auto it = stops_in_tram.find(stop);
    if (it == stops_in_tram.end()){
        cout << "TRAM is absent";
        return;
    }
    else {
        cout << "TRAM_IN_STOP " << stop << " : ";
        const vector<string>& trams = it->second;
        for (const auto& tram : trams){
            cout << tram << endl;
        }
        cout << endl;
    }
}

void TRAMS(const map<string, vector<string>>& tram_in_stops) {
    if (tram_in_stops.empty()) {
        cout << "Нет трамваев" << endl;
        return;
    }
    for (const auto& [tram, stops] : tram_in_stops) {
        cout << "Трамвай " << tram << ": ";
        if (stops.empty()) {
            cout << "нет остановок";
        } else {
            for (const auto& stop : stops) {
                cout << stop << " ";
            }
        }
        cout << endl;
    }
}
