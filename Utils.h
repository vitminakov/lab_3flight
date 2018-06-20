
#pragma once
#include <fstream>
//вопрос пользователю
bool InputQuery();

//ввод номера
bool InputNum(int32_t &num);
bool InputNum(double &num);

//считывание строки из бинарного файла
std::string StrFromBin(std::fstream *f);

//запись строки в бинарный файл
void StrToBin(std::fstream *f, std::string str);

void ShowHeader();

void InputStr(std::string &str);