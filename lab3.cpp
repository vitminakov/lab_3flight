/* №10. Реализовать систему управления багажом. */
#include <iostream>
#include <string>
#include "DateTime.h"
#include "Luggage.h"
#include "MyContainer.h"
#include <Windows.h>


/* Сдача багажа */
void DropOff(MyContainer<Luggage> &storage) {
	Luggage luggage;

	cout << "Сдача багажа" << endl;
	if (ReadLuggage(luggage) == true) {
		storage.Add(luggage);
		cout << "Багаж успешно сдан." << endl;
	}
	else cout << "Багаж не был сдан." << endl;
}

/* Получить багаж */

void Claim(MyContainer<Luggage> &storage) {
	auto check = [](const Luggage &l1, const Luggage& l2) {
		return l1.owner.compare(l2.owner) == 0 && l1.flight == l2.flight;
	};

	Luggage luggage;
	int index;

	cout << "Получение багажа" << endl << "Введите ФИО владельца: ";
	InputStr(luggage.owner);
	cout << "Введите номер рейса: ";
	cin >> luggage.flight;
	cout << endl;

	index = storage.LinearSearch(check, luggage);

	if (index == -1) cout << "Багаж не найден." << endl;
	else {
		cout << "Выдан багаж: " << endl;

		ShowHeader();
		cout << endl;

		while (index != -1) {
			ShowLuggage(storage.GetElem(index));
			storage.RemoveInd(index);
			index = storage.LinearSearch(check, luggage);
		}

		cout << endl;
	}
}

/* Получить сведения о багаже (поиск) */

void ViewAll(MyContainer<Luggage> &storage) {
	int ans;

	do {
		cout << "Сведения о багаже" << endl
			<< "1> По имени владельца" << endl
			<< "2> По номеру рейса" << endl
			<< "3> По времени отправления" << endl
			<< "0> Выход" << endl
			<< ">";
	} while (!InputNum(ans) || ans < 0 || ans > 3);
	cout << endl;

	switch (ans)
	{
	case 0: return;
	case 1: storage.Sort([](const Luggage &l1, const Luggage &l2) { return l1.owner.compare(l2.owner) == -1; }); break;
	case 2: storage.Sort([](const Luggage &l1, const Luggage &l2) { return l1.flight < l2.flight; }); break;
	case 3: storage.Sort([](const Luggage &l1, const Luggage &l2) { return CompareDateTime(l1.departure, l2.departure) == -1; }); break;
	}

	ShowHeader();
	cout << endl;

	auto count = storage.Count();
	if (count == 0) cout << "Хранилище пусто." << endl;
	else for (int i = 0; i < count; i++) ShowLuggage(storage.GetElem(i));
	cout << endl;
}


/* Изъять багаж (удаление) */
void Confiscate(MyContainer<Luggage> &storage) {
	auto check = [](const Luggage &l1, const Luggage& l2) {
		return l1.owner.compare(l2.owner) == 0 && l1.flight == l2.flight;
	};

	Luggage luggage;
	int index;

	cout << "Изъятие багажа" << endl << "Введите имя владельца: ";
	InputStr(luggage.owner);
	cout << "Введите номер рейса: ";
	cin >> luggage.flight;
	cout << endl;

	index = storage.LinearSearch(check, luggage);

	if (index == -1) cout << "Багаж не найден." << endl;
	else {
		cout << "Изъят багаж: " << endl;

		ShowHeader();
		cout << endl;
		while (index != -1) {
			ShowLuggage(storage.GetElem(index));
			storage.RemoveInd(index);
			index = storage.LinearSearch(check, luggage);
		}

		cout << endl;
	}
}

void Menu(MyContainer<Luggage> &storage) {
	int ans;

	while (true) {
		do {
			cout << "Система управления багажом" << endl;
			cout << "Выберите режим доступа:" << endl;
			cout << "1> Пассажир" << endl
				<< "2> Сотрудник управления" << endl
				<< "0> Выход" << endl
				<< ">";
		} while (!InputNum(ans) || ans < 0 || ans > 2);
		cout << endl;

		switch (ans) {
		case 0: return;
		case 1:
			do {
				cout << "1> Сдать багаж" << endl
					<< "2> Получить багаж" << endl
					<< "0> Выход" << endl
					<< ">";
			} while (!InputNum(ans) || ans < 0 || ans > 2);
			cout << endl;

			switch (ans) {
			case 1: DropOff(storage); break;
			case 2: Claim(storage); break;
			}

			break;
		case 2:
			do {
				cout << "1> Информация о багажах" << endl
					<< "2> Изъять багаж" << endl
					<< "0> Выход" << endl
					<< ">";
			} while (!InputNum(ans) || ans < 0 || ans > 2);
			cout << endl;

			switch (ans) {
			case 1: ViewAll(storage); break;
			case 2: Confiscate(storage); break;
			}

			break;
		}
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);

	MyContainer<Luggage> bank("Source.dat", LuggageFromFile, LuggageToFile);
	Menu(bank);


	return 0;
}