#include "User.h"
#include "Customers.h"
#include "CW.h"



void User::authorization(SOCKET sserver)
{
	string path = "users.txt";
	ifstream fin;
	int check=0;
	fin.open(path, ostream::in);
	int number_of_users = Checks::number_of_records(path, 2);
	char  login_check[20];
	char password_check[20];
	int msg;
	char msg_s[5];
	char msgCheck[5];
	_itoa_s(number_of_users, msg_s, 10);
	send(sserver, msg_s, 5, 0);
	

		if (!fin.is_open() || number_of_users == 0)
		{
			cout << "Ошибка: невозможно открыть файл." << endl;		
			if (number_of_users == 0) {
				cout << "Ошибка: нет зарегистрированных клиентов." << endl;
			}

		}
		else {
			User *users;
			users = new User[number_of_users];
		

				recv(sserver, login_check, sizeof(login_check), 0);
				recv(sserver, password_check, sizeof(password_check), 0);

				for (int i = 0; i < number_of_users; i++) {
					fin >> users[i].login;
					fin >> users[i].password;
				}


				for (int i = 0; i < number_of_users; i++) {
					
					if (strcmp(users[i].login, login_check) == 0) {
						
						for (int i = 0; i < number_of_users; i++)
						{
							for (int j = 0; j < strlen(users[i].password); j++) users[i].password[j] = users[i].password[j] - 5;
						}

						if (strcmp(users[i].password, password_check) == 0) {
							cout << '\n';
							/*cout << "Вход от имени клиента." << endl;*/
							check = 2;
							_itoa_s(check, msgCheck, 10);
							send(sserver, msgCheck, 5, 0);
							userMenu(i,sserver);
						
						}
							
						
						

					}
				}
				if (check != 2) {
					_itoa_s(check, msgCheck, 10);
					send(sserver, msgCheck, 5, 0);
				}
				delete[] users;
		}
		fin.close();

	

}

void User::registration(SOCKET sserver)
{
	char login_check[20];
	char password_check[20];
	recv(sserver, login_check, sizeof(login_check), 0);
	recv(sserver, password_check, sizeof(password_check), 0);
	string path = "users.txt";
	int number_of_users = number_of_records(path, 2);
	int c=0; char msgCheck[5];
	
	Customers customer;

	if (number_of_users == 0) {
		ofstream fout;
		fout.open(path, ostream::app);
		if (!fout.is_open()) {
			cout << "Ошибка открытия файла." << endl;
		}
		else {
			c = 2;
			_itoa_s(c, msgCheck, 10);
			send(sserver, msgCheck, sizeof(msgCheck), 0);
			for (int j = 0; j < strlen(password_check); j++) password_check[j] = password_check[j] + 5;
			fout << login_check << endl;
			fout << password_check << endl;
			/*cout << "Регистрация клиента" << endl;*/
			customer.addCustomer(sserver);
		}
		
	}
	else {
		User *users;
		users = new User[number_of_users];
		ifstream fin;
		fin.open(path, ostream::in);
		if (!fin.is_open())
		{
			cout << "Ошибка открытия файла." << endl;
		}
		else {
			for (int i = 0; i < number_of_users; i++) {
				fin >> users[i].login;
				fin >> users[i].password;
				if (strcmp(login_check, users[i].login) == 0) {
					c = 1;
					_itoa_s(c, msgCheck, 10);
					send(sserver, msgCheck, sizeof(msgCheck), 0);
				}
			}
			
		}
		fin.close();
		delete[] users;
	}
	if (c == 0) {
		ofstream fout;
		fout.open(path, ostream::app);
		if (!fout.is_open()) {
			cout << "Ошибка открытия файла." << endl;
		}
		else {
			_itoa_s(c, msgCheck, 10);
			send(sserver, msgCheck, sizeof(msgCheck), 0);
			for (int j = 0; j < strlen(password_check); j++) password_check[j] = password_check[j] + 5;
			fout << login_check << endl;
			fout << password_check << endl;
			/*cout << "Регистрация клиента" << endl;*/
			customer.addCustomer(sserver);
		}
		fout.close();
	}
	
}

void User::deleteUser(int number)
{
	string path = "users.txt";
	int number_of_users = number_of_records(path, 2);
	User *users;
	users = new User[number_of_users];
	ifstream fin;
	fin.open(path, ostream::in);
	if (!fin.is_open())
	{
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		for (int i = 0; i < number_of_users; i++) {
			fin >> users[i].login;
			fin >> users[i].password;
		}
	}
	fin.close();

	ofstream fout;
	fout.open(path, ios_base::trunc);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		if (number_of_users != number) {
			for (int u = number - 1; u < number_of_users - 1; u++)
				users[u] = users[u + 1];
		}
		for (int i = 0; i < number_of_users - 1; i++) {
			fout << users[i].login << endl;
			fout << users[i].password << endl;
		}
	}
	fout.close();
	delete[] users;
}


void User::userMenu(int numUser, SOCKET sserver) {
	
	char surname[20];
	char patronymic[20];
	char name[20];
	char passportSeries[5];
	char passportNumber[8];
	int accountNumber;
	int cash,day,month,year;
	char msgChoice[5];
	setlocale(LC_ALL, "rus");
	ifstream fin;
	string path_base = "customers.txt";
	int number_of_customers = number_of_records(path_base, 10);
	Customers *customers;
	customers = new Customers[number_of_customers];
	fin.open(path_base);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла." << endl;

	}
	else {
		for (int i = 0; i < number_of_customers; i++) {
			fin >> surname; customers[i].set_surname(surname);
			fin >> name;  customers[i].set_name(name);
			fin >> patronymic; customers[i].set_patronymic(patronymic);
			fin >> day;
			fin >> month;
			fin >> year; 
			fin >> passportSeries; customers[i].set_passportSeries(passportSeries);
			fin >> passportNumber; customers[i].set_passportNumber(passportNumber);
			fin >> accountNumber; customers[i].set_accountNumber(accountNumber);
			fin >> cash; customers[i].set_cash(cash);
		}
	}
	fin.close();
	int choice;
	int check = 0;
	while (check == 0)
	{
		customers[numUser].print(sserver, numUser);
		recv(sserver, msgChoice, sizeof(msgChoice), 0);
		choice = atoi(msgChoice);

		switch (choice)
		{
		case 1:
		{
			customers[numUser].transfer(sserver, numUser);
			break;
		}; 

		case 2:
		{   customers[numUser].salary(sserver, numUser);
			break;
		};
		case 3:
		{   customers[numUser].withdraw(sserver, numUser);
			break;
		}; 
		case 4:
		{
			
			break;
		};
		case 5:
		{
			customers[numUser].applyForALoan(sserver, numUser);
			break;
		}
		case 6: {
			customers[numUser].checkCredit(sserver, numUser);
			break;
		}
		case 7: {
			check = 5;
			break;
		}
		}
	}

}


