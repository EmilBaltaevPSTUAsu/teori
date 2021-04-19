#pragma once

template <class T>
struct point
{
	T data;
	point<T>* next;
	point<T>* prev;
};

template <class T>
point<T>* make_point(const T& data) {
	point<T>* p = new point<T>;
	p->data = data;
	p->next = 0;
	p->prev = 0;
	return p;
}
