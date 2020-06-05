#include "Expert.h"
#include "Customers.h"
#include "CW.h"

void Expert::authorization(SOCKET sserver)
{
	ifstream fin;
	int check = 5;
	char pass[20];
	char log[20];
	char msgChoice[5];
	fin.open("expert.txt");
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



		int check = 0;

		int k, k1;
		k = strcmp(pass, password);
		k1 = strcmp(log, login);
		if (k == 0 && k1 == 0) {
			check = 1;
			cout << "\n";
			_itoa_s(check, msgChoice, 10);
			send(sserver, msgChoice, 5, 0);
			expertMenu(sserver);

		}
		else {
			_itoa_s(check, msgChoice, 10);
			send(sserver, msgChoice, 5, 0);
		}
	}


	fin.close();
}

void Expert::expertMenu( SOCKET sserver)
{
	Customers customer;
	char msgChoice[5];
	int check = 0;
	while (check == 0) {
		recv(sserver, msgChoice, sizeof(msgChoice), 0);
		int choice = atoi(msgChoice);
		switch (choice) {
		case 1: {
			customer.matrix(sserver);
			break;
		}
		case 2: {
			customer.showCredit(sserver);
			break;

		}
		
		case 3:

			check = 5;
			break;

		}
	}

}
