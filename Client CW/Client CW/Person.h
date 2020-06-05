#pragma once
#include <WinSock2.h>

class Person {
protected:
	char login[20];
	char password[20];
public:
	virtual int first_menu() = 0;
	virtual void authorization(SOCKET sclient) = 0;
	virtual void second_menu(SOCKET sclient) = 0;
};