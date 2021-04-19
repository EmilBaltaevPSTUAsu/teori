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
	// �������� ��
	for (int i = 0; i < size; i++)
		arr[i] = 0;
}

void HashTable::show()
{
	if (count == 0)
		cout << "�����" << endl;
	for (int i = 0; i < size; i++)
		// ���� �� �����
		if (arr[i] != 0)
			cout << i + 1 << ") " << *arr[i] << endl;
	cout << endl;
}

void HashTable::add()
{
	if (size == 0)
		throw exception("��� �� �������");
	int n;
	cout << "N? "; cin >> n;
	if (n < 1)
		throw exception("�������� ��������");
	if (count + n > size)
		throw exception("������� ����� ��������");
	count += n;
	Person* p = 0;
	int hashInd;
	for (int i = 0; i < n; i++) {
		p = Person::random();
		hashInd = p->getHashCode() % size;
		// ��������
		if (arr[hashInd] == 0)
			arr[hashInd] = p;
		// ������
		else {
			count_collision++;
			for (int j = i + 1; j < size; j++) {
				// ���� ����� ��������� �����
				if (arr[j] == 0) {
					arr[j] = p;
					break;
				}
				// ���� ������ ����
				if ((j + 1) == i)
					throw exception("���� ������ ���");
				// ���� ������� �� ����� - ������ � ������
				if ((j + 1) == size)
					j = -1;
			}
		}
	}
	cout << "�������" << endl;
}

void HashTable::del()
{
	if (size == 0)
		throw exception("��� �� �������");
	string key;
	cout << "key? "; cin >> key;
	Person p("", "", "", key, "");
	int hashInd = p.getHashCode() % size;
	if (arr[hashInd] != 0 && *arr[hashInd] == p) {
		cout << "����� � ������� ����\n";
		arr[hashInd] = 0;
		count--;
		return;
	}
	else {
		for (int j = hashInd + 1, c = 1; j < size; j++, c++) {
			// ���� ����� ������
			if (arr[j] != 0 && *arr[j] == p) {
				cout << "����� ����� " << c << " ����� �� " << j + 1 << " ������" << endl;
				arr[hashInd] = 0;
				count--;
				break;
			}
			// ���� ������� �� ����� - ������ � ������
			if ((j + 1) == size)
				j = -1;
			// ���� ������ ����
			if ((j + 1) == hashInd)
				throw exception("��� ������ �����");
		}
	}
}

void HashTable::save()
{
	if (size == 0)
		throw exception("��� �� �������");
	fstream f("f.bin", ios::out);
	f << count << endl;
	for (int i = 0; i < size; i++)
		if (arr[i] != 0)
			f << *arr[i] << endl;
	f.close();
	cout << "�������" << endl;
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
		cout << "�����";
	else {
		cout << "�������" << endl;
		count = i;
	}
}
