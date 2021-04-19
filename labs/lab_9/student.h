#pragma once
#include <iostream>
#include <fstream>
using namespace std;

struct student
{
	char fname[50];
	char sname[50];
	char tname[50];
	char adress[255];
	char group[50];
	double rating;

	friend ostream& operator<< (ostream& out, const student& a);
	friend istream& operator>> (istream& in, student& a);
	friend fstream& operator<< (fstream& out, const student& a);
	friend fstream& operator>> (fstream& in, student& a);
};

// cout << 
ostream& operator<< (ostream& out, const student& a) {
	out << a.fname << " " << a.sname[0] << ". " << a.tname[0] << ". гр. " << a.group << endl;
	out << "Проживает: " << a.group << " cр.рейтинг: " << a.rating << endl;
	return out;
}

// cin >>
istream& operator>> (istream& in, student& a) {
	cout << "ФИО: "; in >> a.fname >> a.sname >> a.tname;
	in.ignore();
	cout << "Адрес: "; in.getline(a.adress, 255);
	cout << "Группа: "; in >> a.group;
	cout << "Рейтинг: "; in >> a.rating;
	return in;
}

// fileStream <<
fstream& operator<< (fstream& out, const student& a) {
	out << a.fname << " " << a.sname << " " << a.tname << " " << a.adress << " " << a.group << " " << a.rating << endl;
	return out;
}

// fileStream >>
fstream& operator>> (fstream& in, student& a) {
	in >> a.fname >> a.sname >> a.tname >> a.adress >> a.group >> a.rating;
	return in;
}
