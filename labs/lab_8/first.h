#pragma once
#include "MyQueue.h"

MyQueue<double> first_make() {
	int n;
	cout << "N? "; cin >> n;
	MyQueue<double> temp;
	double val;
	cout << "Введите " << n << " значений через пробел: ";
	for (int i = 0; i < n; i++) {
		cin >> val;
		temp.push(val);
	}
	return temp;
}

void first_show(string text, MyQueue<double>& que) {
	cout << text;
	MyQueue<double> temp;
	double p;
	while (!que.empty()) {
		p = que.front();
		cout << p << " ";
		temp.push(p);
		que.pop();
	}
	while (!temp.empty()) {
		p = temp.front();
		que.push(p);
		temp.pop();
	}
	cout << endl;
}

void first_insert(MyQueue<double>& que) {
	MyQueue<double> temp;
	double p;
	while (!que.empty()) {
		p = que.front();
		temp.push(p);		
		if (p < 0)
			temp.push(0);
		que.pop();
	}
	while (!temp.empty()) {
		p = temp.front();
		que.push(p);
		temp.pop();
	}
}

void first_exec() {
	try {
		MyQueue<double> que = first_make();
		first_show("Исходная очередь: ", que);
		first_insert(que);
		first_show("Очередь после добавления 0 после отрицательных: ", que);
	}
	catch (exception& err) {
		cout << "Ошибка: " << err.what() << endl;
	}
}