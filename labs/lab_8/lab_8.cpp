#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "first.h"
#include "second.h"
#include "third.h"

int main()
{
    system("chcp 1251");

    cout << "\n1 часть\n"; first_exec();
    cout << "\n2 часть\n"; second_exec();
    cout << "\n3 часть\n"; third_exec();
}

