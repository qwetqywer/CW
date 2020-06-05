#include "User.h"
#include "Customers.h"
#include "CW.h"


void User::authorization(SOCKET sclient)
{
	char login_check[20];
	char password_check[20];
	char msg[5]; int ch = 0;
    recv(sclient, msg, sizeof(msg), 0);
	ch= atoi(msg);
		if (ch == 0) {
			cout << "Ошибка: нет зарегистрированных клиентов." << endl;
			system("pause");
		}
		else {
				system("cls");
				cout << "Введите логин:" << endl;
				cin >> login_check;
				send(sclient, login_check, sizeof(login_check), 0);

				cout << "Введите пароль:" << endl;
				int j = 0;
				while (j != 16)
				{
					password_check[j] = _getch();
					if (password_check[j] == '\r')
						break;
					if (password_check[j] == '\b')
					{
						printf("\b \b");
						j--;
					}
					else if (password_check[j] != '\0')
					{
						printf("*");
						j++;
					}
				}
				password_check[j] = '\0';

				send(sclient, password_check, sizeof(password_check), 0);
				recv(sclient, msg, sizeof(msg), 0);
				int check = atoi(msg);

				if (check == 0) {
					cout << "\n";
					cout << "Ошибка: неверный пароль или логин." << endl;
					system("pause");
				
				}
				if (check == 2) {
					cout << "\n";
					cout << "Вы вошли в систему!" << endl;
					system("pause");
					second_menu(sclient);
			
					
				}	
		}
}

int User::first_menu()
{
	
	cout << "1. Перевести деньги на другой счет" << endl
		<< "2. Положить деньги на счет" << endl
		<< "3. Снять деньги со счета" << endl
		<< "4. Просмотреть историю операций" << endl
		<< "5. Подать заявку на кредит" << endl
		<< "6. Просмотреть заявку на кредит" << endl
		<< "7. Вернуться назад" << endl;
	int choice = 1;
	choice = Checks::CheckNumber(choice, 7);
	return choice;
	return 0;
}

void User::second_menu(SOCKET sclient)
{
	Customers customer;
	int check = 0;
	
	while (check == 0) {
		system("cls");
		customer.print(sclient);
		int choice = first_menu();	
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(sclient, msgChoice, 5, 0);
		switch (choice) {
		case 1: {
			customer.transfer(sclient);
			break;
		}
		case 2: {

			customer.salary(sclient);
			break;

		}
		case 3: {
			customer.withdraw(sclient);

			break;
		}
		case 4: {
			customer.history(sclient);

			break;
		}
		case 5: {
			customer.applyForALoan(sclient);
			break;
		}
		case 6: {
			customer.showApplication(sclient);
			break;
		}
		case 7: {
			check = 5;

			break;
		}
		}
	}
}

void User::registration(SOCKET sclient) {
	char msg[5]; 
	Customers customer;
	
	cout << "Введите логин:" << endl;
	cin >> login;
	send(sclient, login, sizeof(login), 0);

	cout << "Введите пароль:" << endl;
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
	send(sclient, password, sizeof(password), 0);




	recv(sclient, msg, sizeof(msg), 0);
	int check = atoi(msg);
	if (check == 1) {
		cout << "Ошибка: данный логин уже используется" << endl;
		system("pause");
	}
	else {

		customer.addCustomer(sclient);
	}



	

}
