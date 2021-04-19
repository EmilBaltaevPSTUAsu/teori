#pragma once
#include <iostream>
#include "point.h"
using namespace std;

template <class T>
class MyQueue
{
private:
	point<T>* curr;
	point<T>* beg;
	int len;

public:
	MyQueue();
	MyQueue(const MyQueue<T>& que);
	~MyQueue();

	T& front();
	T& back();

	int size();
	bool empty();
	void push(const T& val);
	void pop();
};

template<class T>
inline MyQueue<T>::MyQueue()
{
	beg = curr = 0;
	len = 0;
}

template<class T>
inline MyQueue<T>::MyQueue(const MyQueue<T>& que)
{
	point<T>* p = que.curr;
	while (p != 0) {
		push(p->data);
		p = p->prev;
	}
}

template<class T>
inline MyQueue<T>::~MyQueue()
{
	point<T>* p = beg;
	while (p != 0) {
		p = beg->next;
		delete beg;
		beg = p;
	}
	beg = curr =  0;
}

template<class T>
inline T& MyQueue<T>::front()
{
	if (curr == 0)
		throw exception("пустая очередь");
	return curr->data;
}

template<class T>
inline T& MyQueue<T>::back()
{
	if (beg == 0)
		throw exception("пустая очередь");
	return beg->data;
}

template<class T>
inline int MyQueue<T>::size()
{
	return len;
}

template<class T>
inline bool MyQueue<T>::empty()
{
	return len == 0;
}

template<class T>
inline void MyQueue<T>::push(const T& val)
{
	point<T>* temp = make_point(val);
	// если пустой
	if (len == 0) {
		curr = beg = temp;
	}
	else {
		temp->next = beg;
		beg->prev = temp;
		beg = temp;
		// чтобы удалять с начала
		if (len == 1)
			curr->prev = temp;
	}
	len++;
}

template<class T>
inline void MyQueue<T>::pop()
{
	point<T>* temp = curr;
	curr = curr->prev;
	delete temp;
	len--;
	if (len != 0)
		curr->next = 0;
	else
		curr = beg = 0;
}
