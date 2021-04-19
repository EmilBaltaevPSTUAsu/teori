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
	// ищем
	for (auto it = fins.begin(); it != fins.end(); it++)
		if (*it == fin)
			return true;
	return false;
}

void Group::fin_select() {
	if (fins.size() == 0)
		throw exception("пусто");
	for (int i = 0; i < fins.size(); i++) {
		// если помечено на удаление
		if (fins[i].get_isDelete() == true)
			cout << "--] ";
		cout << i + 1 << ") " << fins[i] << endl;
	}
}

void Group::fin_select_by_department() {
	char buf[255];
	if (fins.size() == 0)
		throw exception("пусто");
	cout << "Подразделение? "; cin.ignore(); cin.getline(buf, 255);
	for (int i = 0; i < fins.size(); i++)
		if (fins[i].get_department() == string(buf)) {
			// если помечено на удаление
			if (fins[i].get_isDelete() == true)
				cout << "--] ";
			cout << i + 1 << ") " << fins[i] << endl;
		}
}

void Group::fin_insert() {
	int x, i = 1;
	Finance temp;
	auto it = fins.begin();
	cout << "\n1. В начало\n2. В конец\n3. С заданным номером\n>"; cin >> x;
	switch (x) {
	case 1: it = fins.begin(); break;	// начало
	case 2: it = fins.end(); break;		// конец
	case 3:								// по номеру
		cout << "Num? "; cin >> x;
		for (it = fins.begin(); it != fins.end(); i++, it++)
			if (i == x) {
				it = fins.insert(it, temp);
				x = 0;
				break;
			}
		// не нашли нужный номер
		if (x == 0) 
			throw exception("неверное значение");
		break;
	default:
		throw exception("неверное значение");
	}
	cin >> temp; 
	temp.set_id(fin_AI++);
	if (fin_contains(temp) == true)
		throw exception("Уже есть значение за данный период");
	fins.insert(it, temp);
	cout << "Успешно\n";
}

void Group::fin_update() {
	int x, key, i = 1;
	auto it = fins.begin();
	cout << "\n1. По ключу\n 2. По номеру\n>"; cin >> x;
	if (x != 1 && x != 2)
		throw exception("Неверный номер");
	cout << "key? "; cin >> key;
	for (it = fins.begin(); it != fins.end(); i++, it++) {
		if (x == 1 && it->get_id() == key)	// ключ
			break;		
		else if (x == 2 && i == key)		// номер
			break;
	}
	if(it == fins.end())
		throw exception("Нет заданного элемента\n");
	cin >> *it;
	cout << "Успешно" << endl;
}

void Group::fin_delete() {
	int x, key, i = 1;
	auto it = fins.begin();
	cout << "\n1. По ключу\n 2. По номеру\n>"; cin >> x;
	if (x != 1 && x != 2)
		throw exception("Неверный номер");
	cout << "key? "; cin >> key;
	// ищем
	for (it = fins.begin(); it != fins.end(); i++, it++) {
		if (x == 1 && it->get_id() == key)	// ключ
			break;
		else if (x == 2 && i == key)		// номер
			break;
	}
	if (it == fins.end())
		throw exception("Нет заданного элемента\n");
	it->set_isDelete(true);
	last_delete = it->get_id();
	cout << "Успешно" << endl;
}

void Group::fin_cancel_delete() {
	if (last_delete < 0)
		throw exception("Ничего не удалялось");
	auto it = fins.begin();
	// ищем
	for (it = fins.begin(); it != fins.end(); it++)
		if (it->get_id() == last_delete) {
			last_delete = -1;
			break;
		}
	if (it == fins.end())
		throw exception("Ошибка при отмене\n");
	it->set_isDelete(false);
	cout << "Успешно" << endl;
}

void Group::fin_save()
{
	string path;
	cout << "path? "; cin >> path;
	fstream f(path, ios::out);
	if (f.is_open() == false)
		throw exception("Файл не был открыт");
	f << fin_AI << endl;
	for (auto it = fins.begin(); it != fins.end(); it++) 
		// помеченные удаляем
		if(it->get_isDelete() == false)
			f << *it << endl;
	f.close();
	cout << "Успешно" << endl;
}

void Group::fin_read()
{
	string path;
	cout << "path? "; cin >> path;
	fstream f(path, ios::in);
	if (f.is_open() == false)
		throw exception("Файл не был открыт");
	fins.clear();
	Finance temp;
	f >> fin_AI;
	do {
		// последнее чтение вызывает исключение в сеттере класса
		try { f >> temp; } catch(exception& ex) {}
		if (f.eof())
			break;
		fins.push_back(temp);

	} while (!f.eof());
	f.close();
	cout << "Успешно" << endl;
}

// самые прибыльные годы
void Group::query1() {
	if(fins.size() == 0)
		throw exception("пусто");
	// собираем статистику
	map<string, map<int, vector<double>>> data;
	for (auto it = fins.begin(); it != fins.end(); it++) {
		// если добавлено подразделение
		if (data.find(it->get_department()) != data.end()) {
			if (data[it->get_department()].find(it->get_year()) != data[it->get_department()].end()) {
				data[it->get_department()][it->get_year()][0] += it->get_salary();
				data[it->get_department()][it->get_year()][1] += 1;
			}
			else {
				vector<double> temp; 
				temp.push_back(it->get_salary());	// сумма дохода
				temp.push_back(1);	// количество месяцев
				data[it->get_department()].insert(pair<int, vector<double>>(it->get_year(), temp));
			}
		}
		// если не добавлено
		else {
			map<int, vector<double>> temp;
			data.insert(pair<string, map<int, vector<double>>>(it->get_department(), temp));
		}
	}
	// анализируем статистику
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
		cout << "--- Самый прибыльный год " << year << endl;
	}
}

// Наиболее длинные периоды подразделений с доходом меньше среднего
void Group::query2() {
	set<string> deps;
	double avg = 0;
	// считаем сумму и запоминаем уникальные подразделения
	for (auto it = fins.begin(); it != fins.end(); it++) {
		deps.insert(it->get_department());
		avg += it->get_salary();
	}
	avg /= fins.size();
	cout << "Средний доход: " << avg << endl;
	vector<Finance> temp;
	for (auto it = deps.begin(); it != deps.end(); it++) {
		// отбираем по данному подразделению
		for (int i = 0; i < fins.size(); i++)
			if (fins[i].get_department() == *it)
				temp.push_back(fins[i]);
		// сортируем по датам
		sort(temp.begin(), temp.end(), [](Finance& fin1, Finance& fin2) {
			return  
				fin1.get_year() == fin2.get_year() && fin1.get_month() < fin2.get_month() || 
				fin1.get_year() < fin2.get_year();
		});
		int prev = 0, c = 0;
		int stY, stM, maxStY, maxStM, maxEndY, maxEndM;
		for (auto it2 = temp.begin(); it2 != temp.end(); it2++) {
			// если доход меньше среднего
			if (it2->get_salary() < avg) {
				// если начало периода
				if (c == 0) {
					stY = it2->get_year();
					stM = it2->get_month();
				}
				c++;
			}
			else {
				// запоминаем максимальный период
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
		cout << *it << " - наиболее длинный период равен " << prev << " с " << maxStM << "." << maxStY << " по " << maxEndM << "." << maxEndY << endl;
		temp.clear();
	}
}
