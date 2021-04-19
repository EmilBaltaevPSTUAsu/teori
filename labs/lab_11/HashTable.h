#pragma once
#include "Person.h"

class HashTable
{
private:
	Person** arr;
	int size;
	int count_collision;
	int count;

public:
	HashTable();
	~HashTable();
	void clear();

	int get_countCollision() { return count_collision; }

	void init(int n);
	void show();
	void add();
	void del();
	void save();
	void read();
};

