#pragma once
#include <fstream>
#include "student.h"

void cpp_save() {
	fstream f("f.bin", ios::out);
	int n;
	cout << "N?"; cin >> n;
	student a;
	for (int i = 0; i < n; i++) {
		cin >> a;
		f << a << endl;
	}
	f.close();

}

void cpp_read() {
	fstream f("f.bin", ios::in);
	student a;
	cout << "������ ���������:\n";
	long i = 0;
	do {
		f >> a;
		if (f.eof())
			break;
		cout << ++i << ") " << a;

	} while (!f.eof());
	f.close();
	if (i == 0)
		cout << "�����";
}

student* cpp_add(fstream& f) {
	student* s = new student;
	cin >> *s;
	f << *s << endl;
	delete s;
	return s;
}

void cpp_insert() {
	int K;
	cout << "K? "; cin >> K;
	fstream f("f.bin", ios::in);
	fstream temp("f2.bin", ios::out);
	student a, *b = 0;
	long i = 0;
	do {
		f >> a;
		if (f.eof())
			break;
		// ���� �����
		if (++i == K)
			b = cpp_add(temp);
		temp << a << endl;
	} while (!f.eof());
	// ���� � �����
	if(++i == K)
		b = cpp_add(temp);
	f.close();
	temp.close();
	remove("f.bin");
	rename("f2.bin", "f.bin");
	if (b == 0)
		cout << "�������� �����" << endl;
	else
		cout << "�������" << endl;
}

void cpp_delete() {
	double key;
	cout << "key? "; cin >> key;
	fstream f("f.bin", ios::in);
	fstream temp("f2.bin", ios::out);
	student a;
	do {
		f >> a;
		if (f.eof())
			break;
		if (a.rating >= key)
			temp << a << endl;
	} while (!f.eof());
	f.close();
	temp.close();
	remove("f.bin");
	rename("f2.bin", "f.bin");
	cout << "�������" << endl;
}

void cpp_exec() {
	int x;
	while (true) {
		cout << "\n1.�������\n";
		cout << "2.���������\n";
		cout << "3.������� � ��������� ������ ���������\n";
		cout << "4.�������� � ������� �\n";
		cout << "5.�����\n>";
		cin >> x;
		switch (x) {
		case 1: cpp_save(); break;
		case 2: cpp_read(); break;
		case 3: cpp_delete(); break;
		case 4: cpp_insert(); break;
		case 5: return;
		}
	}
}
