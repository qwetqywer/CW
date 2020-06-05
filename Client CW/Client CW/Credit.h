#pragma once
#include "CW.h"
class Credit {
	char type[20];
	char money[21];
	char time[21];
	int salary[4];
public:
	char * get_type() {
		return type;
	}
	char * get_money() {
		return money;
	}
	char * get_time() {
		return time;
	}

	void set_money(char* money) {
		strcpy(this->money, money);
	}
	void set_time(char* time) {
		strcpy(this->time, time);
	}
	void set_type(char* type) {
		strcpy(this->type, type);
	}

	void set_salary1(int salary1) {
		salary[0] = salary1;
	}
	void set_salary2(int salary2) {
		salary[1] = salary2;
	}
	void set_salary3(int salary3) {
		salary[2] = salary3;
	}
	void set_salary4(int salary4) {
		salary[3] = salary4;
	}
	int get_salary1() {
		return salary[0];
	}
	int get_salary2() {
		return salary[1];
	}
	int get_salary3() {
		return salary[2];
	}
	int get_salary4() {
		return salary[3];
	}
};