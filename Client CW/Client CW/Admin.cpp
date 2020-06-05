#include "CW.h"
#include "Admin.h"
#include "Customers.h"

void Admin::authorization(SOCKET sclient)
{
	int check = 5;
	char msgChoice[5];
	cout << "������� �����" << endl;
	cin >> login;
	cout << "������� ������" << endl;
	int j = 0;
	while (j != 16)
	{
		password[j] = _getch();
		if (password[j] == '\r')
			break;
		if (password[j] == '\b')
		{
			printf("\b \b");
			j--;
		}
		else if (password[j] != '\0')
		{
			printf("*");
			j++;
		}
	}
	password[j] = '\0';

	send(sclient, login, sizeof(login), 0);
	send(sclient, password, sizeof(password), 0);
	
	recv(sclient, msgChoice, sizeof(msgChoice), 0);
	int choice = atoi(msgChoice);
	if (choice == 1) {
		cout << "\n";
		cout << "�� ����� � �������!" << endl;
		system("pause");
		second_menu(sclient);
	}
	else {
		cout << "\n";
		cout << "�������� ����� ��� ������!" << endl;
		system("pause");
	}		
}

int Admin::first_menu()
{
	system("cls");
	cout << "1. ����������� ��������" << endl
		<< "2. ������������� �������" << endl
		<< "3. ������� �������" << endl
		<< "4. ����� � ���������� ��������" << endl
		<< "5. ��������� �����" << endl;

	int choice = 1;
	choice = CheckNumber(choice, 5);
	return choice;
}

void Admin::second_menu(SOCKET sclient)
{
	Customers customer;
	system("cls");
	
	char msgChoice[5];
	int check = 0;
	while (check == 0) {
		int choice = first_menu();
		_itoa_s(choice, msgChoice, 10);
		send(sclient, msgChoice, 5, 0);
		switch (choice) {
		case 1: {
			customer.showAll(sclient);
			break;
		}
		case 2: {
			customer.editCustomer(sclient);
			break;
		}
		case 3: {
			customer.deleteCustomer(sclient);
			break;
		}
		case 4: {
			customer.searchMenu(sclient);
			break;
		}
		case 5: {
			check = 5;
			break;
		}
		default: {
			cout << "����������� ������� ��������" << endl;
			break;
		}
		}
	}

}



