#include "Finance.h"

Finance::Finance(int i, string d, int y, int m, double s)
{
    id = i;
    dep = d;
    set_year(y);
    set_month(m);
    set_salary(s);
}

void Finance::set_year(int y)
{
    if (y < 1900 || y > 2021)
        throw exception("Не верный год");
    year = y;
}

void Finance::set_month(int m)
{
    if(m < 1 || m> 12)
        throw exception("Не верный месяц");
    month = m;
}

void Finance::set_salary(double s)
{
    if(s < 0)
        throw exception("Не верный доход");
    salary = s;
}

bool Finance::operator==(const Finance& fin)
{
    return dep == fin.dep &&  year == fin.year && month == fin.month;
}

ostream& operator<<(ostream& out, const Finance& fin)
{
    out << fin.id << ": " << fin.dep << " - ";
    if (fin.month < 10)
        out << "0";
    out << fin.month << "." << fin.year << " = " << fin.salary << " у.е.";
    return out;
}

istream& operator>>(istream& in, Finance& fin)
{
    int temp;
    char buf[255];
    in.ignore();
    cout << "Подраздаление? "; in.getline(buf, 255); fin.dep = string(buf);
    cout << "Год? "; in >> temp; fin.set_year(temp);
    cout << "Месяц? "; in >> temp; fin.set_month(temp);
    cout << "Доход? "; in >> temp; fin.set_salary(temp);
    return in;
}

fstream& operator<<(fstream& out, const Finance& fin)
{
    out << fin.id << " " << fin.year << " " << fin.month << " " << fin.salary << endl;
    out << fin.dep;
    return out;
}

fstream& operator>>(fstream& in, Finance& fin)
{
    int temp;
    char buf[255];
    in >> fin.id;
    in >> temp; fin.set_year(temp);
    in >> temp; fin.set_month(temp);
    in >> temp; fin.set_salary(temp);
    in.ignore();
    in.getline(buf, 255); fin.dep = string(buf);
    return in;
}
