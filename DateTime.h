#pragma once
#include <string>
#include <fstream>

// Структура даты и времени
struct DateTime {
	int32_t day, month, year;
	int32_t hour, minute;
};

// Считывание DateTime из строки
bool DateTimeFromStr(std::string str, DateTime &date);

// Преобразование DateTime в строку
std::string DateTimeToStr(const DateTime &d);

// Вывод DateTime в консоль
void DateTimeToConsole(const DateTime &date);

// Сравнение DateTime
int CompareDateTime(const DateTime &d1, const DateTime &d2);

// Считывание DateTime из бинарного файла
bool DateTimeFromBin(DateTime &d, std::fstream *f);

// Запись DateTime в бинарный файл
void DateTimeToBin(const DateTime &d, std::fstream *f);