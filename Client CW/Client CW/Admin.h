#pragma once
#include "Person.h"



class Admin : public Person {
public:
	void authorization(SOCKET sclient);
	int first_menu();
	void second_menu(SOCKET sclient);

};