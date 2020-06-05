#include "Customers.h"
#include "User.h"
#include "CW.h"
#include <ctime>
#include "Credit.h"
#include "InvalidNumberException.h"

int counter = 0;

void Customers::addCustomer(SOCKET sserver)
{
	ifstream fin;
	
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	fin.open(path_base);
	int day, month, year;
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}

	}
	fin.close();
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);

	for (int i = 0; i < number_of_customers; i++) {
		send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
		send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);
	}


	srand(time(0));
	int acc = 100000000;

	char ch_day[5], ch_month[5], ch_year[5];
	recv(sserver, surname, sizeof(surname), 0);
	recv(sserver, name, sizeof(name), 0);
	recv(sserver, patronymic, sizeof(patronymic), 0);
	recv(sserver, ch_day, sizeof(ch_day), 0);
	recv(sserver, ch_month, sizeof(ch_month), 0);
	recv(sserver, ch_year, sizeof(ch_year), 0);
	recv(sserver, passportSeries, sizeof(passportSeries), 0);
	recv(sserver, passportNumber, sizeof(passportNumber), 0);
	
	ofstream fout;
	fout.open(path_base, ios_base::trunc);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else{
		for (int i = 0; i < number_of_customers; i++) {
			fout << customers[i].surname << endl;
			fout << customers[i].name << endl;
			fout << customers[i].patronymic << endl;
			day = customers[i].date.get_day(); fout << day << endl;
			month = customers[i].date.get_month(); fout << month << endl;
			year = customers[i].date.get_year(); fout << year << endl;
			fout << customers[i].passportSeries << endl;
			fout << customers[i].passportNumber << endl;
			fout << customers[i].accountNumber << endl;
			fout << customers[i].cash << endl;
		}
		day = atoi(ch_day);
		month = atoi(ch_month);
		year = atoi(ch_year);
		acc = acc + rand() % 9999999;
		fout << surname << endl;
		fout << name << endl;
		fout << patronymic << endl;
		fout << day << endl;
		fout << month << endl;
		fout << year << endl;
		fout << passportSeries << endl;
		fout << passportNumber << endl;
		fout << acc<< endl;
		fout << cash << endl;
	}
	fout.close();
	char account[10];
	_itoa_s(acc, account, 10);
	send(sserver, account, sizeof(account), 0);


}


void Customers::showAll(SOCKET sserver) {
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	ifstream fin;
	int day, month, year;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;

	}
	else { 
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();


	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	for (int i = 0; i < number_of_customers; i++) 
	{
		send(sserver, customers[i].surname, sizeof(customers[i].surname), 0);
		send(sserver, customers[i].name, sizeof(customers[i].name), 0);
		send(sserver, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
		day = customers[i].date.get_day();
		_itoa_s(day, ch_day, 10);
		send(sserver, ch_day, sizeof(ch_day), 0);

		month = customers[i].date.get_month();
		_itoa_s(month, ch_month, 10);
		send(sserver, ch_month, sizeof(ch_month), 0);

		year = customers[i].date.get_year();
		_itoa_s(year, ch_year, 10);
		send(sserver, ch_year, sizeof(ch_year), 0);

		send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
		send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);

		_itoa_s(customers[i].accountNumber, acc, 10);
		send(sserver, acc, sizeof(acc), 0);

		_itoa_s(customers[i].cash, money, 10);
		send(sserver, money, sizeof(money), 0);
	}
	delete[] customers;
}


void Customers::deleteCustomer(SOCKET sserver) {
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	ifstream fin;
	int day, month, year;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	showAll(sserver);
	recv(sserver, msg, sizeof(msg), 0);
	int choice = atoi(msg);

	ofstream fout;
	fout.open(path_base, ios_base::trunc);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		if (number_of_customers != choice) {
			for (int u = choice - 1; u < number_of_customers - 1; u++)
				customers[u] = customers[u + 1];
		}
		for (int i = 0; i < number_of_customers - 1; i++) {
			fout << customers[i].surname << endl;
			fout << customers[i].name << endl;
			fout << customers[i].patronymic << endl;
			day = customers[i].date.get_day(); fout << day << endl;
			month = customers[i].date.get_month(); fout << month << endl;
			year = customers[i].date.get_year(); fout << year << endl;
			fout << customers[i].passportSeries << endl;
			fout << customers[i].passportNumber << endl;
			fout << customers[i].accountNumber << endl;
			fout << customers[i].cash << endl;
		}
	}
	fout.close();
	delete[] customers;
	User user;
	user.deleteUser(choice);
}

void Customers::editCustomer(SOCKET sserver) {

	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	ifstream fin;
	int day, month, year;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	showAll(sserver);
	recv(sserver, msg, sizeof(msg), 0);
	int choice = atoi(msg);

	//////////////////////////////////
	send(sserver, customers[choice - 1].surname, sizeof(customers[choice - 1].surname), 0);
	send(sserver, customers[choice - 1].name, sizeof(customers[choice - 1].name), 0);
	send(sserver, customers[choice - 1].patronymic, sizeof(customers[choice - 1].patronymic), 0);

	char ch_day[5], ch_month[5], ch_year[5];
	day = customers[choice - 1].date.get_day();
	_itoa_s(day, ch_day, 10);
	send(sserver, ch_day, sizeof(ch_day), 0);

	month = customers[choice - 1].date.get_month();
	_itoa_s(month, ch_month, 10);
	send(sserver, ch_month, sizeof(ch_month), 0);

	year = customers[choice - 1].date.get_year();
	_itoa_s(year, ch_year, 10);
	send(sserver, ch_year, sizeof(ch_year), 0);

	send(sserver, customers[choice - 1].passportSeries, sizeof(customers[choice - 1].passportSeries), 0);
	send(sserver, customers[choice - 1].passportNumber, sizeof(customers[choice - 1].passportNumber), 0);
	///////////////////////////////////////


	recv(sserver, customers[choice - 1].surname, sizeof(customers[choice - 1].surname), 0);
	recv(sserver, customers[choice - 1].name, sizeof(customers[choice - 1].name), 0);
	recv(sserver, customers[choice - 1].patronymic, sizeof(customers[choice - 1].patronymic), 0);
	recv(sserver, ch_day, sizeof(ch_day), 0);
	recv(sserver, ch_month, sizeof(ch_month), 0);
	recv(sserver, ch_year, sizeof(ch_year), 0);
	day = atoi(ch_day);
	month = atoi(ch_month);
	year = atoi(ch_year);
	customers[choice - 1].date.set_day(day);
	customers[choice - 1].date.set_month(month);
	customers[choice - 1].date.set_year(year);
	recv(sserver, customers[choice - 1].passportSeries, sizeof(customers[choice - 1].passportSeries), 0);
	recv(sserver, customers[choice - 1].passportNumber, sizeof(customers[choice - 1].passportNumber), 0);
	//////////////////////////////////////////

	ofstream fout;
	fout.open(path_base, ios_base::trunc);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fout << customers[i].surname << endl;
			fout << customers[i].name << endl;
			fout << customers[i].patronymic << endl;
			day = customers[i].date.get_day(); fout << day << endl;
			month = customers[i].date.get_month(); fout << month << endl;
			year = customers[i].date.get_year(); fout << year << endl;
			fout << customers[i].passportSeries << endl;
			fout << customers[i].passportNumber << endl;
			fout << customers[i].accountNumber << endl;
			fout << customers[i].cash << endl;
		}
	}
	fout.close();
	delete[] customers;
}

void Customers::searchMenu(SOCKET sserver) {

	int check = 0;
	char msgChoice[5];
	do
	{
		recv(sserver, msgChoice, sizeof(msgChoice), 0);
		int choice = atoi(msgChoice);

		switch (choice)
		{
		case 1: {
			searchSNP(sserver);
			break;
		}
		case 2: { 
			searchPassport(sserver);
			break;
		}
		case 3: {
			searchAccountNumber(sserver);
			break; 
		}
		case 4: {
			sortingCustomers(sserver);
			break;

		}
		case 5:
			check = 5;
			break;
		}

	} while (check == 0);
}

void Customers::searchSNP(SOCKET sserver) {

	string path_base = "customers.txt";
	char surname_s[20];
	char patronymic_p[20];
	char name_n[20];
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	int flag = 0;
	int number_of_customers = Checks::number_of_records(path_base, 10);
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	if (number_of_customers == 0) {
		cout << "Нет зарегистрированных клиентов." << endl;
		system("pause");
	}
	else {
		recv(sserver, surname_s, sizeof(surname_s), 0);
		recv(sserver, name_n, sizeof(name_n), 0);
		recv(sserver, patronymic_p, sizeof(patronymic_p), 0);
		Customers *customers;
		customers = new Customers[number_of_customers];
		ifstream fin;
		int day, month, year, check = 0;
		fin.open(path_base);
		if (!fin.is_open()) {
			cout << "Ошибка открытия файла." << endl;

		}
		else {
			for (int i = 0; i < number_of_customers; i++) {
				fin >> customers[i].surname;
				fin >> customers[i].name;
				fin >> customers[i].patronymic;
				fin >> day; customers[i].date.set_day(day);
				fin >> month; customers[i].date.set_month(month);
				fin >> year; customers[i].date.set_year(year);
				fin >> customers[i].passportSeries;
				fin >> customers[i].passportNumber;
				fin >> customers[i].accountNumber;
				fin >> customers[i].cash;
				if (strcmp(customers[i].surname, surname_s) == 0 && strcmp(customers[i].name, name_n) == 0 && strcmp(customers[i].patronymic, patronymic_p) == 0) {
					check++;
				}
			}

			char msg[5];
			_itoa_s(check, msg, 10);
			send(sserver, msg, sizeof(msg), 0);
			if (check == 0) {

			}
			else {
				for (int i = 0; i < number_of_customers; i++) {
					if (strcmp(customers[i].surname, surname_s) == 0 && strcmp(customers[i].name, name_n) == 0 && strcmp(customers[i].patronymic, patronymic_p) == 0) {
						send(sserver, customers[i].surname, sizeof(customers[i].surname), 0);
						send(sserver, customers[i].name, sizeof(customers[i].name), 0);
						send(sserver, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
						day = customers[i].date.get_day();
						_itoa_s(day, ch_day, 10);
						send(sserver, ch_day, sizeof(ch_day), 0);

						month = customers[i].date.get_month();
						_itoa_s(month, ch_month, 10);
						send(sserver, ch_month, sizeof(ch_month), 0);

						year = customers[i].date.get_year();
						_itoa_s(year, ch_year, 10);
						send(sserver, ch_year, sizeof(ch_year), 0);

						send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
						send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);

						_itoa_s(customers[i].accountNumber, acc, 10);
						send(sserver, acc, sizeof(acc), 0);

						_itoa_s(customers[i].cash, money, 10);
						send(sserver, money, sizeof(money), 0);
					}
				}
			}
		}
		fin.close();
	}

	


}

void Customers::searchPassport(SOCKET sserver) {
	string path_base = "customers.txt";
	char passportSeries_p[5];
	char passportNumber_p[8];
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	int flag = 0;
	int number_of_customers = Checks::number_of_records(path_base, 10);
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	if (number_of_customers == 0) {
		cout << "Нет зарегистрированных клиентов." << endl;
		system("pause");
	}
	else {
		recv(sserver, passportSeries_p, sizeof(passportSeries_p), 0);
		recv(sserver, passportNumber_p, sizeof(passportNumber_p), 0);
		
		Customers *customers;
		customers = new Customers[number_of_customers];
		ifstream fin;
		int day, month, year, check = 0;
		fin.open(path_base);
		if (!fin.is_open()) {
			cout << "Ошибка открытия файла." << endl;

		}
		else {
			for (int i = 0; i < number_of_customers; i++) {
				fin >> customers[i].surname;
				fin >> customers[i].name;
				fin >> customers[i].patronymic;
				fin >> day; customers[i].date.set_day(day);
				fin >> month; customers[i].date.set_month(month);
				fin >> year; customers[i].date.set_year(year);
				fin >> customers[i].passportSeries;
				fin >> customers[i].passportNumber;
				fin >> customers[i].accountNumber;
				fin >> customers[i].cash;
				if (strcmp(customers[i].passportSeries, passportSeries_p) == 0 && strcmp(customers[i].passportNumber, passportNumber_p) == 0 ) {
					check++;
				}
			}

			char msg[5];
			_itoa_s(check, msg, 10);
			send(sserver, msg, sizeof(msg), 0);
			if (check == 0) {

			}
			else {
				for (int i = 0; i < number_of_customers; i++) {
					if (strcmp(customers[i].passportSeries, passportSeries_p) == 0 && strcmp(customers[i].passportNumber, passportNumber_p) == 0) {
						send(sserver, customers[i].surname, sizeof(customers[i].surname), 0);
						send(sserver, customers[i].name, sizeof(customers[i].name), 0);
						send(sserver, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
						day = customers[i].date.get_day();
						_itoa_s(day, ch_day, 10);
						send(sserver, ch_day, sizeof(ch_day), 0);

						month = customers[i].date.get_month();
						_itoa_s(month, ch_month, 10);
						send(sserver, ch_month, sizeof(ch_month), 0);

						year = customers[i].date.get_year();
						_itoa_s(year, ch_year, 10);
						send(sserver, ch_year, sizeof(ch_year), 0);

						send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
						send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);

						_itoa_s(customers[i].accountNumber, acc, 10);
						send(sserver, acc, sizeof(acc), 0);

						_itoa_s(customers[i].cash, money, 10);
						send(sserver, money, sizeof(money), 0);
					}
				}
			}
		}
		fin.close();
	}

}

void Customers::searchAccountNumber(SOCKET sserver) {
	string path_base = "customers.txt";
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	int flag = 0;
	int number_of_customers = Checks::number_of_records(path_base, 10);
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	if (number_of_customers == 0) {
		cout << "Нет зарегистрированных клиентов." << endl;
		system("pause");
	}
	else {
		recv(sserver, acc, sizeof(acc), 0);
		int accNumber = atoi(acc);

		Customers *customers;
		customers = new Customers[number_of_customers];
		ifstream fin;
		int day, month, year, check = 0;
		fin.open(path_base);
		if (!fin.is_open()) {
			cout << "Ошибка открытия файла." << endl;

		}
		else {
			for (int i = 0; i < number_of_customers; i++) {
				fin >> customers[i].surname;
				fin >> customers[i].name;
				fin >> customers[i].patronymic;
				fin >> day; customers[i].date.set_day(day);
				fin >> month; customers[i].date.set_month(month);
				fin >> year; customers[i].date.set_year(year);
				fin >> customers[i].passportSeries;
				fin >> customers[i].passportNumber;
				fin >> customers[i].accountNumber;
				fin >> customers[i].cash;
				if (customers[i].accountNumber==accNumber) {
					check++;
				}
			}

			char msg[5];
			_itoa_s(check, msg, 10);
			send(sserver, msg, sizeof(msg), 0);
			if (check == 0) {

			}
			else {
				for (int i = 0; i < number_of_customers; i++) {
					if (customers[i].accountNumber == accNumber) {
						send(sserver, customers[i].surname, sizeof(customers[i].surname), 0);
						send(sserver, customers[i].name, sizeof(customers[i].name), 0);
						send(sserver, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
						day = customers[i].date.get_day();
						_itoa_s(day, ch_day, 10);
						send(sserver, ch_day, sizeof(ch_day), 0);

						month = customers[i].date.get_month();
						_itoa_s(month, ch_month, 10);
						send(sserver, ch_month, sizeof(ch_month), 0);

						year = customers[i].date.get_year();
						_itoa_s(year, ch_year, 10);
						send(sserver, ch_year, sizeof(ch_year), 0);

						send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
						send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);

						_itoa_s(customers[i].accountNumber, acc, 10);
						send(sserver, acc, sizeof(acc), 0);

						_itoa_s(customers[i].cash, money, 10);
						send(sserver, money, sizeof(money), 0);
					}
				}
			}
		}
		fin.close();
	}

}

void Customers::sortingCustomers(SOCKET sserver)
{
	string path_base = "customers.txt";
	int number_of_customers = Checks::number_of_records(path_base, 10);
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	if (number_of_customers == 0) {
	}
	else {
		Customers *customers;
		customers = new Customers[number_of_customers];
		ifstream fin;
		int day, month, year;
		fin.open(path_base);
		if (!fin.is_open()) {
			cout << "Ошибка открытия файла." << endl;

		}
		else {
			for (int i = 0; i < number_of_customers; i++) {
				fin >> customers[i].surname;
				fin >> customers[i].name;
				fin >> customers[i].patronymic;
				fin >> day; customers[i].date.set_day(day);
				fin >> month; customers[i].date.set_month(month);
				fin >> year; customers[i].date.set_year(year);
				fin >> customers[i].passportSeries;
				fin >> customers[i].passportNumber;
				fin >> customers[i].accountNumber;
				fin >> customers[i].cash;

			}

			for (int j = 0; j < number_of_customers; j++) {
				for (int i = 0; i < number_of_customers - 1; i++) {
					if (strcmp(customers[i].surname,customers[i + 1].surname)>0) {
						swap(customers[i], customers[i + 1]);
					}
				}
			}

			char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
			for (int i = 0; i < number_of_customers; i++)
			{
				send(sserver, customers[i].surname, sizeof(customers[i].surname), 0);
				send(sserver, customers[i].name, sizeof(customers[i].name), 0);
				send(sserver, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
				day = customers[i].date.get_day();
				_itoa_s(day, ch_day, 10);
				send(sserver, ch_day, sizeof(ch_day), 0);

				month = customers[i].date.get_month();
				_itoa_s(month, ch_month, 10);
				send(sserver, ch_month, sizeof(ch_month), 0);

				year = customers[i].date.get_year();
				_itoa_s(year, ch_year, 10);
				send(sserver, ch_year, sizeof(ch_year), 0);

				send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
				send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);

				_itoa_s(customers[i].accountNumber, acc, 10);
				send(sserver, acc, sizeof(acc), 0);

				_itoa_s(customers[i].cash, money, 10);
				send(sserver, money, sizeof(money), 0);
			}
			
		}
		delete[] customers;
		fin.close();

	}
}

void Customers::transfer(SOCKET sserver,int numUser) {
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	ifstream fin;
	int day, month, year;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();

	char cash_msg[10];
	_itoa_s(customers[numUser].cash, cash_msg, 10);
	send(sserver, cash_msg, sizeof(cash_msg), 0);


	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	for (int i = 0; i < number_of_customers; i++)
	{
		send(sserver, customers[i].surname, sizeof(customers[i].surname), 0);
		send(sserver, customers[i].name, sizeof(customers[i].name), 0);
		send(sserver, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
		day = customers[i].date.get_day();
		_itoa_s(day, ch_day, 10);
		send(sserver, ch_day, sizeof(ch_day), 0);

		month = customers[i].date.get_month();
		_itoa_s(month, ch_month, 10);
		send(sserver, ch_month, sizeof(ch_month), 0);

		year = customers[i].date.get_year();
		_itoa_s(year, ch_year, 10);
		send(sserver, ch_year, sizeof(ch_year), 0);

		send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
		send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);

		_itoa_s(customers[i].accountNumber, acc, 10);
		send(sserver, acc, sizeof(acc), 0);

		_itoa_s(customers[i].cash, money, 10);
		send(sserver, money, sizeof(money), 0);
	}
	char msg_g[10];
	recv(sserver, msg_g, sizeof(msg_g), 0);
	int accNumber = atoi(msg_g);
	recv(sserver, msg_g, sizeof(msg_g), 0);
	int amountMoney = atoi(msg_g);


		customers[numUser].cash = customers[numUser].cash - amountMoney;
		for (int i = 0; i < number_of_customers; i++) {
			if (customers[i].accountNumber == accNumber) {
				customers[i].cash = customers[i].cash + amountMoney;
				break;
			}
		}

		_itoa_s(customers[numUser].cash, money, 10);
		send(sserver, money, sizeof(money), 0);
		_itoa_s(customers[numUser].accountNumber, acc, 10);
		send(sserver, acc, sizeof(acc), 0);

		ofstream fout;
		fout.open(path_base, ios_base::trunc);
		if (!fout.is_open()) {
			cout << "Ошибка открытия файла." << endl;
		}
		else {
			for (int i = 0; i < number_of_customers; i++) {
				fout << customers[i].surname << endl;
				fout << customers[i].name << endl;
				fout << customers[i].patronymic << endl;
				day = customers[i].date.get_day(); fout << day << endl;
				month = customers[i].date.get_month(); fout << month << endl;
				year = customers[i].date.get_year(); fout << year << endl;
				fout << customers[i].passportSeries << endl;
				fout << customers[i].passportNumber << endl;
				fout << customers[i].accountNumber << endl;
				fout << customers[i].cash << endl;
			}
		}
		fout.close();
	
	delete[] customers;

}

void Customers::applyForALoan(SOCKET sserver, int numUser)
{

	ifstream fin;
	string path_base = "applications.txt";
	int number_of_lenders = number_of_records(path_base, 15);
	Customers *lenders;
	lenders = new Customers[number_of_lenders];
	fin.open(path_base);
	int salary1, salary2, salary3, salary4;
	int day, month, year;
	char type[20], money[21], time[21], type_ch[20], money_ch[21], time_ch[21];
	char pr[2];
	try
	{
		fin.open(path_base);
	}
	catch (const InvalidNumberException& ex)
	{
		cout << ex.what() << endl;
		cout << "Ошибка открытия файла." << endl;
	}
		
	
		for (int i = 0; i < number_of_lenders; i++) {
			fin.getline(lenders[i].surname, sizeof(lenders[i].surname), '\n');
			fin.getline(lenders[i].name, sizeof(lenders[i].name), '\n'); 	
			fin.getline(lenders[i].patronymic, sizeof(lenders[i].patronymic), '\n'); 
			fin >> day; lenders[i].date.set_day(day);
			fin >> month; lenders[i].date.set_month(month);
			fin >> year; lenders[i].date.set_year(year);
			fin.getline(pr, sizeof(pr), '\n');
			fin.getline(lenders[i].passportSeries, sizeof(lenders[i].passportSeries), '\n');
			fin.getline(lenders[i].passportNumber, sizeof(lenders[i].passportNumber), '\n');
			fin.getline(type, sizeof(type), '\n'); lenders[i].credit.set_type(type);
			fin.getline(money, sizeof(money), '\n');  lenders[i].credit.set_money(money);
			fin.getline(time, sizeof(time), '\n');  lenders[i].credit.set_time(time);
			fin >> salary1; lenders[i].credit.set_salary1(salary1);
			fin >> salary2; lenders[i].credit.set_salary2(salary2);
			fin >> salary3; lenders[i].credit.set_salary3(salary3);
			fin >> salary4; lenders[i].credit.set_salary4(salary4);
		}

	
	fin.close();

	path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();


	Credit *credits;
	credits = new Credit[4];
	credits = credits->readFileInformation();
	int money_m, time_t, choice;
	char msg_choice[5];
	recv(sserver, msg_choice, sizeof(msg_choice), 0);
	choice = atoi(msg_choice);


	char msg_money[10], msg_time[10];
	recv(sserver, msg_money, sizeof(msg_money), 0);
	recv(sserver, msg_time, sizeof(msg_time), 0);
	money_m = atoi(msg_money);
	time_t = atoi(msg_time);
	if (choice == 1) {
		if (money_m == 1) {
			credits[0].setMoney1();
		}
		if (money_m == 2) {
			credits[0].setMoney2();
		}
		if (money_m == 3) {
			credits[0].setMoney3();
		}
		if (money_m == 1) {
			credits[0].setTime1();
		}
		if (money_m == 2) {
			credits[0].setTime2();
		}
		if (money_m == 3) {
			credits[0].setTime3();
		}
	}
	if (choice == 2) {
		if (money_m == 1) {
			credits[1].setMoney1();
		}
		if (money_m == 2) {
			credits[1].setMoney2();
		}
		if (money_m == 3) {
			credits[1].setMoney3();
		}
		if (money_m == 1) {
			credits[1].setTime1();
		}
		if (money_m == 2) {
			credits[1].setTime2();
		}
		if (money_m == 3) {
			credits[1].setTime3();
		}
	}
	if (choice == 3) {
		char m[21];
		_itoa_s(money_m, m, 10);
		credits[2].set_money(m);
		credits[2].setTime2();
	}
	if (choice == 4) {
		if (money_m == 1) {
			credits[3].setMoney1();
		}
		if (money_m == 2) {
			credits[3].setMoney2();
		}
		if (money_m == 3) {
			credits[3].setMoney3();
		}
		if (money_m == 1) {
			credits[3].setTime1();
		}
		if (money_m == 2) {
			credits[3].setTime2();
		}
		if (money_m == 3) {
			credits[3].setTime3();
		}
	}
	strcpy(type_ch, credits[choice - 1].get_type());
	strcpy(money_ch, credits[choice - 1].get_money());
	strcpy(time_ch, credits[choice - 1].get_time());

	char salary[10];

	recv(sserver, salary, sizeof(salary), 0);
	salary1 = atoi(salary);
	recv(sserver, salary, sizeof(salary), 0);
	salary2 = atoi(salary);
	recv(sserver, salary, sizeof(salary), 0);
	salary3 = atoi(salary);
	recv(sserver, salary, sizeof(salary), 0);
	salary4 = atoi(salary);
	int salary11, salary22, salary33, salary44;
	string base = "applications.txt";
	ofstream fout;
	fout.open(base, ios_base::trunc);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_lenders; i++) {
			fout << lenders[i].surname << endl;
			fout << lenders[i].name << endl;
			fout << lenders[i].patronymic << endl;
			day = lenders[i].date.get_day(); fout << day << endl;
			month = lenders[i].date.get_month(); fout << month << endl;
			year = lenders[i].date.get_year(); fout << year << endl;
			fout << lenders[i].passportSeries << endl;
			fout << lenders[i].passportNumber << endl;
			strcpy(type, lenders[i].credit.get_type()); fout << type << endl;
			strcpy(money, lenders[i].credit.get_money()); fout << money << endl;
			strcpy(time, lenders[i].credit.get_time()); fout << time << endl;
			salary11 = lenders[i].credit.get_salary1();   fout << salary11 << endl;
			salary22 = lenders[i].credit.get_salary2();   fout << salary22 << endl;
			salary33 = lenders[i].credit.get_salary3();   fout << salary33 << endl;
			salary44 = lenders[i].credit.get_salary4();   fout << salary44 << endl;
		}
		fout << customers[numUser].surname << endl;
		fout << customers[numUser].name << endl;
		fout << customers[numUser].patronymic << endl;
		day = customers[numUser].date.get_day(); fout << day << endl;
		month = customers[numUser].date.get_month(); fout << month << endl;
		year = customers[numUser].date.get_year(); fout << year << endl;
		fout << customers[numUser].passportSeries << endl;
		fout << customers[numUser].passportNumber << endl;
		fout << type_ch << endl;
		fout << money_ch << endl;
		fout << time_ch << endl;
		fout << salary1 << endl;
		fout << salary2 << endl;
		fout << salary3 << endl;
		fout << salary4 << endl;
	}
	fout.close();
}

void Customers::matrix(SOCKET sserver)
{
	ifstream fin;
	string path_base = "applications.txt";
	int number_of_customers = number_of_records(path_base, 15);
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	if (number_of_customers == 0) {

	}
	else {
		Customers *customers;
		customers = new Customers[number_of_customers];
		fin.open(path_base);

		

		int salary1, salary2, salary3, salary4;
		int day, month, year;
		char type[20], money[21], time[21];
		char pr[2];
		if (!fin.is_open()) {
			cout << "Ошибка открытия файла." << endl;
		}
		else {
			for (int i = 0; i < number_of_customers; i++) {
				fin >> customers[i].surname;
				fin >> customers[i].name;
				fin >> customers[i].patronymic;
				fin >> day; customers[i].date.set_day(day);
				fin >> month; customers[i].date.set_month(month);
				fin >> year; customers[i].date.set_year(year);
				fin.getline(pr, sizeof(pr), '\n');
				fin.getline(customers[i].passportSeries, sizeof(customers[i].passportSeries), '\n');
				fin.getline(customers[i].passportNumber, sizeof(customers[i].passportNumber), '\n');
				fin.getline(type, sizeof(type), '\n'); customers[i].credit.set_type(type);
				fin.getline(money, sizeof(money), '\n');  customers[i].credit.set_money(money);
				fin.getline(time, sizeof(time), '\n');  customers[i].credit.set_time(time);
				fin >> salary1; customers[i].credit.set_salary1(salary1);
				fin >> salary2; customers[i].credit.set_salary2(salary2);
				fin >> salary3; customers[i].credit.set_salary3(salary3);
				fin >> salary4; customers[i].credit.set_salary4(salary4);
			}

		}
		fin.close();
		int columns = 4;
		int **matrix;
		matrix = new int*[number_of_customers];
		for (int z = 0; z < number_of_customers; z++) { matrix[z] = new int[columns]; }

		for (int i = 0; i < number_of_customers; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = customers[i].credit.get_salary1();
				j++;
				matrix[i][j] = customers[i].credit.get_salary2();
				j++;
				matrix[i][j] = customers[i].credit.get_salary3();
				j++;
				matrix[i][j] = customers[i].credit.get_salary4();
				j++;

			}
		}

		char element[10];
		for (int i = 0; i < number_of_customers; i++) {
			for (int j = 0; j < columns; j++) {
				_itoa_s(matrix[i][j], element, 10);
				send(sserver, element, sizeof(element), 0);
			}
		}


		int *min = new int[number_of_customers];
		int minElement;
		for (int i = 0; i < number_of_customers; i++) {
			minElement = matrix[i][0];
			for (int j = 0; j < columns; j++) {
				if (matrix[i][j] < minElement)
				{
					minElement = matrix[i][j];
				}
			}
			min[i] = minElement;
			_itoa_s(minElement, element, 10);
			send(sserver, element, sizeof(element), 0);
		}

		int maxElement = min[0];
		int indexMax = 0;
		for (int i = 0; i < number_of_customers; i++) {

			if (min[i] > maxElement)
			{
				maxElement = min[i];
				indexMax = i;
			}
		}
		_itoa_s(maxElement, element, 10);
		send(sserver, element, sizeof(element), 0);
		_itoa_s(indexMax, element, 10);
		send(sserver, element, sizeof(element), 0);

		int choice = 2;
		char msg_g[10];
		recv(sserver, msg_g, sizeof(msg_g), 0);
		choice = atoi(msg_g);

		path_base = "approvedApplications.txt";
		int number_of_lenders = number_of_records(path_base, 15);
		Customers *lenders = new Customers[number_of_lenders];
		int  salary11, salary22, salary33, salary44;
		char  type_ch[20], money_ch[21], time_ch[21];

		fin.open(path_base);
		if (!fin.is_open()) {
			cout << "Ошибка открытия файла." << endl;
		}
		else {
			for (int i = 0; i < number_of_lenders; i++) {
				fin.getline(lenders[i].surname, sizeof(lenders[i].surname), '\n');
				fin.getline(lenders[i].name, sizeof(lenders[i].name), '\n');
				fin.getline(lenders[i].patronymic, sizeof(lenders[i].patronymic), '\n');
				fin >> day; lenders[i].date.set_day(day);
				fin >> month; lenders[i].date.set_month(month);
				fin >> year; lenders[i].date.set_year(year);
				fin.getline(pr, sizeof(pr), '\n');
				fin.getline(lenders[i].passportSeries, sizeof(lenders[i].passportSeries), '\n');
				fin.getline(lenders[i].passportNumber, sizeof(lenders[i].passportNumber), '\n');
				fin.getline(type, sizeof(type), '\n'); lenders[i].credit.set_type(type);
				fin.getline(money, sizeof(money), '\n');  lenders[i].credit.set_money(money);
				fin.getline(time, sizeof(time), '\n');  lenders[i].credit.set_time(time);
				fin >> salary1; lenders[i].credit.set_salary1(salary1);
				fin >> salary2; lenders[i].credit.set_salary2(salary2);
				fin >> salary3; lenders[i].credit.set_salary3(salary3);
				fin >> salary4; lenders[i].credit.set_salary4(salary4);
			}

		}
		fin.close();


		if (choice == 1) {


			fin.open(path_base);
			ofstream fout;
			fout.open(path_base, ios_base::trunc);
			if (!fout.is_open()) {
				cout << "Ошибка открытия файла." << endl;
			}
			else {
				for (int i = 0; i < number_of_lenders; i++) {
					fout << lenders[i].surname << endl;
					fout << lenders[i].name << endl;
					fout << lenders[i].patronymic << endl;
					day = lenders[i].date.get_day(); fout << day << endl;
					month = lenders[i].date.get_month(); fout << month << endl;
					year = lenders[i].date.get_year(); fout << year << endl;
					fout << lenders[i].passportSeries << endl;
					fout << lenders[i].passportNumber << endl;
					strcpy_s(type, lenders[i].credit.get_type()); fout << type << endl;
					strcpy_s(money, lenders[i].credit.get_money()); fout << money << endl;
					strcpy_s(time, lenders[i].credit.get_time()); fout << time << endl;
					salary11 = lenders[i].credit.get_salary1();   fout << salary11 << endl;
					salary22 = lenders[i].credit.get_salary2();   fout << salary22 << endl;
					salary33 = lenders[i].credit.get_salary3();   fout << salary33 << endl;
					salary44 = lenders[i].credit.get_salary4();   fout << salary44 << endl;
				}
				fout << customers[indexMax].surname << endl;
				fout << customers[indexMax].name << endl;
				fout << customers[indexMax].patronymic << endl;
				day = customers[indexMax].date.get_day(); fout << day << endl;
				month = customers[indexMax].date.get_month(); fout << month << endl;
				year = customers[indexMax].date.get_year(); fout << year << endl;
				fout << customers[indexMax].passportSeries << endl;
				fout << customers[indexMax].passportNumber << endl;
				strcpy_s(type, customers[indexMax].credit.get_type());  fout << type << endl;
				strcpy_s(money, customers[indexMax].credit.get_money());  fout << money << endl;
				strcpy_s(time, customers[indexMax].credit.get_time());  fout << time << endl;
				salary1 = customers[indexMax].credit.get_salary1(); fout << salary1 << endl;
				salary2 = customers[indexMax].credit.get_salary2(); fout << salary2 << endl;
				salary3 = customers[indexMax].credit.get_salary3(); fout << salary3 << endl;
				salary4 = customers[indexMax].credit.get_salary4(); fout << salary4 << endl;

			}
			fout.close();
			path_base = "applications.txt";
			fout.open(path_base, ios_base::trunc);
			if (!fout.is_open()) {
				cout << "Ошибка открытия файла." << endl;
			}
			else {
				if (number_of_customers != indexMax) {
					for (int u = indexMax; u < number_of_customers - 1; u++)
						customers[u] = customers[u + 1];
				}
				for (int i = 0; i < number_of_customers - 1; i++) {
					fout << customers[i].surname << endl;
					fout << customers[i].name << endl;
					fout << customers[i].patronymic << endl;
					day = customers[i].date.get_day(); fout << day << endl;
					month = customers[i].date.get_month(); fout << month << endl;
					year = customers[i].date.get_year(); fout << year << endl;
					fout << customers[i].passportSeries << endl;
					fout << customers[i].passportNumber << endl;
					strcpy_s(type, customers[i].credit.get_type());  fout << type << endl;
					strcpy_s(money, customers[i].credit.get_money());  fout << money << endl;
					strcpy_s(time, customers[i].credit.get_time());  fout << time << endl;
					salary1 = customers[i].credit.get_salary1(); fout << salary1 << endl;
					salary2 = customers[i].credit.get_salary2(); fout << salary2 << endl;
					salary3 = customers[i].credit.get_salary3(); fout << salary3 << endl;
					salary4 = customers[i].credit.get_salary4(); fout << salary4 << endl;
				}
			}
			fout.close();
			

		}
		for (int count = 0; count < number_of_lenders; count++)
			delete[] matrix[count];
	}
	
}

void Customers::showCredit(SOCKET sserver)
{
	string path_base = "approvedApplications.txt";
	int number_of_lenders = number_of_records(path_base, 15);
	Customers *lenders = new Customers[number_of_lenders];
	int  salary1, salary2, salary3, salary4, day, month, year;
	char  type[20], money[21], time[21];
	char pr[2];
	ifstream fin;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_lenders; i++) {
			fin.getline(lenders[i].surname, sizeof(lenders[i].surname), '\n');
			fin.getline(lenders[i].name, sizeof(lenders[i].name), '\n');
			fin.getline(lenders[i].patronymic, sizeof(lenders[i].patronymic), '\n');
			fin >> day; lenders[i].date.set_day(day);
			fin >> month; lenders[i].date.set_month(month);
			fin >> year; lenders[i].date.set_year(year);
			fin.getline(pr, sizeof(pr), '\n');
			fin.getline(lenders[i].passportSeries, sizeof(lenders[i].passportSeries), '\n');
			fin.getline(lenders[i].passportNumber, sizeof(lenders[i].passportNumber), '\n');
			fin.getline(type, sizeof(type), '\n'); lenders[i].credit.set_type(type);
			fin.getline(money, sizeof(money), '\n');  lenders[i].credit.set_money(money);
			fin.getline(time, sizeof(time), '\n');  lenders[i].credit.set_time(time);
			fin >> salary1; lenders[i].credit.set_salary1(salary1);
			fin >> salary2; lenders[i].credit.set_salary2(salary2);
			fin >> salary3; lenders[i].credit.set_salary3(salary3);
			fin >> salary4; lenders[i].credit.set_salary4(salary4);
		}

	}
	fin.close();

	char msg[5];
	_itoa_s(number_of_lenders, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	char ch_day[5], ch_month[5], ch_year[5], salary11[10], salary22[10], salary33[10], salary44[10];
	for (int i = 0; i < number_of_lenders; i++)
	{
		send(sserver, lenders[i].surname, sizeof(lenders[i].surname), 0);
		send(sserver, lenders[i].name, sizeof(lenders[i].name), 0);
		send(sserver, lenders[i].patronymic, sizeof(lenders[i].patronymic), 0);
		day = lenders[i].date.get_day();
		_itoa_s(day, ch_day, 10);
		send(sserver, ch_day, sizeof(ch_day), 0);

		month = lenders[i].date.get_month();
		_itoa_s(month, ch_month, 10);
		send(sserver, ch_month, sizeof(ch_month), 0);

		year = lenders[i].date.get_year();
		_itoa_s(year, ch_year, 10);
		send(sserver, ch_year, sizeof(ch_year), 0);

		send(sserver, lenders[i].passportSeries, sizeof(lenders[i].passportSeries), 0);
		send(sserver, lenders[i].passportNumber, sizeof(lenders[i].passportNumber), 0);

		strcpy(type, lenders[i].credit.get_type()); send(sserver, type, sizeof(type), 0);
		strcpy(money, lenders[i].credit.get_money()); send(sserver, money, sizeof(money), 0);
		strcpy(time, lenders[i].credit.get_time()); send(sserver, time, sizeof(time), 0);

		salary1 = lenders[i].credit.get_salary1();
		_itoa_s(salary1, salary11, 10);
		send(sserver, salary11, sizeof(salary11), 0);

		salary2 = lenders[i].credit.get_salary2();
		_itoa_s(salary2, salary22, 10);
		send(sserver, salary22, sizeof(salary22), 0);

		salary3 = lenders[i].credit.get_salary3();
		_itoa_s(salary3, salary33, 10);
		send(sserver, salary33, sizeof(salary33), 0);

		salary4 = lenders[i].credit.get_salary4();
		_itoa_s(salary4, salary44, 10);
		send(sserver, salary44, sizeof(salary44), 0);

	}
	delete[] lenders;


}

void Customers::checkCredit(SOCKET sserver, int numUser)
{
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	ifstream fin;
	int day, month, year;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();


	path_base = "approvedApplications.txt";
	int number_of_lenders = number_of_records(path_base, 15);
	Customers *lenders = new Customers[number_of_lenders];
	int  salary1, salary2, salary3, salary4;
	char  type[20], money[21], time[21];
	char pr[2];

	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_lenders; i++) {
			fin.getline(lenders[i].surname, sizeof(lenders[i].surname), '\n');
			fin.getline(lenders[i].name, sizeof(lenders[i].name), '\n');
			fin.getline(lenders[i].patronymic, sizeof(lenders[i].patronymic), '\n');
			fin >> day; lenders[i].date.set_day(day);
			fin >> month; lenders[i].date.set_month(month);
			fin >> year; lenders[i].date.set_year(year);
			fin.getline(pr, sizeof(pr), '\n');
			fin.getline(lenders[i].passportSeries, sizeof(lenders[i].passportSeries), '\n');
			fin.getline(lenders[i].passportNumber, sizeof(lenders[i].passportNumber), '\n');
			fin.getline(type, sizeof(type), '\n'); lenders[i].credit.set_type(type);
			fin.getline(money, sizeof(money), '\n');  lenders[i].credit.set_money(money);
			fin.getline(time, sizeof(time), '\n');  lenders[i].credit.set_time(time);
			fin >> salary1; lenders[i].credit.set_salary1(salary1);
			fin >> salary2; lenders[i].credit.set_salary2(salary2);
			fin >> salary3; lenders[i].credit.set_salary3(salary3);
			fin >> salary4; lenders[i].credit.set_salary4(salary4);
		}

	}
	fin.close();

	path_base = "applications.txt";
	int number_of_app = number_of_records(path_base, 15);
	Customers *applicants;
	applicants = new Customers[number_of_app];
	fin.open(path_base);

	char  type_ch[20], money_ch[21], time_ch[21];

	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_app; i++) {
			fin.getline(applicants[i].surname, sizeof(applicants[i].surname), '\n');
			fin.getline(applicants[i].name, sizeof(applicants[i].name), '\n');
			fin.getline(applicants[i].patronymic, sizeof(applicants[i].patronymic), '\n');
			fin >> day; applicants[i].date.set_day(day);
			fin >> month; applicants[i].date.set_month(month);
			fin >> year; applicants[i].date.set_year(year);
			fin.getline(pr, sizeof(pr), '\n');
			fin.getline(applicants[i].passportSeries, sizeof(applicants[i].passportSeries), '\n');
			fin.getline(applicants[i].passportNumber, sizeof(applicants[i].passportNumber), '\n');
			fin.getline(type, sizeof(type), '\n'); applicants[i].credit.set_type(type);
			fin.getline(money, sizeof(money), '\n');  applicants[i].credit.set_money(money);
			fin.getline(time, sizeof(time), '\n');  applicants[i].credit.set_time(time);
			fin >> salary1; applicants[i].credit.set_salary1(salary1);
			fin >> salary2; applicants[i].credit.set_salary2(salary2);
			fin >> salary3; applicants[i].credit.set_salary3(salary3);
			fin >> salary4; applicants[i].credit.set_salary4(salary4);
		}

	}
	fin.close();

	char msg[5];
	int check=0;
	for (int i = 0; i < number_of_lenders; i++) {
		if (strcmp(lenders[i].surname, customers[numUser].surname) == 0 && strcmp(lenders[i].name, customers[numUser].name) == 0 && strcmp(lenders[i].passportSeries, customers[numUser].passportSeries) == 0 && strcmp(lenders[i].passportNumber, customers[numUser].passportNumber) == 0) {
			strcpy(type, lenders[i].credit.get_type()); send(sserver, type, sizeof(type), 0);
			strcpy(money, lenders[i].credit.get_money()); send(sserver, money, sizeof(money), 0);
			strcpy(time, lenders[i].credit.get_time()); send(sserver, time, sizeof(time), 0);
			check = 1;
			_itoa_s(check, msg, 10);
			send(sserver, msg, sizeof(msg), 0);
		}
	}

	for (int i = 0; i < number_of_app; i++) {
		if (strcmp(applicants[i].surname, customers[numUser].surname) == 0 && strcmp(applicants[i].name, customers[numUser].name) == 0 && strcmp(applicants[i].passportSeries, customers[numUser].passportSeries) == 0 && strcmp(applicants[i].passportNumber, customers[numUser].passportNumber) == 0) {
			strcpy(type, applicants[i].credit.get_type()); send(sserver, type, sizeof(type), 0);
			strcpy(money, applicants[i].credit.get_money()); send(sserver, money, sizeof(money), 0);
			strcpy(time, applicants[i].credit.get_time()); send(sserver, time, sizeof(time), 0);
			check = 2;
			_itoa_s(check, msg, 10);
			send(sserver, msg, sizeof(msg), 0);
		}
	}

	if (check == 0) {
		_itoa_s(check, msg, 10);
		send(sserver, msg, sizeof(msg), 0);
	}


}


void Customers::salary(SOCKET sserver, int numUser) {
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	ifstream fin;
	int day, month, year;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();


	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	for (int i = 0; i < number_of_customers; i++)
	{
		send(sserver, customers[i].surname, sizeof(customers[i].surname), 0);
		send(sserver, customers[i].name, sizeof(customers[i].name), 0);
		send(sserver, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
		day = customers[i].date.get_day();
		_itoa_s(day, ch_day, 10);
		send(sserver, ch_day, sizeof(ch_day), 0);

		month = customers[i].date.get_month();
		_itoa_s(month, ch_month, 10);
		send(sserver, ch_month, sizeof(ch_month), 0);

		year = customers[i].date.get_year();
		_itoa_s(year, ch_year, 10);
		send(sserver, ch_year, sizeof(ch_year), 0);

		send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
		send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);

		_itoa_s(customers[i].accountNumber, acc, 10);
		send(sserver, acc, sizeof(acc), 0);

		_itoa_s(customers[i].cash, money, 10);
		send(sserver, money, sizeof(money), 0);
	}
	char msg_g[10];
	recv(sserver, msg_g, sizeof(msg_g), 0);
	int amountMoney = atoi(msg_g);

	customers[numUser].cash = customers[numUser].cash + amountMoney;
	
	_itoa_s(customers[numUser].cash, money, 10);
	send(sserver, money, sizeof(money), 0);
	_itoa_s(customers[numUser].accountNumber, acc, 10);
	send(sserver, acc, sizeof(acc), 0);
	ofstream fout;
	fout.open(path_base, ios_base::trunc);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fout << customers[i].surname << endl;
			fout << customers[i].name << endl;
			fout << customers[i].patronymic << endl;
			day = customers[i].date.get_day(); fout << day << endl;
			month = customers[i].date.get_month(); fout << month << endl;
			year = customers[i].date.get_year(); fout << year << endl;
			fout << customers[i].passportSeries << endl;
			fout << customers[i].passportNumber << endl;
			fout << customers[i].accountNumber << endl;
			fout << customers[i].cash << endl;
		}
	}
	fout.close();
	

	
	counter++;
	delete[] customers;
}

void Customers::withdraw(SOCKET sserver, int numUser) {
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	ifstream fin;
	int day, month, year;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();

	char cash_msg[10];
	_itoa_s(customers[numUser].cash, cash_msg, 10);
	send(sserver, cash_msg, sizeof(cash_msg), 0);
	char msg[5];
	_itoa_s(number_of_customers, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	for (int i = 0; i < number_of_customers; i++)
	{
		send(sserver, customers[i].surname, sizeof(customers[i].surname), 0);
		send(sserver, customers[i].name, sizeof(customers[i].name), 0);
		send(sserver, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
		day = customers[i].date.get_day();
		_itoa_s(day, ch_day, 10);
		send(sserver, ch_day, sizeof(ch_day), 0);

		month = customers[i].date.get_month();
		_itoa_s(month, ch_month, 10);
		send(sserver, ch_month, sizeof(ch_month), 0);

		year = customers[i].date.get_year();
		_itoa_s(year, ch_year, 10);
		send(sserver, ch_year, sizeof(ch_year), 0);

		send(sserver, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
		send(sserver, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);

		_itoa_s(customers[i].accountNumber, acc, 10);
		send(sserver, acc, sizeof(acc), 0);

		_itoa_s(customers[i].cash, money, 10);
		send(sserver, money, sizeof(money), 0);
	}


	char msg_g[10];
	recv(sserver, msg_g, sizeof(msg_g), 0);
	int amountMoney = atoi(msg_g);
		customers[numUser].cash = customers[numUser].cash - amountMoney;

		_itoa_s(customers[numUser].cash, money, 10);
		send(sserver, money, sizeof(money), 0);
		_itoa_s(customers[numUser].accountNumber, acc, 10);
		send(sserver, acc, sizeof(acc), 0);
		ofstream fout;
		fout.open(path_base, ios_base::trunc);
		if (!fout.is_open()) {
			cout << "Ошибка открытия файла." << endl;
		}
		else {
			for (int i = 0; i < number_of_customers; i++) {
				fout << customers[i].surname << endl;
				fout << customers[i].name << endl;
				fout << customers[i].patronymic << endl;
				day = customers[i].date.get_day(); fout << day << endl;
				month = customers[i].date.get_month(); fout << month << endl;
				year = customers[i].date.get_year(); fout << year << endl;
				fout << customers[i].passportSeries << endl;
				fout << customers[i].passportNumber << endl;
				fout << customers[i].accountNumber << endl;
				fout << customers[i].cash << endl;
			}
		}
		fout.close();


		counter++;
	
    
	delete[] customers;

}

void Customers::print(SOCKET sserver, int numUser) {
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	ifstream fin;
	int day, month, year;
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> customers[i].surname;
			fin >> customers[i].name;
			fin >> customers[i].patronymic;
			fin >> day; customers[i].date.set_day(day);
			fin >> month; customers[i].date.set_month(month);
			fin >> year; customers[i].date.set_year(year);
			fin >> customers[i].passportSeries;
			fin >> customers[i].passportNumber;
			fin >> customers[i].accountNumber;
			fin >> customers[i].cash;
		}
	}
	fin.close();
	
	char msg[10], msg_cash[10];
	_itoa_s(customers[numUser].accountNumber, msg, 10);
	send(sserver, msg, sizeof(msg), 0);
	_itoa_s(customers[numUser].cash, msg_cash, 10);
	send(sserver, msg_cash, sizeof(msg_cash), 0);

}