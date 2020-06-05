#pragma once
#include "Person.h"




class Admin : public Person {
public:
	void authorization(SOCKET sserver);
	void second_menu(SOCKET sserver);
};