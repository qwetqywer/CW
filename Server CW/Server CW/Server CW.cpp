#include "Admin.h"
#include "User.h"
#include "Expert.h"
#include "CW.h"



SOCKET Connections[100];
int Counter = 0;


void ClientHandler(int index) {
	char msgChoice[5];
	Admin admin;
	User user;
	Expert expert;
	while (true) {
		
				int check = 0;
		
				do
				{
					recv(Connections[index], msgChoice, sizeof(msgChoice), 0);
					int choice = atoi(msgChoice);
		
					switch (choice)
					{
					case 1: {
						admin.authorization(Connections[index]); break;
					} 
					case 2: { user.authorization(Connections[index]); break; }
					case 3: { expert.authorization(Connections[index]); break; }
					case 4: { user.registration(Connections[index]); break; }
					case 5: {break; }
					}
		
				} while (check == 0);
	}
}


int main()
{	
	SetConsoleTitle(L"Банк(сервер)");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Ошибка" << endl;
		
		exit(1);
	}
	else { cout << "Сервер готов к работе!" << endl; }
	

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0) {
			cout << "Ошибка #2\n";
		}
		else {
			SYSTEMTIME st;
			GetSystemTime(&st);
			cout << "Параметры подключения: " << st.wDay << "." << st.wMonth << "." << st.wYear << ".." << st.wHour << "-" << st.wMinute << endl;
			Connections[i] = newConnection;
			Counter++;
			cout << "Клиент №" << Counter << " подключен!" << endl;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}


	system("pause");
		
		return 0;
}





