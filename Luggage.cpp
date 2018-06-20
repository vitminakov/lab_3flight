#include <iostream>
#include <iomanip>
#include <ctime>
#include "Utils.h"
#include "Luggage.h"


// Получение сведений о багаже из консоли
bool ReadLuggage(Luggage &luggage) {
	string str;
	Luggage l;

	cout << "Введите ФИО владельца: ";
	InputStr(l.owner);
	if ((l.owner == "") || (l.owner == " ")) return false;

	cout << "Введите номер рейса: ";
	if (!InputNum(l.flight)) return false;

	cout << "Введите дату и время вылета (дд.мм.гггг чч:мм) : ";
	InputStr(str);
	if (!DateTimeFromStr(str, l.departure)) return false;

	cout << "Введите пункт назначения: ";
	InputStr(l.destination);
	if ((l.destination == "") || (l.destination == " ")) return false;

	cout << "Введите количество занимаемых багажом мест: ";
	if (!InputNum(l.countOfPlaces)) return false;

	cout << "Введите суммарный вес багажа: ";
	if (!InputNum(l.totalWeight)) return false;

	luggage = l;
	return true;
}

// Вывод на консоль
void ShowLuggage(const Luggage &luggage) {
	cout << setw(25) << left << luggage.owner
		<< setw(8) << left << luggage.flight
		<< setw(20) << left << DateTimeToStr(luggage.departure)
		<< setw(15) << left << luggage.destination
		<< setw(15) << left << luggage.countOfPlaces
		<< setw(1) << left << luggage.totalWeight << "кг." <<endl;
}


// Считывание сведений о багаже из файла
bool LuggageFromFile(Luggage &luggage, fstream *f) {
	string str;
	Luggage l;

	if (!f->is_open()) return false;

	try {
		l.owner = StrFromBin(f);
		if (l.owner == "") return false;
		f->read(reinterpret_cast<char*>(&l.flight), sizeof(l.flight));
		if (!DateTimeFromBin(l.departure, f)) return false;
		l.destination = StrFromBin(f);
		if (l.destination == "") return false;
		f->read(reinterpret_cast<char*>(&l.countOfPlaces), sizeof(l.countOfPlaces));
		f->read(reinterpret_cast<char*>(&l.totalWeight), sizeof(l.totalWeight));

		luggage = l;

		return true;
	}
	catch (...) {
		throw "Не удалось считать из файла";
	}
}

// Вывод в файл
void LuggageToFile(const Luggage &luggage, fstream *f) {
	StrToBin(f, luggage.owner);
	f->write(reinterpret_cast<char*>(const_cast<int32_t*>(&luggage.flight)), sizeof(luggage.flight));
	DateTimeToBin(luggage.departure, f);
	StrToBin(f, luggage.destination);
	f->write(reinterpret_cast<char*>(const_cast<int32_t*>(&luggage.countOfPlaces)), sizeof(luggage.countOfPlaces));
	f->write(reinterpret_cast<char*>(const_cast<double*>(&luggage.totalWeight)), sizeof(luggage.totalWeight));
}