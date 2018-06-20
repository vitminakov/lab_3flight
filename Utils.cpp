#include <iostream>
#include <iomanip>
#include <string>
#include "Utils.h"

//вопрос пользователю
bool InputQuery() {
	char c;
	do {
		std::cout << "Y/N? ";
		std::cin >> c;
	} while (c != 'n' && c != 'N' && c != 'y' && c != 'Y');
	return c == 'Y' || c == 'y';
}

//ввод номера
bool InputNum(double & num) {
	std::cin >> num;
	bool OK = std::cin.good();
	std::cin.clear();
	/*Функция игнорирования используется для пропуска
	(отбрасывания/выброса) символов во входном потоке.
	У потока ввода есть буфер чтения, в котором он хранит символы.
	Мы обращаемся к нему, вызывая функцию rdbuf().
	А любой уважающий себя буфер знает, сколько символов в нем содержится.
	Поскольку и мы хотим это узнать, мы вызываем функцию in_avail()
	этого буфера. Это количество символов нам и нужно проигнорировать*/
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return OK;
}

bool InputNum(int32_t &num) {
	std::cin >> num;
	bool OK = std::cin.good();
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return OK;
}

//считывание строки из бинарного файла
std::string StrFromBin(std::fstream *f) {
	std::string result;
	int32_t len;
	if (!f->read(reinterpret_cast<char*>(&len), sizeof(len))) {
		return "";
	}
	char *buf = new char[len];
	if (!f->read(buf, len)) {
		return "";
	}
	result = buf;
	delete[] buf;
	return result;
}

//запись строки в бинарный файл
void StrToBin(std::fstream *f, std::string str) {
	int32_t len = str.length() + 1;
	f->write(reinterpret_cast<char*>(&len), sizeof(len));
	f->write(str.c_str(), len);
}

void ShowHeader() {
	std::cout << std::setw(25) << std::left << "Владелец:"
		<< std::setw(8) << std::left << "Рейс:"
		<< std::setw(20) << std::left << "Отправление:"
		<< std::setw(15) << std::left << "Назначение:"
		<< std::setw(15) << std::left << "Кол-во мест:"
		<< std::setw(5) << std::left << "Вес багажа:";
}


void InputStr(std::string &str) {
	std::getline(std::cin, str);
}