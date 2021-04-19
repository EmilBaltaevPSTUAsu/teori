#include "Person.h"

Person::Person()
{
    fname = sname = tname = phone = adress = "";
}

Person::Person(string f, string s, string t, string p, string a)
{
    fname = f;
    sname = s;
    tname = t;
    phone = p;
    adress = a;
}

Person::Person(const Person& p)
{
    fname = p.fname;
    sname = p.sname;
    tname = p.tname;
    phone = p.phone;
    adress = p.adress;
}

bool Person::operator==(const Person& p)
{
    return p.phone == phone;
}

int Person::getHashCode() 
{
    int sum = 0;
    for (int k = 0; k < phone.length(); k++)
        sum = sum + int(phone[k]);
    return  sum;
}

Person* Person::random()
{
    Person* p = new Person;
    string F[30] = { "Загидуллин","Панкина","Яндиева","Квартирова","Малышева","Набережный","Осинцев","Строганова",
        "Клоков","Сиянскиха","Снегирёв","Педича","Яхимовича","Виноградов","Янгосярова","Турчанинова","Крайнева",
        "Абоимова","Икрамов","Лисицына","Терещенко","Антипов","Богомолов","Смирновский","Янцижин","Голышева","Дюженкова","Пашина","Корбылева","Болокана" };
    p->fname = F[rand() % 30];
    string N[40] = { "Эльвира","Владислава","Алина","Герман","Прокл","Всеслава","Кондратий","Валерия","Раиса",
        "Борис","Маргарита","Бронислав","Кира","Емельян","Богдан","Пахом","Эрнест","Марина","Майя","Юлия",
        "Марк","Никита","Трофим","Прохор","Ульян","Роман","Арсений","Кондратий","Терентий","Владислав","Вера",
        "Лада","Ярослава","Ника","Ираида","Наталья","Софья","Пелагея","Роза","Василиса" };
    p->sname = N[rand() % 40];
    string O[20] = { "Архипович","Кузьмевна","Самсонович","Вячеславович","Юлиевна","Яковович","Сергеевич","Панкратиевич","Кондратиевич","Станиславовна",
        "Несторович","Ипполитович","Казимировна","Николаевна","Геннадиевна","Ульянович","Артемиевич","Станиславовна","Сергеевич","Филипповна" };
    p->tname = O[rand() % 20];
    string Adress[20] = { "Москва","Санкт-Петербург","Новосибирск","Пермь","Нижний-Тагил","Краснодар","Ростов","Смоленск","Тамбов","Казань","Хабаровск",
        "Владивосток","Самара","Тюмень","Норильск","Уфа","Челябинск","Воронеж","Сочи","Махачкала" };
    p->adress = Adress[rand() % 20];
    char nums[10] = { '0','1','2','3','4','5','6','7','8','9' };
    p->phone = "8";
    for (int i = 1; i < 11; i++)
        p->phone += nums[rand() % 10];   
    return p;
}

ostream& operator<<(ostream& out, const Person& fin)
{
    out << fin.fname << " " << fin.sname << " " << fin.tname << " " << fin.phone << " " << fin.adress;
    return out;
}

istream& operator>>(istream& in, Person& fin)
{
    cout << "ФИО? "; in >> fin.fname >> fin.sname >> fin.tname;
    cout << "Телефон? "; in >> fin.phone;
    cout << "Адрес? "; in >> fin.adress;
    return in;
}

fstream& operator<<(fstream& out, const Person& fin)
{
    out << fin.fname << " " << fin.sname << " " << fin.tname << " " << fin.phone << " " << fin.adress;
    return out;
}

fstream& operator>>(fstream& in, Person& fin)
{
    in >> fin.fname >> fin.sname >> fin.tname >> fin.phone >> fin.adress;
    return in;
}
