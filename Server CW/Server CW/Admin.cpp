#include "Admin.h"
#include "Customers.h"
#include "CW.h"




void Admin::authorization(SOCKET sserver) {
	ifstream fin;
	int check = 5;
	char pass[20];
	char log [20];
	char msgChoice[5];
	fin.open("admin.txt");
	if (!fin.is_open())
	{
		cout << "Ошибка открытия файла." << endl;
	}
	else {
		fin >> login;
		fin >> password;
		

		recv(sserver, log, sizeof(log), 0);
		recv(sserver, pass, sizeof(pass), 0);


		for (int j = 0; j < strlen(password); j++) {
			password[j] = password[j] - 5;
		}
	

		
		int check=0;
			
		int k, k1;
		k = strcmp(pass, password);
		k1 = strcmp(log, login);
		if (k == 0 && k1 == 0) {
			check = 1;
			cout << "\n";
			/*cout << "Вход от имени администратора." << endl;*/
			_itoa_s(check, msgChoice, 10);
			send(sserver, msgChoice, 5, 0);
			second_menu(sserver);

		}
		else {
			_itoa_s(check, msgChoice, 10);
			send(sserver, msgChoice, 5, 0);
		}
	}
	

	fin.close();
}



void Admin::second_menu(SOCKET sserver)
{

	Customers customer;
	char msgChoice[5];
	int check = 0;
	while (check == 0) {
		recv(sserver, msgChoice, sizeof(msgChoice), 0);
		int choice = atoi(msgChoice);
		switch (choice) {
		case 1: {
			customer.showAll(sserver);
			break;
		}
		case 2: {
			customer.editCustomer(sserver);
			break;

		}
		case 3: {
			customer.deleteCustomer(sserver);
			break;
		}
		case 4: {
			customer.searchMenu(sserver);
			break;
		}
		case 5:
			
			check = 5;
			break;

		}
	}
}


