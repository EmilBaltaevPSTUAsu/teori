#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Person
{
private:
	string fname, sname, tname;
	string phone;
	string adress;

public:
	Person();
	Person(string f, string s, string t, string p, string a);
	Person(const Person& p);
	~Person() {}

	bool operator== (const Person& p);

	int getHashCode();
	static Person* random();

	friend ostream& operator<< (ostream& out, const Person& fin);
	friend istream& operator>> (istream& in, Person& fin);
	friend fstream& operator<< (fstream& out, const Person& fin);
	friend fstream& operator>> (fstream& in, Person& fin);
};

