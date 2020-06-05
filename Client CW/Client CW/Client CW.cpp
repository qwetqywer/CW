#include "CW.h"
#include "Admin.h"
#include "User.h"
#include "Expert.h"

SOCKET Connection;

int main()
{
	SetConsoleTitle(L"Банк(клиент)");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int check;
	Admin admin;
	User user;
	Expert expert;
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Ошибка: не удалось подключиться к серверу.\n";
		return 1;
	}


	char msg1[256];
	while (true) {
		int choice = 0;
		system("cls");
		cout << "1.Войти как администратор" << endl;
		cout << "2.Войти как клиент" << endl;
		cout << "3.Войти как эксперт" << endl;
		cout << "4.Зарегистрироваться как клиент" << endl;
		cout << "5.Выход" << endl;
		cout << "Ваш выбор? " << endl;

		cin >> choice;

		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Connection, msgChoice, 5, 0);

		switch (choice)
		{
		case 1: {
			system("cls"); admin.authorization(Connection);
			break;
		}
		case 2: {
			system("cls"); user.authorization(Connection);
			break;
		}
		case 3: {
			system("cls"); expert.authorization(Connection);
			break;
		}
		case 4: {
			system("cls");  user.registration(Connection);
			break;
		}
		case 5: {
			system("cls"); exit(0);
			break;
		}
		}
        
	}

	system("pause");
	
	
	return 0;
}
    


