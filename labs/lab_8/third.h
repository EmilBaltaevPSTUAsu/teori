#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

struct Point
{
	char* key;
	Point* left;
	Point* right;
};

Point* make_point(char* d)
{
	Point* p = new Point;
	p->key = new char[strlen(d)];
	strcpy(p->key, d);
	p->left = 0;
	p->right = 0;
	return p;
}

//���������� �������� ����������������� ������
Point* Tree(Point* root, int n)
{
	char buf[255];
	Point* p = root;
	Point* r;
	int nl, nr;
	if (n == 0) {
		p = 0; 
		return p;
	}
	nl = n / 2;
	nr = n - nl - 1;
	r = new Point;
	cout << "val? "; cin >> buf;
	r->key = new char[strlen(buf)];
	strcpy(r->key, buf);
	r->left = Tree(r->left, nl);
	r->right = Tree(r->right, nr);
	return r;
}

void getXY(CONSOLE_SCREEN_BUFFER_INFO& csbiInfo) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
}

void goXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printElement(Point* p, int x, int y, int row)
//����� ����� �������
{
	if (p)
	{
		goXY(x, y);
		for (int i = 0; i < strlen(p->key) && i < 3; i++)
			cout << p->key[i];
		printElement(p->left, x  - 10, y + 1, row + 1);	//������� � ������ ���������
		printElement(p->right, x + 10, y + 1, row + 1);	//������� � ������� ���������
	}
}

void printVertical(Point* root) {
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	getXY(csbiInfo);
	int x0 = csbiInfo.dwSize.X / 2,
		y0 = csbiInfo.dwCursorPosition.Y;
	printElement(root, x0, y0, 0);
	cout << endl;
}

void find(Point* p, const char& key, int& count) {
	if (p)
	{
		if (strlen(p->key) > 0 && p->key[0] == key)
			count++;
		find(p->left, key, count);	//������� � ������ ���������
		find(p->right, key, count);	//������� � ������� ���������
	}
}


// ������ ������

Point* Add(Point* root, char* d)
{
	Point* p = root;//������ ������
	Point* r = 0;
	bool ok = false; //���� ��� �������� ������������� �������� d � ������
	while (p && !ok) {
		r = p;
		if (strcmp(d, p->key) == 0)
			ok = true; //������� ��� ����������
		else
			if (strcmp(d, p->key) > 0)
				p = p->left; //����� � ����� ���������
			else
				p = p->right; //����� � ������ ���������
	}
	if (ok)
		return p; //�������, �� ���������
	Point* New_point = new Point;
	New_point->key = new char[strlen(d)];
	strcpy(New_point->key, d);
	New_point->left = 0;
	New_point->right = 0;
	// ���� d<r->key, �� ��������� ��� � ����� ���������
	if (strcmp(d, r->key) > 0)
		r->left = New_point;
	// ���� d>r->key, �� ��������� ��� � ������ ���������
	else
		r->right = New_point;
	return New_point;
}

void formTree(Point* p, Point* rootTree) {
	if (p)
	{
		Add(rootTree, p->key);
		formTree(p->left, rootTree);	//������� � ������ ���������
		formTree(p->right, rootTree);	//������� � ������� ���������
	}
}

void third_exec() {
	int n;
	char buf[255];

	cout << "\n��������-���������������� ������\n";
	cout << "N? "; cin >> n;
	Point* root = new Point;
	root = Tree(root, n);
	printVertical(root);

	cout << "\n���������� ��������� ���-�� � ��������� �������\n";
	char key;
	cout << "c? "; cin >> key;
	int count = 0;
	find(root, key, count);
	cout << "�������� = " << count << endl; 

	cout << "\n������ ������\n";
	Point* rootTree = make_point(root->key);
	formTree(root, rootTree);
	printVertical(rootTree);
}
