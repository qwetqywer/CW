#include "Customers.h"
#include "CW.h"
#include <vector>


int counter = 0;
vector<Customers> operation;


void Customers::addCustomer(SOCKET sclient)
{
	char msg[5]; int check = 0, check1 = 0;
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	Customers *customers;
	customers = new Customers[number_of_customers];
	for (int i = 0; i < number_of_customers; i++) {
		recv(sclient, customers[i].passportSeries, sizeof(customers[i].passportSeries), 0);
		recv(sclient, customers[i].passportNumber, sizeof(customers[i].passportNumber), 0);
	}

	int day_d, month_m, year_y;
	cout << "\n������� �������: ";
again1:
	cin >> surname;
	if (!check_string(surname)) {
		goto again1;
	}

	cout << "\n������� ���: ";
again2:
	cin >> name;
	if (!check_string(name)) {
		goto again2;
	}

	cout << "\n������� ��������: ";
again3:
	cin >> patronymic;
	if (!check_string(patronymic)) {
		goto again3;
	}
	
	cout << "\n���� ��������" << endl;
	cout << "\n������� ����: ";
	day_d = Check_day();
	cout << "\n������� �����: ";
	month_m = Check_month();
	cout << "\n������� ���: ";
	year_y = Check_year();

	while (check == 0) {
		check1 = 0;
		cout << "\n������� ����� � ����� ��������:" << endl;
		cout << "\n�����:";
	again4:
		cin >> passportSeries;
		if (!checkPassport(passportSeries)) {
			goto again4;
		}
		cout << "\n�����:";
	again5:
		cin >> passportNumber;
		if (!checkPassportNumber(passportNumber)) {
			goto again5;
		}
		for (int i = 0; i < number_of_customers; i++) {
			if (strcmp(passportSeries, customers[i].passportSeries) == 0 && strcmp(passportNumber, customers[i].passportNumber) == 0) {
				cout << "������ �������� ������ ���� �����������." << endl;
				check1++;
			}
		}
		if (check1 == 0) {
			check = 1;
		}
	}

	
	char ch_day[5], ch_month[5], ch_year[5];
	_itoa_s(day_d, ch_day, 10);
	_itoa_s(month_m, ch_month, 10);
	_itoa_s(year_y, ch_year, 10);

	send(sclient, surname, sizeof(surname), 0);
	send(sclient, name, sizeof(name), 0);
	send(sclient, patronymic, sizeof(patronymic), 0);
	send(sclient, ch_day, sizeof(ch_day), 0);
	send(sclient, ch_month, sizeof(ch_month), 0);
	send(sclient, ch_year, sizeof(ch_year), 0);
	send(sclient, passportSeries, sizeof(passportSeries), 0);
	send(sclient, passportNumber, sizeof(passportNumber), 0);

	char acc[10];
	recv(sclient, acc, sizeof(acc), 0);
	accountNumber = atoi(acc);
	system("cls");
	cout << "\t\t\t����������� � �������� ������������!" << endl;
	cout << "����� ������ �����: " << accountNumber << endl;
	system("pause");
}

void Customers::showAll(SOCKET sclient)
{
	char msg[5];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	Customers *customers;
	float amountMoney;
	customers = new Customers[number_of_customers];
	char ch_day[5], ch_month[5], ch_year[5],  acc[10], money[10];
	int day, month, year, accNumber;
	
	if (number_of_customers == 0) {
		cout << "��� ������������������ ��������." << endl;
		system("pause");
	}
	else {
	
		
		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "|" << setw(76) << "������ ��������" << setw(74) << "|" << endl;
		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "|" << setw(5)  << "|" <<  setw(22) << "|" << setw(20) << "|" << setw(20)  << "|" << setw(19)<< "���� ��������"<<setw(8)<<"|"  << setw(22)  << "���������� ������" << setw(5)  << "|" <<setw(19)<<"|"<<setw(10)<<"|"<< endl;
		cout << "|" << setw(3) << "�" << setw(2) << "|" << setw(13) << "�������" << setw(9) << "|" << setw(11) << "���" << setw(9) << "|" << setw(13) << "��������" << setw(7) << "|"<<"--------------------------|--------------------------|" << setw(15) <<"����� �����" <<setw(4)<<"|"<<setw(8)<<"����($)"<<setw(2)<<"|"<< endl;
		cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(5) << "����" << setw(3) << "|" << setw(7) << "�����" << setw(3) << "|" << setw(6) << "���" << setw(3) << "|" << setw(8) << "�����" << setw(3) << "|" << setw(10) << "�����" << setw(6) << "|"<<setw(19)<<"|"<<setw(10)<<"|"<< endl;
		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

		for (int i = 0; i < number_of_customers; i++) {
			recv(sclient, customers[i].surname, sizeof(customers[i].surname), 0); 
			recv(sclient, customers[i].name, sizeof(customers[i].name), 0); 
			recv(sclient, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
			recv(sclient, ch_day, sizeof(ch_day), 0);
			recv(sclient, ch_month, sizeof(ch_month), 0);
			recv(sclient, ch_year, sizeof(ch_year), 0);
			day = atoi(ch_day); customers[i].date.set_day(day);
			month = atoi(ch_month); customers[i].date.set_month(month);
			year = atoi(ch_year); customers[i].date.set_year(year);
			recv(sclient, customers[i].passportSeries, sizeof(passportSeries), 0);
			recv(sclient, customers[i].passportNumber, sizeof(passportNumber), 0);
			recv(sclient, acc, sizeof(acc), 0);
			recv(sclient, money, sizeof(money), 0);
			accNumber = atoi(acc); customers[i].set_accountNumber(accNumber);
			amountMoney = atoi(money); customers[i].set_cash(amountMoney);
			customers[i].showOne(i + 1);
		}
		system("pause");
	}
	delete[] customers;
	
}

void Customers::showOne(int counter) {
	cout << "|" << setw(3) << counter << setw(2) << "|" << setw(13) << surname << setw(9) << "|" << setw(11) << name << setw(9) << "|" << setw(13) << patronymic << setw(7) << "|" << setw(5) << date.get_day() << setw(3) << "|" << setw(7) << date.get_month() << setw(3) << "|" << setw(6) << date.get_year() << setw(3) << "|" << setw(8) << passportSeries << setw(3) << "|" << setw(10) << passportNumber << setw(6) << "|" << setw(15) << accountNumber << setw(4) << "|" << setw(8) << cash << setw(2) << "|" << endl;
	cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
}

void Customers::showOneCredit(int counter)
{
	
	cout << "|" << setw(3) << counter << setw(2) << "|" << setw(10) << surname << setw(6) << "|" << setw(10) << name << setw(8) << "|" << setw(13) << patronymic << setw(5) << "|" << setw(5) << date.get_day() << setw(3) << "|" << setw(7) << date.get_month() << setw(3) << "|" << setw(6) << date.get_year() << setw(3) << "|" << setw(8) << passportSeries << setw(3) << "|" << setw(10) << passportNumber << setw(6) << "|" << setw(17) << credit.get_type() << setw(2) << "|" << setw(20) << credit.get_money() << setw(2) << "|" << setw(20) << credit.get_time() << setw(2) << "|" << endl;
	cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

}

void Customers::deleteCustomer(SOCKET sclient) {
	int choice=0;
	char msg[5];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	char msgChoice[5];
	showAll(sclient);
	cout << "����� ������ �� ������ �������?" << endl;
	choice = CheckNumber(choice, number_of_customers);
	_itoa_s(choice, msg, 10);
	send(sclient, msg, sizeof(msg), 0);

}

void Customers::editCustomer(SOCKET sclient) {
	int choice = 0, day, month, year;
	char msg[5];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	char msgChoice[5];
	showAll(sclient);
	cout << "����� ������ �� ������ �������������?" << endl;
	choice = CheckNumber(choice, number_of_customers);
	_itoa_s(choice, msg, 10);
	send(sclient, msg, sizeof(msg), 0);
	char ch_day[5], ch_month[5], ch_year[5];
	Customers customer;
	recv(sclient, customer.surname, sizeof(customer.surname), 0);
	recv(sclient, customer.name, sizeof(customer.name), 0);
	recv(sclient, customer.patronymic, sizeof(customer.patronymic), 0);
	recv(sclient, ch_day, sizeof(ch_day), 0);
	recv(sclient, ch_month, sizeof(ch_month), 0);
	recv(sclient, ch_year, sizeof(ch_year), 0);
	day = atoi(ch_day); month = atoi(ch_month); year = atoi(ch_year);
	customer.date.set_day(day);	customer.date.set_month(month);	customer.date.set_year(year);
	recv(sclient, customer.passportSeries, sizeof(customer.passportSeries), 0);
	recv(sclient, customer.passportNumber, sizeof(customer.passportNumber), 0);
	
	customer.editMenu();

	day = customer.date.get_day();
	month = customer.date.get_month();
	year = customer.date.get_year();
	_itoa_s(day, ch_day, 10);
	_itoa_s(month, ch_month, 10);
	_itoa_s(year, ch_year, 10);

	send(sclient, customer.surname, sizeof(customer.surname), 0);
	send(sclient, customer.name, sizeof(customer.name), 0);
	send(sclient, customer.patronymic, sizeof(customer.patronymic), 0);
	send(sclient, ch_day, sizeof(ch_day), 0);
	send(sclient, ch_month, sizeof(ch_month), 0);
	send(sclient, ch_year, sizeof(ch_year), 0);
	send(sclient, customer.passportSeries, sizeof(customer.passportSeries), 0);
	send(sclient, customer.passportNumber, sizeof(customer.passportNumber), 0);


}
void Customers::editMenu() {
	int check = 0, day, month, year;
	while (check == 0) {
		system("cls");
		cout << "1. ������������� ���" << endl
			<< "2. ������������� ���� ��������" << endl
			<< "3. ������������� ������ ��������" << endl
			<< "4. ��������� �����" << endl;
		int choice = 1;
		choice = Checks::CheckNumber(choice, 4);
		switch (choice) {

		case 1: {
			cout << "\n������� �������: ";
		again1:
			cin >> surname;
			if (!check_string(surname)) {
				goto again1;
			}

			cout << "\n������� ���: ";
		again2:
			cin >> name;
			if (!check_string(name)) {
				goto again2;
			}

			cout << "\n������� ��������: ";
		again3:
			cin >> patronymic;
			if (!check_string(patronymic)) {
				goto again3;
			}
			break;
		}
		case 2:
		{	
			cout << "\n���� ��������" << endl;
		    cout << "\n������� ����: ";
		    day = Check_day();
		    cout << "\n������� �����: ";
		    month = Check_month();
		    cout << "\n������� ���: ";
		    year = Check_year();
			date.set_day(day); date.set_month(month); date.set_year(year);

			break;
		}
		case 3: {
			cout << "\n������� ����� � ����� ��������:" << endl;
			cout << "\n�����:";
			cin >> passportSeries;
			cout << "\n�����:";
			cin >> passportNumber;
			break;
		}
		case 4: {
			check = 5;
			break;
		}
		}
	}
}

void Customers::searchMenu(SOCKET sclient) {
	char msgChoice[5];
	int choice = 1;
	int check = 0;
	while (check==0) {
		system("cls");
		cout << "1.����� �� ���" << endl;
		cout << "2.����� �� ���������� ������" << endl;
		cout << "3.����� �� ������ �����" << endl;
		cout << "4.���������� �������� � ���������� �������" << endl;
		cout << "5.��������� �����" << endl;	
		choice = Checks::CheckNumber(choice, 5);	
		_itoa_s(choice, msgChoice, 10);
		send(sclient, msgChoice, 5, 0);

		switch (choice)
		{
		case 1: {
			searchSNP(sclient);
			break;
		}
		case 2: {
			searchPassport(sclient);
			break;
		}
		case 3: {
			searchAccountNumber(sclient);
			break;
		}
		case 4: {
			sortingCustomers(sclient);
			break;
		}
		case 5: {
			check = 5;
			break;
		}
		default:system("cls"); cout << "������ ������� �����������." << endl;
		}
	}
}

void Customers::searchSNP(SOCKET sclient) {
	char msg[5];
	char surname_s[20];
	char patronymic_p[20];
	char name_n[20];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	if (number_of_customers==0) {
		cout << "��� ������������������ ��������." << endl;
		system("pause");
	}
	else {
		cout << "\n������� �������: ";
	again1:
		cin >> surname_s;
		if (!check_string(surname_s)) {
			goto again1;
		}
		cout << "\n������� ���: ";
	again2:
		cin >> name_n;
		if (!check_string(name_n)) {
			goto again2;
		}
		cout << "\n������� ��������: ";
	again3:
		cin >> patronymic_p;
		if (!check_string(patronymic_p)) {
			goto again3;
		}
		send(sclient, surname_s, sizeof(surname_s), 0);
		send(sclient, name_n, sizeof(name_n), 0);
		send(sclient, patronymic_p, sizeof(patronymic_p), 0);
		recv(sclient, msg, sizeof(msg), 0);
		int counter = atoi(msg);
		if (counter == 0) {
			cout << "�� �������." << endl;
			system("pause");
		}
		else {

			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			cout << "|" << setw(76) << "������ ��������" << setw(74) << "|" << endl;
			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(19) << "���� ��������" << setw(8) << "|" << setw(22) << "���������� ������" << setw(5) << "|" << setw(19) << "|" << setw(10) << "|" << endl;
			cout << "|" << setw(3) << "�" << setw(2) << "|" << setw(13) << "�������" << setw(9) << "|" << setw(11) << "���" << setw(9) << "|" << setw(13) << "��������" << setw(7) << "|" << "--------------------------|--------------------------|" << setw(15) << "����� �����" << setw(4) << "|" << setw(8) << "����" << setw(2) << "|" << endl;
			cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(5) << "����" << setw(3) << "|" << setw(7) << "�����" << setw(3) << "|" << setw(6) << "���" << setw(3) << "|" << setw(8) << "�����" << setw(3) << "|" << setw(10) << "�����" << setw(6) << "|" << setw(19) << "|" << setw(10) << "|" << endl;
			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

			Customers *customers;
			customers = new Customers[counter];
			char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
			int day, month, year, accNumber, amountMoney;
			for (int i = 0; i < counter; i++) {
				recv(sclient, customers[i].surname, sizeof(customers[i].surname), 0);
				recv(sclient, customers[i].name, sizeof(customers[i].name), 0);
				recv(sclient, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
				recv(sclient, ch_day, sizeof(ch_day), 0);
				recv(sclient, ch_month, sizeof(ch_month), 0);
				recv(sclient, ch_year, sizeof(ch_year), 0);
				day = atoi(ch_day); customers[i].date.set_day(day);
				month = atoi(ch_month); customers[i].date.set_month(month);
				year = atoi(ch_year); customers[i].date.set_year(year);
				recv(sclient, customers[i].passportSeries, sizeof(passportSeries), 0);
				recv(sclient, customers[i].passportNumber, sizeof(passportNumber), 0);
				recv(sclient, acc, sizeof(acc), 0);
				recv(sclient, money, sizeof(money), 0);
				accNumber = atoi(acc); customers[i].set_accountNumber(accNumber);
				amountMoney = atoi(money); customers[i].set_cash(amountMoney);
				customers[i].showOne(i + 1);
			}
			system("pause");
		}
	}


}

void Customers::searchPassport(SOCKET sclient) {
	char msg[5];
	char passportSeries_p[5];
	char passportNumber_p[8];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	if (number_of_customers == 0) {
		cout << "��� ������������������ ��������." << endl;
		system("pause");
	}
	else {
		cout << "\n������� ����� ��������: ";
	again1:
		cin >> passportSeries_p;
		if (!check_string(passportSeries_p)) {
			goto again1;
		}
		cout << "\n������� ����� ��������: ";
		cin >> passportNumber_p;
		
		send(sclient, passportSeries_p, sizeof(passportSeries_p), 0);
		send(sclient, passportNumber_p, sizeof(passportNumber_p), 0);
		
		recv(sclient, msg, sizeof(msg), 0);
		int counter = atoi(msg);
		if (counter == 0) {
			cout << "�� �������." << endl;
			system("pause");
		}
		else {

			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			cout << "|" << setw(76) << "������ ��������" << setw(74) << "|" << endl;
			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(19) << "���� ��������" << setw(8) << "|" << setw(22) << "���������� ������" << setw(5) << "|" << setw(19) << "|" << setw(10) << "|" << endl;
			cout << "|" << setw(3) << "�" << setw(2) << "|" << setw(13) << "�������" << setw(9) << "|" << setw(11) << "���" << setw(9) << "|" << setw(13) << "��������" << setw(7) << "|" << "--------------------------|--------------------------|" << setw(15) << "����� �����" << setw(4) << "|" << setw(8) << "����" << setw(2) << "|" << endl;
			cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(5) << "����" << setw(3) << "|" << setw(7) << "�����" << setw(3) << "|" << setw(6) << "���" << setw(3) << "|" << setw(8) << "�����" << setw(3) << "|" << setw(10) << "�����" << setw(6) << "|" << setw(19) << "|" << setw(10) << "|" << endl;
			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

			Customers *customers;
			customers = new Customers[counter];
			char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
			int day, month, year, accNumber, amountMoney;
			for (int i = 0; i < counter; i++) {
				recv(sclient, customers[i].surname, sizeof(customers[i].surname), 0);
				recv(sclient, customers[i].name, sizeof(customers[i].name), 0);
				recv(sclient, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
				recv(sclient, ch_day, sizeof(ch_day), 0);
				recv(sclient, ch_month, sizeof(ch_month), 0);
				recv(sclient, ch_year, sizeof(ch_year), 0);
				day = atoi(ch_day); customers[i].date.set_day(day);
				month = atoi(ch_month); customers[i].date.set_month(month);
				year = atoi(ch_year); customers[i].date.set_year(year);
				recv(sclient, customers[i].passportSeries, sizeof(passportSeries), 0);
				recv(sclient, customers[i].passportNumber, sizeof(passportNumber), 0);
				recv(sclient, acc, sizeof(acc), 0);
				recv(sclient, money, sizeof(money), 0);
				accNumber = atoi(acc); customers[i].set_accountNumber(accNumber);
				amountMoney = atoi(money); customers[i].set_cash(amountMoney);
				customers[i].showOne(i + 1);
			}
			system("pause");
		}
	}
}

void Customers::searchAccountNumber(SOCKET sclient) {
	char msg[5], acc[10];
	int accNumber;
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	if (number_of_customers == 0) {
		cout << "��� ������������������ ��������." << endl;
		system("pause");
	}
	else {
		cout << "\n������� ����� �����: ";
		accNumber = Check_acc_number();
		_itoa_s(accNumber, acc, 10);
		send(sclient, acc, sizeof(acc), 0);
		

		recv(sclient, msg, sizeof(msg), 0);
		int counter = atoi(msg);
		if (counter == 0) {
			cout << "�� �������." << endl;
			system("pause");
		}
		else {
			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			cout << "|" << setw(76) << "������ ��������" << setw(74) << "|" << endl;
			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(19) << "���� ��������" << setw(8) << "|" << setw(22) << "���������� ������" << setw(5) << "|" << setw(19) << "|" << setw(10) << "|" << endl;
			cout << "|" << setw(3) << "�" << setw(2) << "|" << setw(13) << "�������" << setw(9) << "|" << setw(11) << "���" << setw(9) << "|" << setw(13) << "��������" << setw(7) << "|" << "--------------------------|--------------------------|" << setw(15) << "����� �����" << setw(4) << "|" << setw(8) << "����" << setw(2) << "|" << endl;
			cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(5) << "����" << setw(3) << "|" << setw(7) << "�����" << setw(3) << "|" << setw(6) << "���" << setw(3) << "|" << setw(8) << "�����" << setw(3) << "|" << setw(10) << "�����" << setw(6) << "|" << setw(19) << "|" << setw(10) << "|" << endl;
			cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

			Customers *customers;
			customers = new Customers[counter];
			char ch_day[5], ch_month[5], ch_year[5],  money[10];
			int day, month, year, accNumber, amountMoney;
			for (int i = 0; i < counter; i++) {
				recv(sclient, customers[i].surname, sizeof(customers[i].surname), 0);
				recv(sclient, customers[i].name, sizeof(customers[i].name), 0);
				recv(sclient, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
				recv(sclient, ch_day, sizeof(ch_day), 0);
				recv(sclient, ch_month, sizeof(ch_month), 0);
				recv(sclient, ch_year, sizeof(ch_year), 0);
				day = atoi(ch_day); customers[i].date.set_day(day);
				month = atoi(ch_month); customers[i].date.set_month(month);
				year = atoi(ch_year); customers[i].date.set_year(year);
				recv(sclient, customers[i].passportSeries, sizeof(passportSeries), 0);
				recv(sclient, customers[i].passportNumber, sizeof(passportNumber), 0);
				recv(sclient, acc, sizeof(acc), 0);
				recv(sclient, money, sizeof(money), 0);
				accNumber = atoi(acc); customers[i].set_accountNumber(accNumber);
				amountMoney = atoi(money); customers[i].set_cash(amountMoney);
				customers[i].showOne(i + 1);
			}
			system("pause");
		}
	}
}

void Customers::sortingCustomers(SOCKET sclient)
{
	char msg[5], acc[10];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	if (number_of_customers == 0) {
		cout << "��� ������������������ ��������." << endl;
		system("pause");
	}
	else {
		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "|" << setw(76) << "������ ��������" << setw(74) << "|" << endl;
		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(19) << "���� ��������" << setw(8) << "|" << setw(22) << "���������� ������" << setw(5) << "|" << setw(19) << "|" << setw(10) << "|" << endl;
		cout << "|" << setw(3) << "�" << setw(2) << "|" << setw(13) << "�������" << setw(9) << "|" << setw(11) << "���" << setw(9) << "|" << setw(13) << "��������" << setw(7) << "|" << "--------------------------|--------------------------|" << setw(15) << "����� �����" << setw(4) << "|" << setw(8) << "����" << setw(2) << "|" << endl;
		cout << "|" << setw(5) << "|" << setw(22) << "|" << setw(20) << "|" << setw(20) << "|" << setw(5) << "����" << setw(3) << "|" << setw(7) << "�����" << setw(3) << "|" << setw(6) << "���" << setw(3) << "|" << setw(8) << "�����" << setw(3) << "|" << setw(10) << "�����" << setw(6) << "|" << setw(19) << "|" << setw(10) << "|" << endl;
		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

			Customers *customers;
			customers = new Customers[number_of_customers];
			char ch_day[5], ch_month[5], ch_year[5], money[10];
			int day, month, year, accNumber, amountMoney;
			for (int i = 0; i < number_of_customers; i++) {
				recv(sclient, customers[i].surname, sizeof(customers[i].surname), 0);
				recv(sclient, customers[i].name, sizeof(customers[i].name), 0);
				recv(sclient, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
				recv(sclient, ch_day, sizeof(ch_day), 0);
				recv(sclient, ch_month, sizeof(ch_month), 0);
				recv(sclient, ch_year, sizeof(ch_year), 0);
				day = atoi(ch_day); customers[i].date.set_day(day);
				month = atoi(ch_month); customers[i].date.set_month(month);
				year = atoi(ch_year); customers[i].date.set_year(year);
				recv(sclient, customers[i].passportSeries, sizeof(passportSeries), 0);
				recv(sclient, customers[i].passportNumber, sizeof(passportNumber), 0);
				recv(sclient, acc, sizeof(acc), 0);
				recv(sclient, money, sizeof(money), 0);
				accNumber = atoi(acc); customers[i].set_accountNumber(accNumber);
				amountMoney = atoi(money); customers[i].set_cash(amountMoney);
				customers[i].showOne(i + 1);
			}
			system("pause");
		
	}

}

void Customers::transfer(SOCKET sclient) {
	char msg[5];
	char cash_msg[10];
	recv(sclient, cash_msg, sizeof(cash_msg), 0);
	float cashh = atoi(cash_msg);
	
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	Customers *customers;
	customers = new Customers[number_of_customers];
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	int day, month, year, accNumber, amountMoney, check = 0;
	for (int i = 0; i < number_of_customers; i++) {
		recv(sclient, customers[i].surname, sizeof(customers[i].surname), 0);
		recv(sclient, customers[i].name, sizeof(customers[i].name), 0);
		recv(sclient, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
		recv(sclient, ch_day, sizeof(ch_day), 0);
		recv(sclient, ch_month, sizeof(ch_month), 0);
		recv(sclient, ch_year, sizeof(ch_year), 0);
		day = atoi(ch_day); customers[i].date.set_day(day);
		month = atoi(ch_month); customers[i].date.set_month(month);
		year = atoi(ch_year); customers[i].date.set_year(year);
		recv(sclient, customers[i].passportSeries, sizeof(passportSeries), 0);
		recv(sclient, customers[i].passportNumber, sizeof(passportNumber), 0);
		recv(sclient, acc, sizeof(acc), 0);
		recv(sclient, money, sizeof(money), 0);
		accNumber = atoi(acc); customers[i].set_accountNumber(accNumber);
		amountMoney = atoi(money); customers[i].set_cash(amountMoney);
	}
	again1:
	cout << "������� ����� ����� ��� ��������:" << endl;
	accNumber = Check_acc_number();
	for (int i = 0; i < number_of_customers; i++) {
		if (accNumber == customers[i].accountNumber) {
			check++;
		}
	}
	if (check == 0) {
		cout << "����� � ����� ������� ���." << endl;
		goto again1;
	}
	cout << "������� ����� ����� ��� ��������:" << endl;
	while (!(cin >> amountMoney) || (cin.peek() != '\n') || amountMoney < 1 || amountMoney>cashh)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� ������\n";
	}

	char msg_g[10];
	_itoa_s(accNumber, msg_g, 10);
	send(sclient, msg_g, sizeof(msg_g), 0);
	_itoa_s(amountMoney, msg_g, 10);
	send(sclient, msg_g, sizeof(msg_g), 0);

		recv(sclient, money, sizeof(money), 0);
		int prevMoney = atoi(money);
		recv(sclient, acc, sizeof(acc), 0);
		int ourAcc = atoi(acc);
		delete[] customers;
		int num2 = 1;
		Customers cus;
		cus.set_ourAccountNumber(ourAcc);
		cus.set_accountNumber(accNumber);
		cus.set_numOperation(num2);
		cus.set_cash(amountMoney);
		cus.set_prevCash(prevMoney);
		operation.push_back(cus);

}

void Customers::history(SOCKET sclient)
{
	int i = 0;
	vector<Customers>::iterator it;
	for (it=operation.begin(); it!= operation.end(); it++)
	{
		cout << "�������� ����� " << i+1 << endl;
		if (it->numOperation == 3) cout << "�� ����� ���� ����� " << it->cash << "$" << endl;
		if (it->numOperation == 2) cout << "�� ���� ���� �������� " << it->cash << "$" << endl;
		if (it->numOperation == 1) cout << "�� ���� � ������� " << it->accountNumber << " ���� ���������� " << it->cash << "$" << endl;
		cout << "��������� ����� ����� ���� ��������" << endl;
		cout << "����� ������ �����: " << it->ourAccountNumber << endl;
		cout << "���� ($): " << it-> prevCash << endl;
		cout << endl;
		i++;
	}
	system("pause");

}

void Customers::applyForALoan(SOCKET sclient)
{
	cout << "�������� ��� �������:" << endl;
	cout << "1.���������������\n2.����������\n3.�� ������������\n4.����������������" << endl;
	int choice= 0;
	choice= CheckNumber(choice, 4);
	char msg_choice[5];
	_itoa_s(choice, msg_choice, 10);
	send(sclient, msg_choice, sizeof(msg_choice), 0);
	int money, time;
	if (choice == 1) {
		cout << "�������� c����:" << endl;
		cout << "1.�� 100� �� 1000�\n2.�� 1000� �� 3000�\n3.�� 3000� �� 5000�" << endl;
		money = CheckNumber(choice, 3);
		cout << "�������� ����:" << endl;
		cout << "1.�� 24 �������\n2.�� 48 �������\n3.�� 84 �������" << endl;
		time = CheckNumber(choice, 3);
	}
	if (choice == 2) {
		cout << "�������� c����:" << endl;
		cout << "1.�� 2500� �� 10000�\n2.�� 10000� �� 20000�\n3.�� 20000� �� 100000�" << endl;
		money = CheckNumber(choice, 3);
		cout << "�������� ����:" << endl;
		cout << "1.�� 60 �������\n2.�� 84 �������\n3.�� 120 �������" << endl;
		time = CheckNumber(choice, 3);
	}
	if (choice == 3) {
		cout << "������� c����:" << endl;
		while (!(cin >> money) || (cin.peek() != '\n') || money < 1)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ������� ������\n";

		}
		time = 10;
	}
	if (choice == 4) {
		cout << "�������� c����:" << endl;
		cout << "1.�� 500� �� 10000�\n2.�� 500� �� 15000�\n3.�� 1000� �� 25000�" << endl;
		money = CheckNumber(choice, 3);
		cout << "�������� ����:" << endl;
		cout << "1.�� 24 �� 48 �������\n2.48 �������\n3.�� 24 �� 60 �������" << endl;
		time = CheckNumber(choice, 3);
	}
	char msg_money[10],msg_time[10];
	_itoa_s(money, msg_money, 10);
	send(sclient, msg_money, sizeof(msg_money), 0);
	_itoa_s(time, msg_time, 10);
	send(sclient, msg_time, sizeof(msg_time), 0);
	int salary1, salary2, salary3, salary4;
	cout << "������������ ����� �� ����� ������� �� ��������� �������:" << endl;
	cout << "31.03.2020: ";
	while (!(cin >> salary1) || (cin.peek() != '\n'))
	{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ������� ������\n";

	}
	cout << "31.12.2019: ";
	while (!(cin >> salary2) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� ������\n";

	}
	cout << "31.09.2019: ";
	while (!(cin >> salary3) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� ������\n";

	}
	cout << "31.06.2019: ";
	while (!(cin >> salary4) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� ������\n";

	}
	char salary[10];
	_itoa_s(salary1, salary, 10);
	send(sclient, salary, sizeof(salary), 0);
	_itoa_s(salary2, salary, 10);
	send(sclient, salary, sizeof(salary), 0);
	_itoa_s(salary3, salary, 10);
	send(sclient, salary, sizeof(salary), 0);
	_itoa_s(salary4, salary, 10);
	send(sclient, salary, sizeof(salary), 0);
}

void Customers::matrix(SOCKET sclient)
{
	char msg[5];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_lenders = atoi(msg);
	if (number_of_lenders == 0) {
		cout << "������ ������ �� ������ ����" << endl;
	}
	else {
		int **matrix;
		int columns = 4;
		matrix = new int*[number_of_lenders];
		for (int z = 0; z < number_of_lenders; z++) { matrix[z] = new int[columns]; }



		char element[10];
		for (int i = 0; i < number_of_lenders; i++) {
			for (int j = 0; j < columns; j++) {
				recv(sclient, element, sizeof(element), 0);
				matrix[i][j] = atoi(element);
			}
		}


		cout << "|--------------------------------------|" << endl;
		cout << "|" << setw(7) << "|" << setw(5) << "�1" << setw(3) << "|" << setw(5) << "�2" << setw(3) << "|" << setw(5) << "�3" << setw(3) << "|" << setw(5) << "�4" << setw(3) << "|" << endl;
		cout << "|--------------------------------------|" << endl;


		for (int i = 0; i < number_of_lenders; i++) {
			cout << "|  " << "�" << i + 1 << "  |" << setw(6) << matrix[i][0] << setw(2) << "|" << setw(6) << matrix[i][1] << setw(2) << "|" << setw(6) << matrix[i][2] << setw(2) << "|" << setw(6) << matrix[i][3] << setw(2) << "|" << endl;
			cout << "|--------------------------------------|" << endl;
		}

		system("pause");
		int *min = new int[number_of_lenders];
		for (int i = 0; i < number_of_lenders; i++) {
			recv(sclient, element, sizeof(element), 0);
			min[i] = atoi(element);
		}

		for (int i = 0; i < number_of_lenders; i++) {
			cout << "����������� ������� ������ �" << i + 1 << ": " << min[i] << endl;
		}
		char msg_g[10];
		recv(sclient, element, sizeof(element), 0);
		int W = atoi(element);
		recv(sclient, element, sizeof(element), 0);
		int indexMax = atoi(element);
		cout << "W max min = " << W << endl;

		cout << "������ ������� �" << indexMax + 1 << " ������ � ���������" << endl;
		cout << "������� 1-����������� ��� 0-�����" << endl;

		int choice = 0;
	again:
		choice = Check<int>();
		if (choice == 1) {

			_itoa_s(choice, msg_g, 10);
			send(sclient, msg_g, sizeof(msg_g), 0);
		}
		if (choice == 0) {
			_itoa_s(choice, msg_g, 10);
			send(sclient, msg_g, sizeof(msg_g), 0);
		}
		if (choice>1) {
			cout << "����������� ������� ��������" << endl;
			goto again;
		}

		for (int count = 0; count < number_of_lenders; count++)
			delete[] matrix[count];
	}
}

void Customers::showCredits(SOCKET sclient)
{
	string path_base = "approvedApplications.txt";
	char msg[5];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_lenders = atoi(msg);
	Customers *lenders = new Customers[number_of_lenders];
	int  salary1, salary2, salary3, salary4, day, month, year;
	char ch_day[5], ch_month[5], ch_year[5];
	char type[20], money[21], time[21],salary11[10], salary22[10], salary33[10], salary44[10];

	if (number_of_lenders == 0) {
		cout << "��� ������������������ ��������." << endl;
		system("pause");
	}
	else {


		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "|" << setw(89) << "���������� ������" << setw(85) << "|" << endl;
		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "|" << setw(5) << "|" << setw(16) << "|" << setw(18) << "|" << setw(18) << "|" << setw(19) << "���� ��������" << setw(8) << "|" << setw(22) << "���������� ������" << setw(5) << "|" << setw(19) << "|" << setw(22) << "|"  << setw(22) << "|"<< endl;
		cout << "|" << setw(3) << "�" << setw(2) << "|" << setw(10) << "�������" << setw(6) << "|" << setw(10) << "���" << setw(8) << "|" << setw(13) << "��������" << setw(5) << "|" << "--------------------------|--------------------------|" << setw(15) << "��� �������" << setw(4) << "|" << setw(15) << "����� �������" << setw(7) << "|"<< setw(15) << "���� �������" << setw(7)  << "|" << endl;
		cout << "|" << setw(5) << "|" << setw(16) << "|" << setw(18) << "|" << setw(18) << "|" << setw(5) << "����" << setw(3) << "|" << setw(7) << "�����" << setw(3) << "|" << setw(6) << "���" << setw(3) << "|" << setw(8) << "�����" << setw(3) << "|" << setw(10) << "�����" << setw(6) << "|" << setw(19) << "|" << setw(22) << "|" << setw(22) << "|" << endl;
		cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

		for (int i = 0; i < number_of_lenders; i++) {
			recv(sclient, lenders[i].surname, sizeof(lenders[i].surname), 0);
			recv(sclient, lenders[i].name, sizeof(lenders[i].name), 0);
			recv(sclient, lenders[i].patronymic, sizeof(lenders[i].patronymic), 0);
			recv(sclient, ch_day, sizeof(ch_day), 0);
			recv(sclient, ch_month, sizeof(ch_month), 0);
			recv(sclient, ch_year, sizeof(ch_year), 0);
			day = atoi(ch_day); lenders[i].date.set_day(day);
			month = atoi(ch_month); lenders[i].date.set_month(month);
			year = atoi(ch_year); lenders[i].date.set_year(year);
			recv(sclient, lenders[i].passportSeries, sizeof(passportSeries), 0);
			recv(sclient, lenders[i].passportNumber, sizeof(passportNumber), 0);

			recv(sclient, type, sizeof(type), 0);
			lenders[i].credit.set_type(type);

			recv(sclient, money, sizeof(money), 0);
			lenders[i].credit.set_money(money);

			recv(sclient, time, sizeof(time), 0);
			lenders[i].credit.set_time(time);

			recv(sclient, salary11, sizeof(salary11), 0);
			recv(sclient, salary22, sizeof(salary22), 0);
			recv(sclient, salary33, sizeof(salary33), 0);
			recv(sclient, salary44, sizeof(salary44), 0);

			salary1 = atoi(salary11); lenders[i].credit.set_salary1(salary1);
			salary2 = atoi(salary22); lenders[i].credit.set_salary2(salary2);
			salary3 = atoi(salary33); lenders[i].credit.set_salary3(salary3);
			salary4 = atoi(salary44); lenders[i].credit.set_salary4(salary4);

			lenders[i].showOneCredit(i + 1);

		}
		system("pause");
	}
	delete[] lenders;
	
}

void Customers::showApplication(SOCKET sclient)
{
	char type[20], money[21], time[21], msg[5];
	recv(sclient, type, sizeof(type), 0);
	recv(sclient, money, sizeof(money), 0);
	recv(sclient, time, sizeof(time), 0);
	recv(sclient, msg, sizeof(msg), 0);
	int check = atoi(msg);
	if (check == 0) {
		cout << "�� �� �������� ������ �� ������." << endl;
	}
	else {
		cout << "|-------------------------------------|" << endl;
		cout << "|" << " ��� �������:" << setw(17) << type << setw(8) << "|" << endl;
		cout << "|" << " ����� �������:" << setw(21) << money << setw(2) << "|" << endl;
		cout << "|" << " ����:" << setw(20) << time << setw(12) << "|" << endl;
		if (check == 1) {
			cout << "| ������: ��������                    |" << endl; 
			cout << "|-------------------------------------|" << endl;
		}
		if (check == 2) {
			cout << "| ������: ���������������             |" << endl;
			cout << "|-------------------------------------|" << endl;
		}
	}
	system("pause");
}

void Customers::salary(SOCKET sclient) {
	char msg[5];
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	Customers *customers;
	customers = new Customers[number_of_customers];
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	int day, month, year, accNumber, amountMoney, check = 0;
	for (int i = 0; i < number_of_customers; i++) {
		recv(sclient, customers[i].surname, sizeof(customers[i].surname), 0);
		recv(sclient, customers[i].name, sizeof(customers[i].name), 0);
		recv(sclient, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
		recv(sclient, ch_day, sizeof(ch_day), 0);
		recv(sclient, ch_month, sizeof(ch_month), 0);
		recv(sclient, ch_year, sizeof(ch_year), 0);
		day = atoi(ch_day); customers[i].date.set_day(day);
		month = atoi(ch_month); customers[i].date.set_month(month);
		year = atoi(ch_year); customers[i].date.set_year(year);
		recv(sclient, customers[i].passportSeries, sizeof(passportSeries), 0);
		recv(sclient, customers[i].passportNumber, sizeof(passportNumber), 0);
		recv(sclient, acc, sizeof(acc), 0);
		recv(sclient, money, sizeof(money), 0);
		accNumber = atoi(acc); customers[i].set_accountNumber(accNumber);
		amountMoney = atoi(money); customers[i].set_cash(amountMoney);
	}

	cout << "������� ����� �����, ������� �� ������ �������� �� ����:" << endl;
	while (!(cin >> amountMoney) || (cin.peek() != '\n') || amountMoney < 1)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� ������\n";

	}

	char msg_g[10];
	_itoa_s(amountMoney, msg_g, 10);
	send(sclient, msg_g, sizeof(msg_g), 0);
	recv(sclient, money, sizeof(money), 0);
	int prevMoney = atoi(money);
	recv(sclient, acc, sizeof(acc), 0);
	int ourAcc = atoi(acc);
	delete[] customers;
	int num2 = 2;
	Customers cus;
	cus.set_ourAccountNumber(ourAcc);
	cus.set_accountNumber(accNumber);
	cus.set_numOperation(num2);
	cus.set_cash(amountMoney);
	cus.set_prevCash(prevMoney);
	operation.push_back(cus);
}

void Customers::withdraw(SOCKET sclient) {
	char msg[5];
	char cash_msg[10];
	recv(sclient, cash_msg, sizeof(cash_msg), 0);
	int cashh = atoi(cash_msg);
	recv(sclient, msg, sizeof(msg), 0);
	int number_of_customers = atoi(msg);
	Customers *customers;
	customers = new Customers[number_of_customers];
	char ch_day[5], ch_month[5], ch_year[5], acc[10], money[10];
	int day, month, year, accNumber, amountMoney, check = 0;
	for (int i = 0; i < number_of_customers; i++) {
		recv(sclient, customers[i].surname, sizeof(customers[i].surname), 0);
		recv(sclient, customers[i].name, sizeof(customers[i].name), 0);
		recv(sclient, customers[i].patronymic, sizeof(customers[i].patronymic), 0);
		recv(sclient, ch_day, sizeof(ch_day), 0);
		recv(sclient, ch_month, sizeof(ch_month), 0);
		recv(sclient, ch_year, sizeof(ch_year), 0);
		day = atoi(ch_day); customers[i].date.set_day(day);
		month = atoi(ch_month); customers[i].date.set_month(month);
		year = atoi(ch_year); customers[i].date.set_year(year);
		recv(sclient, customers[i].passportSeries, sizeof(passportSeries), 0);
		recv(sclient, customers[i].passportNumber, sizeof(passportNumber), 0);
		recv(sclient, acc, sizeof(acc), 0);
		recv(sclient, money, sizeof(money), 0);
		accNumber = atoi(acc); customers[i].set_accountNumber(accNumber);
		amountMoney = atoi(money); customers[i].set_cash(amountMoney);
	}

	cout << "������� ����� �����, ������� �� ������ �������� �� ����:" << endl;
	while (!(cin >> amountMoney) || (cin.peek() != '\n') || amountMoney < 1 || amountMoney>cashh)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� ������\n";
		

	}

	char msg_g[10];
	_itoa_s(amountMoney, msg_g, 10);
	send(sclient, msg_g, sizeof(msg_g), 0);
	recv(sclient, money, sizeof(money), 0);
	int prevMoney = atoi(money);
	recv(sclient, acc, sizeof(acc), 0);
	int ourAcc = atoi(acc);
	delete[] customers;
	int num2 = 3;
	
	Customers cus;
	cus.set_ourAccountNumber(ourAcc);
	cus.set_accountNumber(accNumber);
	cus.set_numOperation(num2);
	cus.set_cash(amountMoney);
	cus.set_prevCash(prevMoney);
	operation.push_back(cus);


}

void Customers::print(SOCKET sclient) {
	char msg[10], msg_cash[10];
	int accNumber, money;
	recv(sclient, msg, sizeof(msg), 0);
	accNumber = atoi(msg);
	recv(sclient, msg_cash, sizeof(msg_cash), 0);
	money = atoi(msg_cash);
	cout << "����� ������ �����: " << accNumber << endl;
	cout << "���� ($): " << money << endl;

}


