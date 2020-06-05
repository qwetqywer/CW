#pragma once
#include <string>

using namespace std;
#ifndef Checks_h
#define Checks_h
namespace Checks {
	int CheckNumber(int number, int max);
	int number_of_records(string path, int max);
	int Check_day();
	int Check_month();
	int Check_year();
	int Check_range(int n1);
	bool check_string(char* stroka);
	bool checkPassport(char* stroka);
	bool checkPassportNumber(char* stroka);
	int Check_acc_number();
};
#endif