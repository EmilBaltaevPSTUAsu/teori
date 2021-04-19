#include <iostream>
#include "HashTable.h"

int main()
{
	system("chcp 1251");
    srand(time(0));
    int x;
    HashTable table;
    while (true) {
        try {
            cout << "\n1. Создать";
            cout << "\n2. Добавить";
            cout << "\n3. Удалить";
            cout << "\n4. Посмотреть";
            cout << "\n5. Количество коллизий";
            cout << "\n6. Очистить";
            cout << "\n7. Сохранить";
            cout << "\n8. Загрузить";
            cout << "\n9. Выйти\n>";
            cin >> x;

            switch (x) {
            case 1: cout << "N? "; cin >> x; table.init(x); cout << "Успешно" << endl; break;
            case 2: table.add();  break;
            case 3: table.del(); break;
            case 4: table.show(); break;
            case 5: cout << "Значение = " << table.get_countCollision(); break;
            case 6: table.clear(); cout << "Успешно\n"; break;
            case 7: table.save(); break;
            case 8: table.read(); break;
            case 9: return 0;
            }
        }
        catch (exception& ex) {
            cout << "Ошибка: " << ex.what() << endl;
        }
    }
}
