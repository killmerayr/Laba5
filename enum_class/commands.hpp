#pragma once
#include <string>
#include <vector>
#include <map>

//Перечисление команд
enum class TR {
    CREATE_TRAM,
    TRAM_IN_STOP,
    STOPS_IN_TRAM,
    TRAMS,
    UNKNOWN_COMMAND
};

// Преобразование строки в команду
TR StringToTR(const std::string& str);

// Парсинг слов из строки (с пропуском skip первых слов)
std::vector<std::string> ParseWords(const std::string& str, size_t skip = 0);

// Создание трамвая и его маршрута
void CREATE_TRAM(const std::string& input, std::map<std::string, std::vector<std::string>>& stops_in_tram, std::map<std::string, std::vector<std::string>>& tram_in_stops);

// Вывод остановок трамвая и других трамваев на этих остановках
void STOPS_IN_TRAM(const std::string& input, const std::map<std::string, std::vector<std::string>>& tram_in_stops, const std::map<std::string, std::vector<std::string>>& stops_in_tram);

// Вывод трамваев, проходящих через остановку
void TRAM_IN_STOP(const std::string& input, const std::map<std::string, std::vector<std::string>>& stops_in_tram);

// Вывод всех трамваев и их маршрутов
void TRAMS(const std::map<std::string, std::vector<std::string>>& tram_in_stops);