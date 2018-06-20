#include <iostream>
#include <cstdlib>
#include <sstream>
#include "DateTime.h"

// Проверка на высокосный год
bool LeapYear(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

// Возвращает кол-во дней в месяце 
int CountDayInMonth(int month, int year) {
	switch (month)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		return LeapYear(year) ? 29 : 28;
	default:
		return 31;
	}
}

// Выделение числа из строкового представления DateTime
int GetNum(std::string str, int &num, char sym) {
	int p = str.find(sym, 0);
	if (p != -1) {
		const char *ch = str.c_str();
		num = atoi(ch);
		return p;
	}
	return -1;
}

// Преобразование строки в DateTime
bool DateTimeFromStr(std::string str, DateTime &date) {
	DateTime d;

	if (str == "") return false;

	int p = GetNum(str, d.day, '.');
	if (p != 1 && p != 2) return false;

	str = str.substr(p + 1);
	p = GetNum(str, d.month, '.');
	if (p != 1 && p != 2) return false;

	str = str.substr(p + 1);
	p = GetNum(str, d.year, ' ');
	if (p != 4) return false;

	str = str.substr(p + 1);
	p = GetNum(str, d.hour, ':');
	if (p != 1 && p != 2) return false;

	str = str.substr(p + 1) + ':';
	p = GetNum(str, d.minute, ':');
	if (p != 1 && p != 2) return false;

	if (d.month >= 1 && d.month <= 12 && d.year > 1900 &&
		d.day >= 1 && d.day <= CountDayInMonth(d.month, d.year) &&
		d.hour >= 0 && d.hour <= 23 && d.minute >= 0 && d.minute <= 59) {
		date = d;
		return true;
	}

	return false;
}

// Вывод DateTime в консоль
void DateTimeToConsole(const DateTime &date) {
	std::cout << DateTimeToStr(date);
}

// Преобразование DateTime в строку
std::string DateTimeToStr(const DateTime &d) {
	std::string res = "";

	if (d.day < 10) res += '0';
	res += std::to_string(d.day) + '.';

	if (d.month < 10) res += '0';
	res += std::to_string(d.month) + '.';

	res += std::to_string(d.year) + ' ';

	if (d.hour < 10) res += '0';
	res += std::to_string(d.hour) + ':';

	if (d.minute < 10) res += '0';
	res += std::to_string(d.minute);

	return res;
}

// Считывание DateTime из бинарного файла
bool DateTimeFromBin(DateTime &d, std::fstream *f) {
	return f->read(reinterpret_cast<char*>(&(d.day)), sizeof(d.day)) &&
		f->read(reinterpret_cast<char*>(&(d.month)), sizeof(d.month)) &&
		f->read(reinterpret_cast<char*>(&(d.year)), sizeof(d.year)) &&
		f->read(reinterpret_cast<char*>(&(d.hour)), sizeof(d.hour)) &&
		f->read(reinterpret_cast<char*>(&(d.minute)), sizeof(d.minute));
}

// Запись DateTime в бинарный файл
void DateTimeToBin(const DateTime &d, std::fstream *f) {
	f->write(reinterpret_cast<char*>(const_cast<int32_t*>(&d.day)), sizeof(d.day)) &&
		f->write(reinterpret_cast<char*>(const_cast<int32_t*>(&d.month)), sizeof(d.month)) &&
		f->write(reinterpret_cast<char*>(const_cast<int32_t*>(&d.year)), sizeof(d.year)) &&
		f->write(reinterpret_cast<char*>(const_cast<int32_t*>(&d.hour)), sizeof(d.hour)) &&
		f->write(reinterpret_cast<char*>(const_cast<int32_t*>(&d.minute)), sizeof(d.minute));
}

// Сравнение DateTime
int CompareDateTime(const DateTime &d1, const DateTime &d2) {
	if (d1.year > d2.year) return 1;
	if (d1.year < d2.year) return -1;
	if (d1.month > d2.month) return 1;
	if (d1.month < d2.month) return -1;
	if (d1.day > d2.day) return 1;
	if (d1.day < d2.day) return -1;

	if (d1.hour > d2.hour) return 1;
	if (d1.hour < d2.hour) return -1;
	if (d1.minute > d2.minute) return 1;
	if (d1.minute < d2.minute) return -1;

	return 0;
}