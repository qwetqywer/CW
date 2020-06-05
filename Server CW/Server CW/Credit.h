#pragma once
#include "CW.h"

class Credit {
	char type[20];
	char money[4][21];
	char time[4][21];
	
	char money_choice[21];
	char time_choice[21];
	int salary[4];
public:
	Credit *readFileInformation();
	void set_money(char* money_choice) {
		strcpy(this->money_choice, money_choice);
	}
	void set_time(char* time_choice) {
		strcpy(this->time_choice, time_choice);
	}
	void set_type(char* type) {
		strcpy(this->type, type);
	}
	char* get_type() {
		return type;
	}
	char* get_time() {
		return time_choice;
	}
	char* get_money() {
		return money_choice;
	}
	void setMoney1() {
		strcpy(money_choice, money[0]);
	}
	void setMoney2() {
		strcpy(money_choice, money[1]);
	}
	void setMoney3() {
		strcpy(money_choice, money[2]);
	}
	void setTime1() {
		strcpy_s(time_choice, time[0]);
	}
	void setTime2() {
		strcpy(time_choice, time[1]);
	}
	void setTime3() {
		strcpy(time_choice, time[2]);
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