#include "Group.h"

Group::Group() {
	fins = vector<Finance>();
	fin_AI = 1;
	last_delete = -1;
}

Group::~Group() {
	fins.clear();
}

bool Group::fin_contains(Finance& fin)
{
	// ����
	for (auto it = fins.begin(); it != fins.end(); it++)
		if (*it == fin)
			return true;
	return false;
}

void Group::fin_select() {
	if (fins.size() == 0)
		throw exception("�����");
	for (int i = 0; i < fins.size(); i++) {
		// ���� �������� �� ��������
		if (fins[i].get_isDelete() == true)
			cout << "--] ";
		cout << i + 1 << ") " << fins[i] << endl;
	}
}

void Group::fin_select_by_department() {
	char buf[255];
	if (fins.size() == 0)
		throw exception("�����");
	cout << "�������������? "; cin.ignore(); cin.getline(buf, 255);
	for (int i = 0; i < fins.size(); i++)
		if (fins[i].get_department() == string(buf)) {
			// ���� �������� �� ��������
			if (fins[i].get_isDelete() == true)
				cout << "--] ";
			cout << i + 1 << ") " << fins[i] << endl;
		}
}

void Group::fin_insert() {
	int x, i = 1;
	Finance temp;
	auto it = fins.begin();
	cout << "\n1. � ������\n2. � �����\n3. � �������� �������\n>"; cin >> x;
	switch (x) {
	case 1: it = fins.begin(); break;	// ������
	case 2: it = fins.end(); break;		// �����
	case 3:								// �� ������
		cout << "Num? "; cin >> x;
		for (it = fins.begin(); it != fins.end(); i++, it++)
			if (i == x) {
				it = fins.insert(it, temp);
				x = 0;
				break;
			}
		// �� ����� ������ �����
		if (x == 0) 
			throw exception("�������� ��������");
		break;
	default:
		throw exception("�������� ��������");
	}
	cin >> temp; 
	temp.set_id(fin_AI++);
	if (fin_contains(temp) == true)
		throw exception("��� ���� �������� �� ������ ������");
	fins.insert(it, temp);
	cout << "�������\n";
}

void Group::fin_update() {
	int x, key, i = 1;
	auto it = fins.begin();
	cout << "\n1. �� �����\n 2. �� ������\n>"; cin >> x;
	if (x != 1 && x != 2)
		throw exception("�������� �����");
	cout << "key? "; cin >> key;
	for (it = fins.begin(); it != fins.end(); i++, it++) {
		if (x == 1 && it->get_id() == key)	// ����
			break;		
		else if (x == 2 && i == key)		// �����
			break;
	}
	if(it == fins.end())
		throw exception("��� ��������� ��������\n");
	cin >> *it;
	cout << "�������" << endl;
}

void Group::fin_delete() {
	int x, key, i = 1;
	auto it = fins.begin();
	cout << "\n1. �� �����\n 2. �� ������\n>"; cin >> x;
	if (x != 1 && x != 2)
		throw exception("�������� �����");
	cout << "key? "; cin >> key;
	// ����
	for (it = fins.begin(); it != fins.end(); i++, it++) {
		if (x == 1 && it->get_id() == key)	// ����
			break;
		else if (x == 2 && i == key)		// �����
			break;
	}
	if (it == fins.end())
		throw exception("��� ��������� ��������\n");
	it->set_isDelete(true);
	last_delete = it->get_id();
	cout << "�������" << endl;
}

void Group::fin_cancel_delete() {
	if (last_delete < 0)
		throw exception("������ �� ���������");
	auto it = fins.begin();
	// ����
	for (it = fins.begin(); it != fins.end(); it++)
		if (it->get_id() == last_delete) {
			last_delete = -1;
			break;
		}
	if (it == fins.end())
		throw exception("������ ��� ������\n");
	it->set_isDelete(false);
	cout << "�������" << endl;
}

void Group::fin_save()
{
	string path;
	cout << "path? "; cin >> path;
	fstream f(path, ios::out);
	if (f.is_open() == false)
		throw exception("���� �� ��� ������");
	f << fin_AI << endl;
	for (auto it = fins.begin(); it != fins.end(); it++) 
		// ���������� �������
		if(it->get_isDelete() == false)
			f << *it << endl;
	f.close();
	cout << "�������" << endl;
}

void Group::fin_read()
{
	string path;
	cout << "path? "; cin >> path;
	fstream f(path, ios::in);
	if (f.is_open() == false)
		throw exception("���� �� ��� ������");
	fins.clear();
	Finance temp;
	f >> fin_AI;
	do {
		// ��������� ������ �������� ���������� � ������� ������
		try { f >> temp; } catch(exception& ex) {}
		if (f.eof())
			break;
		fins.push_back(temp);

	} while (!f.eof());
	f.close();
	cout << "�������" << endl;
}

// ����� ���������� ����
void Group::query1() {
	if(fins.size() == 0)
		throw exception("�����");
	// �������� ����������
	map<string, map<int, vector<double>>> data;
	for (auto it = fins.begin(); it != fins.end(); it++) {
		// ���� ��������� �������������
		if (data.find(it->get_department()) != data.end()) {
			if (data[it->get_department()].find(it->get_year()) != data[it->get_department()].end()) {
				data[it->get_department()][it->get_year()][0] += it->get_salary();
				data[it->get_department()][it->get_year()][1] += 1;
			}
			else {
				vector<double> temp; 
				temp.push_back(it->get_salary());	// ����� ������
				temp.push_back(1);	// ���������� �������
				data[it->get_department()].insert(pair<int, vector<double>>(it->get_year(), temp));
			}
		}
		// ���� �� ���������
		else {
			map<int, vector<double>> temp;
			data.insert(pair<string, map<int, vector<double>>>(it->get_department(), temp));
		}
	}
	// ����������� ����������
	string dep;
	int year = 0;
	double salary = 0;
	for (auto it = data.begin(); it != data.end(); it++) {
		dep = it->first;
		cout << dep << endl;
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			cout << "- " << it2->first << ": " << it2->second[0] << endl;
			if (salary < it2->second[0]) {
				year = it2->first;
				salary = it2->second[0];
			}
		}
		cout << "--- ����� ���������� ��� " << year << endl;
	}
}

// �������� ������� ������� ������������� � ������� ������ ��������
void Group::query2() {
	set<string> deps;
	double avg = 0;
	// ������� ����� � ���������� ���������� �������������
	for (auto it = fins.begin(); it != fins.end(); it++) {
		deps.insert(it->get_department());
		avg += it->get_salary();
	}
	avg /= fins.size();
	cout << "������� �����: " << avg << endl;
	vector<Finance> temp;
	for (auto it = deps.begin(); it != deps.end(); it++) {
		// �������� �� ������� �������������
		for (int i = 0; i < fins.size(); i++)
			if (fins[i].get_department() == *it)
				temp.push_back(fins[i]);
		// ��������� �� �����
		sort(temp.begin(), temp.end(), [](Finance& fin1, Finance& fin2) {
			return  
				fin1.get_year() == fin2.get_year() && fin1.get_month() < fin2.get_month() || 
				fin1.get_year() < fin2.get_year();
		});
		int prev = 0, c = 0;
		int stY, stM, maxStY, maxStM, maxEndY, maxEndM;
		for (auto it2 = temp.begin(); it2 != temp.end(); it2++) {
			// ���� ����� ������ ��������
			if (it2->get_salary() < avg) {
				// ���� ������ �������
				if (c == 0) {
					stY = it2->get_year();
					stM = it2->get_month();
				}
				c++;
			}
			else {
				// ���������� ������������ ������
				if (prev < c) {
					prev = c;
					maxStY = stY;
					maxStM = stM;
					maxEndY = it2->get_year();
					maxEndM = it2->get_month();
				}
				c = 0;
			}
		}
		cout << *it << " - �������� ������� ������ ����� " << prev << " � " << maxStM << "." << maxStY << " �� " << maxEndM << "." << maxEndY << endl;
		temp.clear();
	}
}
