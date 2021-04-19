#pragma once
#include "MyStack.h"

MyStack<double> second_make() {
	int n;
	cout << "N? "; cin >> n;
	MyStack<double> temp;
	double val;
	cout << "������� " << n << " �������� ����� ������: ";
	for (int i = 0; i < n; i++) {
		cin >> val;
		temp.push(val);
	}
	return temp;
}

void second_show(string text, MyStack<double>& st) {
	cout << text;
	double val;
	MyStack<double> temp;
	while (!st.empty()) {
		val = st.top();
		cout << val << " ";
		temp.push(val);
		st.pop();
	}
	while (!temp.empty()) {
		val = temp.top();
		st.push(val);
		temp.pop();
	}
	cout << endl;
}

void second_insert(MyStack<double>& st) {
	double val;
	MyStack<double> temp;
	while (!st.empty()) {
		val = st.top();
		if (val < 0)
			temp.push(0);
		temp.push(val);
		st.pop();
	}
	while (!temp.empty()) {
		val = temp.top();
		st.push(val);
		temp.pop();
	}
}

void second_exec() {
	try {
		MyStack<double> st = second_make();
		second_show("�������� ����: ", st);
		second_insert(st);
		second_show("���� ����� ���������� 0 ����� �������������: ", st);
	}
	catch (exception& err) {
		cout << "������: " << err.what() << endl;
	}
}
