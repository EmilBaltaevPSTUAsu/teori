#pragma once
#include "student.h"

void c_save() {
	int n;
	cout << "N? "; cin >> n;
	student a;
	FILE* f = fopen("file1.bin", "wb");
	for (int i = 0; i < n; i++) {
		cin >> a;
		fwrite(&a, sizeof(student), 1, f);
	}
	fclose(f);
	cout << "�������\n";
}

void c_read() {
	FILE* f;
	f = fopen("file1.bin", "rb");
	student a;
	cout << "������ ���������\n";
	long i;
	for (i = 0; fread(&a, sizeof(student), 1, f); i++) {
		cout << (i + 1) << ") ";
		cout << a << endl;
	}
	if (i == 0)
		cout << "�����";
	fclose(f);
	cout << endl;
}

student* c_add(FILE* f) {
	student* s = new student;
	cin >> *s;
	fwrite(s, sizeof(student), 1, f);
	delete s;
	return s;
}

void c_insert() {
	int K;
	cout << "K? "; cin >> K;
	FILE* f;
	FILE* temp;
	f = fopen("file1.bin", "rb");
	temp = fopen("file2.bin", "wb");
	student a, *b = 0;
	long i;
	for (i = 0; fread(&a, sizeof(student), 1, f); i++) {
		// ���� ����� �����
		if ((i + 1) == K)
			b = c_add(temp);
		fwrite(&a, sizeof(student), 1, temp);
	}
	// ���� � �����
	if ((i+1) == K) 
		b = c_add(temp);
	fclose(f);
	fclose(temp);
	remove("file1.bin");
	rename("file2.bin", "file1.bin");
	if (b == 0)
		cout << "�������� �����" << endl;
	else
		cout << "�������" << endl;
}

void c_delete() {
	double key;
	cout << "key? "; cin >> key;
	FILE* f;
	FILE* temp;
	f = fopen("file1.bin", "rb");
	temp = fopen("file2.bin", "wb");
	student a;
	for (long i = 0; fread(&a, sizeof(student), 1, f); i++) {
		if(a.rating >= key)
			fwrite(&a, sizeof(student), 1, temp);
	}
	fclose(f);
	fclose(temp); 
	remove("file1.bin");
	rename("file2.bin", "file1.bin");
	cout << "�������" << endl;
}

void c_exec() {
	int x;
	while (true) {
		cout << "\n1.�������\n";
		cout << "2.���������\n";
		cout << "3.������� � ��������� ������ ���������\n";
		cout << "4.�������� � ������� �\n";
		cout << "5.�����\n>";
		cin >> x;
		switch (x) {
		case 1: c_save(); break;
		case 2: c_read(); break;
		case 3: c_delete(); break;
		case 4: c_insert(); break;
		case 5: return;
		}
	}
}

