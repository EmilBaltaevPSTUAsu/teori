#include "HashTable.h"

HashTable::HashTable()
{
	arr = 0;
	count = 0;
	size = 0;
	count_collision = 0;
}

HashTable::~HashTable()
{
	clear();
}

void HashTable::clear() {
	if (count == 0)
		return;
	for (int i = 0; i < size; i++) {
		delete arr[i];
		arr[i] = 0;
	}
	count_collision = 0;
	count = 0;
}

void HashTable::init(int n)
{
	clear();
	delete[] arr;
	size = n;
	arr = new Person * [size];
	// обнуляем всё
	for (int i = 0; i < size; i++)
		arr[i] = 0;
}

void HashTable::show()
{
	if (count == 0)
		cout << "пусто" << endl;
	for (int i = 0; i < size; i++)
		// если не пусто
		if (arr[i] != 0)
			cout << i + 1 << ") " << *arr[i] << endl;
	cout << endl;
}

void HashTable::add()
{
	if (size == 0)
		throw exception("Еще не создано");
	int n;
	cout << "N? "; cin >> n;
	if (n < 1)
		throw exception("неверное значение");
	if (count + n > size)
		throw exception("слишком много значений");
	count += n;
	Person* p = 0;
	int hashInd;
	for (int i = 0; i < n; i++) {
		p = Person::random();
		hashInd = p->getHashCode() % size;
		// свободно
		if (arr[hashInd] == 0)
			arr[hashInd] = p;
		// занято
		else {
			count_collision++;
			for (int j = i + 1; j < size; j++) {
				// если нашли свободное место
				if (arr[j] == 0) {
					arr[j] = p;
					break;
				}
				// если прошли круг
				if ((j + 1) == i)
					throw exception("Мест больше нет");
				// если доходим до конца - встаем в начало
				if ((j + 1) == size)
					j = -1;
			}
		}
	}
	cout << "Успешно" << endl;
}

void HashTable::del()
{
	if (size == 0)
		throw exception("Еще не создано");
	string key;
	cout << "key? "; cin >> key;
	Person p("", "", "", key, "");
	int hashInd = p.getHashCode() % size;
	if (arr[hashInd] != 0 && *arr[hashInd] == p) {
		cout << "Нашли с первого раза\n";
		arr[hashInd] = 0;
		count--;
		return;
	}
	else {
		for (int j = hashInd + 1, c = 1; j < size; j++, c++) {
			// если нашли нужный
			if (arr[j] != 0 && *arr[j] == p) {
				cout << "Нашли после " << c << " шагов на " << j + 1 << " номере" << endl;
				arr[hashInd] = 0;
				count--;
				break;
			}
			// если доходим до конца - встаем в начало
			if ((j + 1) == size)
				j = -1;
			// если прошли круг
			if ((j + 1) == hashInd)
				throw exception("Нет такого ключа");
		}
	}
}

void HashTable::save()
{
	if (size == 0)
		throw exception("Еще не создано");
	fstream f("f.bin", ios::out);
	f << count << endl;
	for (int i = 0; i < size; i++)
		if (arr[i] != 0)
			f << *arr[i] << endl;
	f.close();
	cout << "Успешно" << endl;
}

void HashTable::read()
{
	clear();
	fstream f("f.bin", ios::in);
	f >> count;
	init(count);
	Person p;

	int i = 0;
	do {
		f >> p;
		if (f.eof())
			break;
		Person* temp = new Person(p);
		arr[i++] = temp;
	} while (!f.eof());
	f.close();
	if (i == 0)
		cout << "пусто";
	else {
		cout << "Успешно" << endl;
		count = i;
	}
}
