#pragma once

#include <string>
#include <fstream>
#include "DateTime.h"

using namespace std;

// Структура "Багаж"
struct Luggage {
	string owner; // passenger
	int32_t flight;
	DateTime departure;
	string destination;
	int32_t countOfPlaces;
	double_t totalWeight;
};

// Получение сведений о багаже из консоли
bool ReadLuggage(Luggage&);

// Вывод на консоль
void ShowLuggage(const Luggage&);

// Считывание сведений о багаже из файла
bool LuggageFromFile(Luggage&, fstream*);

// Вывод в файл
void LuggageToFile(const Luggage&, fstream*);