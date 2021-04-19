#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "c.h"
#include "cpp.h"

int main()
{
	system("chcp 1251");

	int x;
	while (true) {
		cout << "\n1. C\n2.C++\n3. Выход\n>";
		cin >> x;
		system("cls");
		switch (x) {
		case 1: c_exec(); break;
		case 2: cpp_exec(); break;
		case 3: return 0;
		}
	}
}
