#pragma once
#include <WinSock2.h>

class Person {
protected:
	char login[20];
	char password[20];
public:	
	virtual void authorization(SOCKET sserver) = 0;
};