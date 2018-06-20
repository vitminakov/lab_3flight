#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Utils.h"

//класс контейнер 
template <typename T>
class MyContainer
{
private:
	std::vector<T> _records; //контейнер
	std::string _sourceName;
	bool (*_load)(T&, std::fstream*); //функция загрузки
	void (*_save)(const T&, std::fstream*); //функция сохранения

									//сохранение в файл
	void Save() {
		if (_sourceName == "") {
			return;
		}
		std::fstream file;
		file.open(_sourceName, std::ios::binary | std::ios::out);
		for (T el : _records) {
			_save(el, &file);
		}
		file.close();
	}

public:

	MyContainer() {
		_sourceName = "";
	}

	//конструктор
	MyContainer(std::string fileName, bool(*ld)(T&, std::fstream*),
		void(*sv)(const T&, std::fstream*))
	{
		_load = ld;
		_save = sv;
		if (fileName == "") {
			_sourceName = "DefaultSource.dat";
		}
		else {
			_sourceName = fileName;
		}
		std::fstream file;
		file.open(_sourceName, std::ios::binary | std::ios::in);
		if (file.is_open()) {
			T el;
			while (_load(el, &file)) {
				Add(el);
			}
		}
		else {
			file.open(_sourceName, std::ios::binary | std::ios::out);
		}
		file.close();
	}

	//деструктор
	~MyContainer() {
		Save();
		_records.clear();
	}

	//кол-во элементов в контейнере
	int Count() {
		return _records.size();
	}
	T GetElem(int ind) {
		if (ind < 0 || ind >= _records.size()) {
			throw "Неверный индекс";
		}
		return _records[ind];
	}

	//сортировка
	void Sort(bool(*compare)(const T&, const T&)) {
		std::sort(_records.begin(), _records.end(), compare);
	}

	//выборка подмножества по заданному критерию
	MyContainer<T> LinearSearchSubSet(bool(*func)(T, T), T crit) {
		MyContainer<T> subSet;
		for (T rec : _records) {
			if (func(rec, crit)) {
				subSet.Add(rec);
			}
		}
		return subSet;
	}

	//возвращает индекс элемента с заданным критерием
	int LinearSearch(bool (*func)(const T&, const T&), T crit) {
		int i = 0;
		for (T rec : _records) {
			if (func(rec, crit)) {
				return i;
			}
			++i;
		}
		return -1;
	}


	//бинарный поиск
	MyContainer<T> BinarySearch(int(*func)(T, T), bool(*compare)(T, T), T crit) {
		Sort(compare);
		MyContainer<T> subSet;
		int left = 0, right = _records.size() - 1, mid = left + (right - left) / 2;
		while (left < right) {
			if (func(_records[mid], crit) >= 0) {
				right = mid;
			}
			else {
				left = mid + 1;
			}
			mid = left + (right - left) / 2;
		}
		if (func(_records[mid], crit) == 0) {
			subSet.Add(_records[mid]);
			bool lequal, requal;
			for (int i = mid - 1, j = mid + 1; i >= 0 && j < _records.size(); --i, ++j) {
				if (lequal = func(_records[i], crit) == 0) {
					subSet.Add(_records[i]);
				}
				if (requal = func(_records[j], crit) == 0) {
					subSet.Add(_records[j]);
				}
				if (!(lequal || requal)) {
					break;
				}
			}
		}
		return subSet;
	}

	//очистка
	void Clear() {
		_records.clear();
		Save();
	}

	//добавить 
	void Add(T client) {
		_records.push_back(client);
		Save();
	}

	//удаление по индексу
	void RemoveInd(int ind) {
		if (ind < 0 || ind >= _records.size()) {
			throw "Неверный индекс";
		}
		_records.erase(_records.begin() + ind);
		Save();
	}


	//изменение записи в консоле
	bool Change(bool(*func)(T&), int ind) {
		if (ind < 0 || ind >= _records.size()) {
			return false;
		}
		do {
			if (func(_records[ind])) {
				std::cout << "Запись изменена, продолжить изменение? " << std::endl;
			}
			else {
				std::cout << "Не удалось изменить запись, продолжить? " << std::endl;
			}
		} while (InputQuery());
		Save();
		return true;
	}


	//ввод с консоли
	void FromConsole(bool(*input)(T&)) {
		T t;
		do {
			std::cout << std::endl;
			if (input(t)) {
				Add(t);
				std::cout << "Запись успешно довавлена, еще? ";
			}
			else {
				std::cout << "Введено некорректное значение, повторить? ";
			}
		} while (InputQuery());
		Save();
	}

	//считывание из файла
	bool FromFile(bool(*input)(T&, std::fstream*), std::fstream *f) {
		if (!f->is_open()) {
			return false;
		}
		T tmp;
		while (!f->eof()) {
			if (input(tmp, f)) {
				Add(tmp);
			}
			else {
				return false;
			}
		}
		Save();
		return true;
	}

	//запись в поток
	void ToFile(void(*output)(T, std::fstream*), std::fstream *f) {
		if (!f->is_open()) {
			throw "Файл не открыт";
		}
		for (T r : _records) {
			output(r, f);
		}
	}

	//вывод в консоль
	void ToConsole(void(*output)(T)) {
		std::cout << std::endl;
		for (T r : _records) {
			output(r);
		}
		std::cout << std::endl << "Всего записей: " << _records.size() << std::endl;
	}
};
