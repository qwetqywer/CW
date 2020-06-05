#pragma once
class Date {
	int day;
	int month;
	int year;
public:
	int get_day() {
		return day;
	}
	int get_month() {
		return month;
	}
	int get_year() {
		return year;
	}
	void set_day(int day) {
		this->day = day;
	}
	void set_month(int month) {
		this->month = month;
	}
	void set_year(int year) {
		this->year = year;
	}
};