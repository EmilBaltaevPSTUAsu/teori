#include <iostream>
#include <conio.h>
#include "Group.h"

int main()
{
    system("chcp 1251");
    string x;
    Group group;
    while (true) {
        try {
            cout << "Нажмите любую клавишу для продолжения...";
            _getch();
            system("cls");
            cout << "\nsel. Данные о доходах";
            cout << "\nsel1. Данные о доходах подразделения";
            cout << "\nins.  Добавить";
            cout << "\nupd.  Изменить";
            cout << "\ndel.  Удалить";
            cout << "\ncan.  Удалить последнее изменение";
            cout << "\nread. Загрузить из файла";
            cout << "\nsave. Сохранить в файл";
            cout << "\nqu1.  Самые прибыльные годы подразделений";
            cout << "\nqu2.  Наиболее длинные периоды подразделений с доходом меньше среднего";
            cout << "\nesc.  Выйти\n>";
            cin >> x;
            
            if (x == "sel") group.fin_select();
            else if (x == "sel1") group.fin_select_by_department();
            else if (x == "ins") group.fin_insert();
            else if (x == "upd") group.fin_update();
            else if (x == "del") group.fin_delete();
            else if (x == "can") group.fin_cancel_delete();
            else if (x == "read") group.fin_read();
            else if (x == "save") group.fin_save();
            else if (x == "esc") return 0;
            else if (x == "qu1") group.query1();
            else if (x == "qu2") group.query2();
            else throw exception("неверный номер");
        }
        catch (exception& ex) {
            cout << "Ошибка: " << ex.what() << endl;
        }
    }
}
