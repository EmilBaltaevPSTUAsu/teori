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
	cout << "Список студентов:\n";
	long i = 0;
	do {
		f >> a;
		if (f.eof())
			break;
		cout << ++i << ") " << a;

	} while (!f.eof());
	f.close();
	if (i == 0)
		cout << "пусто";
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
		// если нашли
		if (++i == K)
			b = cpp_add(temp);
		temp << a << endl;
	} while (!f.eof());
	// если в конец
	if(++i == K)
		b = cpp_add(temp);
	f.close();
	temp.close();
	remove("f.bin");
	rename("f2.bin", "f.bin");
	if (b == 0)
		cout << "Неверный номер" << endl;
	else
		cout << "Успешно" << endl;
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
	cout << "Успешно" << endl;
}

void cpp_exec() {
	int x;
	while (true) {
		cout << "\n1.Создать\n";
		cout << "2.Прочитать\n";
		cout << "3.Удалить с рейтингом меньше заданного\n";
		cout << "4.Добавить с номером К\n";
		cout << "5.Выйти\n>";
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
