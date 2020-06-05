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
	bool check_string(string stroka) {


		for (int n = 0; n < stroka.size(); n++)
			if ((isdigit((unsigned char)stroka[n]) || stroka[n] == ' '))
			{
				cout << "Неправильно введены данные." << endl;
				return false;
			}
		return true;

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
		while (!(cin >> number) || (cin.peek() != '\n') || number < 2019 || number > 2020)
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
