#pragma once
#include "Person.h"

class User : public Person {
public:
	void authorization(SOCKET sserver);
	/*int first_menu();*/
	void userMenu(int numUser,SOCKET sserver);
	void registration(SOCKET sserver);
	void deleteUser(int number);

};