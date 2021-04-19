#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Finance
{
private:
	int id;
	string dep;
	int year;
	int month;
	double salary;
	bool is_delete = false;

public:
	Finance() { id = 0; dep = ""; year = 0; month = 0; salary = 0; }
	Finance(int i, string d, int y, int m, double s);
	~Finance() {}

	int get_id() { return id; }
	string get_department() { return dep; }
	int get_year() { return year; }
	int get_month() { return month; }
	int get_salary() { return salary; }
	bool get_isDelete() { return is_delete; }

	void set_id(int i) { id = i; }
	void set_department(string d) { dep = d; }
	void set_year(int y);
	void set_month(int m);
	void set_salary(double s);
	void set_isDelete(bool id) { is_delete = id; }

	bool operator== (const Finance& fin);

	friend ostream& operator<< (ostream& out, const Finance& fin);
	friend istream& operator>> (istream& in, Finance& fin);
	friend fstream& operator<< (fstream& out, const Finance& fin);
	friend fstream& operator>> (fstream& in, Finance& fin);
};

