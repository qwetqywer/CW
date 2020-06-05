#pragma once
#include "Date.h"
#include "Credit.h"
#include <WinSock2.h>

class Customers {
	char surname[20];
	char patronymic[20];
	char name[20];
	char passportSeries[5];
	char passportNumber[8];
	int accountNumber;
	Date date;
	Credit credit;
	int cash=0;
public:
	void addCustomer(SOCKET sserver);
	void showAll(SOCKET sserver);
	void deleteCustomer(SOCKET sserver);
	void editCustomer(SOCKET sserver);
	void searchMenu(SOCKET sserver);
	void searchSNP(SOCKET sserver);
	void searchPassport(SOCKET sserver);
	void searchAccountNumber(SOCKET sserver);
	void sortingCustomers(SOCKET sserver);
	void set_surname(char * surname) {
		strcpy_s(this->surname, surname);
	}
	void set_name(char * name) {
		strcpy_s(this->name, name);
	}
	void set_patronymic(char * patronymic) {
		strcpy_s(this->patronymic, patronymic);
	}
	void set_passportSeries(char * passportSeries) {
		strcpy_s(this->passportSeries, passportSeries);
	}
	void set_passportNumber(char * passportNumber) {
		strcpy_s(this->passportNumber, passportNumber);
	}
	void set_accountNumber(int accountNumber) {
		this->accountNumber = accountNumber;
	}
	void set_cash(int cash) {
		this->cash = cash;
	}
	int get_cash() {
		return cash;
	}
	void print(SOCKET sserver, int numUser);
	void withdraw(SOCKET sserver, int numUser);
	void salary(SOCKET sserver, int numUser);
	void transfer(SOCKET sserver, int numUser);
	void applyForALoan(SOCKET sserver,int numUser);
	void matrix(SOCKET sserver);
	void showCredit(SOCKET sserver);
	void checkCredit(SOCKET sserver, int numUser);
};