#pragma once
#include <iostream>
#include "point.h"
using namespace std;

template <class T>
class MyStack 
{
private:
	point<T>* beg;
	point<T>* curr;
	int len;

public:
	MyStack();
	MyStack(const MyStack<T>& st);
	~MyStack();

	int size();
	bool empty();

	T& top();

	void push(const T& val);
	void pop();
};

template<class T>
inline MyStack<T>::MyStack()
{
	beg = curr = 0;
	len = 0;
}

template<class T>
inline MyStack<T>::MyStack(const MyStack<T>& st)
{
	point<T>* p = st.beg;
	while (p != 0) {
		push(p->data);
		p = p->next;
	}
}

template<class T>
inline MyStack<T>::~MyStack()
{
	point<T>* p = beg;
	while (p != 0) {
		p = p->next;
		delete beg;
		beg = p;
	}
	beg = curr = 0;
}

template<class T>
inline int MyStack<T>::size()
{
	return len;
}

template<class T>
inline bool MyStack<T>::empty()
{
	return len == 0;
}

template<class T>
inline T& MyStack<T>::top()
{
	if (curr == 0)
		throw exception("пустой стек");
	return curr->data;
}

template<class T>
inline void MyStack<T>::push(const T& val)
{
	point<T>* temp = make_point(val);
	// если пусто
	if (curr == 0) {
		beg = curr = temp;
	}
	else {
		curr->next = temp;
		temp->prev = curr;
		curr = temp;
	}
	len++;
}

template<class T>
inline void MyStack<T>::pop()
{
	point<T>* p = curr;
	curr = curr->prev;
	delete p;
	len--;
	if (len == 0)
		beg = curr = 0;
	else
		curr->next = 0;
}
