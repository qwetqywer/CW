#pragma once
#include "Date.h"
#include "CW.h"
#include "Credit.h"
#include <WinSock2.h>

class Customers {
	char surname[20];
	char patronymic[20];
	char name[20];
	char passportSeries[5];
	char passportNumber[8];
	Date date;
	Credit credit;
	int accountNumber;
	int cash = 0;
	int numOperation;
	int prevCash;
	int ourAccountNumber;
public:
	void addCustomer(SOCKET sclient);
	void showAll(SOCKET sclient);
	void set_accountNumber(int accountNumber) {
		this->accountNumber = accountNumber;
	}
	void set_cash(int cash) {
		this->cash = cash;
	}
	void deleteCustomer(SOCKET sclient);
	void showOne(int counter);
	void showOneCredit(int counter);
	void editCustomer(SOCKET sclient);
	void editMenu();
	void searchMenu(SOCKET sclient);
	void searchSNP(SOCKET sclient);
	void searchPassport(SOCKET sclient);
	void searchAccountNumber(SOCKET sclient);
	void sortingCustomers(SOCKET sclient);
	void print(SOCKET sclient);
	void withdraw(SOCKET sclient);
	void salary(SOCKET sclient);
	void transfer(SOCKET sclient);
	void history(SOCKET sclient);
	void applyForALoan(SOCKET sclient);
	void matrix(SOCKET sclient);
	void set_ourAccountNumber(int ourAccountNumber) {
		this->ourAccountNumber = ourAccountNumber;
	}
	void set_numOperation(int numOperation) {
		this->numOperation = numOperation;
	}
	void set_prevCash(int prevCash) {
		this->prevCash = prevCash;
	}
	template <class T> friend T Check();

	void showCredits(SOCKET sclient);
	void showApplication(SOCKET sclient);
};



template <class T> T Check()
{
	T number;
	while (!(cin >> number) || (cin.peek() != '\n') || number < 0)
	{
		cout << "Неправильно введены данные\n";
		cin.clear();
		while (cin.get() != '\n');
	}
	return number;
}
