#include "Checks.h"
#include <iostream>
#include <fstream>
using namespace std;


namespace Checks {

	int CheckNumber(int number, int max)
	{
		while (!(cin >> number) || (cin.peek() != '\n') || number <= 0 || number > max)
		{
			cout << "Неправильно введены данные\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		return number;
	}


	bool check_string(char* stroka) {

		for (int n = 0; n < strlen(stroka); n++)
			if ((isdigit((unsigned char)stroka[n]) || stroka[n] == ' '))
			{
				cout << "Неправильно введены данные." << endl;
				return false;
			}
		return true;

	}

	bool checkPassport(char* stroka) {

		if (strlen(stroka) == 2) {

			for (int n = 0; n < strlen(stroka); n++)
				if ((isdigit((unsigned char)stroka[n]) || stroka[n] == ' '))
				{
					cout << "Неправильно введены данные." << endl;
					return false;
				}
			return true;
		}
		else {
			cout << "Неправильно введены данные." << endl;
			return false;
		}

	}

	bool checkPassportNumber(char* stroka) {

		if (strlen(stroka) == 7) {

			for (int n = 0; n < strlen(stroka); n++)
				if ((!isdigit((unsigned char)stroka[n]) || stroka[n] == ' '))
				{
					cout << "Неправильно введены данные." << endl;
					return false;
				}
			return true;
		}
		else {
			cout << "Неправильно введены данные." << endl;
			return false;
		}

	}

	int Check_acc_number()
	{
		int number;
		while (!(cin >> number) || (cin.peek() != '\n') || number < 100000000 || number > 999999999)
		{
			cout << "Неправильно введены данные\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		return number;
	}


	int number_of_records(string path, int max) {
		ifstream f;
		f.open(path);
		int i = 0, count = 0;
		while (!f.eof()) {
			if (f.get() == '\n') {
				i++;
				if (i % max == 0) {
					count++;
				}
			}
		}
		f.close();
		return count;

	}

	int Check_day() {
		int number;
		while (!(cin >> number) || (cin.peek() != '\n') || number <= 0 || number > 31)
		{
			cout << "Неправильно введены данные\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		return number;
	}

	int Check_month() {
		int number;
		while (!(cin >> number) || (cin.peek() != '\n') || number <= 0 || number > 12)
		{
			cout << "Неправильно введены данные\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		return number;
	}

	int Check_year() {
		int number;
		while (!(cin >> number) || (cin.peek() != '\n') || number < 1925 || number > 2002)
		{
			cout << "Неправильно введены данные\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		return number;
	}

	int Check_range(int n1) {
		int number;
		while (!(cin >> number) || (cin.peek() != '\n') || number < n1)
		{
			cout << "Неправильно введены данные\n";
			cout << "До:";
			cin.clear();
			while (cin.get() != '\n');
		}
		return number;
	}
};
