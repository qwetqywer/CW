#pragma once
#include "Person.h"
class Expert : public Person {
public:
	void authorization(SOCKET sserver);
	void expertMenu( SOCKET sserver);
	

};