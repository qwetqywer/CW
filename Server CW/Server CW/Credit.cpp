#include "Credit.h"
#include "CW.h"
#include <stdio.h>

Credit * Credit::readFileInformation()
{
	string path_base = "credit.txt";
	Credit *credits;
	credits = new Credit[4];
	ifstream fin;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < 4; i++) {
			fin.getline(credits[i].type, 20, '\n');
			fin.getline(credits[i].money[0], 21, '\n');
			fin.getline(credits[i].money[1], 21, '\n');
			fin.getline(credits[i].money[2], 21, '\n');
			fin.getline(credits[i].time[0], 21, '\n');
			fin.getline(credits[i].time[1], 21, '\n');
			fin.getline(credits[i].time[2], 21, '\n');
		}
	}
	fin.close();
	return credits;
}
