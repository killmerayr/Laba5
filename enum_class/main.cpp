#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "commands.hpp"

using namespace std;

// Главная функция для работы с трамваями и остановками
int main() {
    map<string, vector<string>> stops_in_tram; // остановка -> список трамваев
    map<string, vector<string>> tram_in_stops; // трамвай -> список остановок

    string input;
    cout << "Введите команду (CREATE_TRAM, TRAM_IN_STOP, STOPS_IN_TRAM, TRAMS, EXIT):" << endl;
    while (getline(cin, input)) {
        if (input.empty()) continue;

        // Получаем команду (первое слово)
        string command_word = ParseWords(input, 0).empty() ? "" : ParseWords(input, 0)[0];
        if (command_word == "EXIT") break;

        TR command = StringToTR(command_word);

        switch (command) {
            case TR::CREATE_TRAM:
                CREATE_TRAM(input, stops_in_tram, tram_in_stops);
                break;
            case TR::TRAM_IN_STOP:
                TRAM_IN_STOP(input, stops_in_tram);
                break;
            case TR::STOPS_IN_TRAM:
                STOPS_IN_TRAM(input, tram_in_stops, stops_in_tram);
                break;
            case TR::TRAMS:
                TRAMS(tram_in_stops);
                break;
            default:
                cout << "Неизвестная команда!" << endl;
                break;
        }
        cout << "Введите команду (CREATE_TRAM, TRAM_IN_STOP, STOPS_IN_TRAM, TRAMS, EXIT):" << endl;
    }
    return 0;
}