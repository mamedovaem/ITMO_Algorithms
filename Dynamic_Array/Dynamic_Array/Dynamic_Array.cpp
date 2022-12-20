// Dynamic_Array.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include "Array.h"

int main()
{
    Array<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    for (auto it = a.iterator(); it.has_current(); it.next())
        std::cout << it.get() << std::endl;
    for (auto it = a.reverseIterator(); it.has_current(); it.next())
    {
        it.set(5);
        std::cout << it.get() << std::endl;
    }

    Array<std::string> b;
    for (char ch = 'A'; ch <= 'Z'; ++ch)
        b.insert(std::string(1, ch));

    b.insert(0, "Q");
    b.insert(12, "8");
    b.remove(3);
    b.insert(b.size(), "4");

    for (int i = 0; i < b.size(); ++i)
        b[i] += (char) i;

    for (auto it = b.iterator(); it.has_current(); it.next())
        std::cout << it.get() << std::endl;
    
    Array<std::string> d;
    d = b;

    for (auto it = b.reverseIterator(); it.has_current(); it.next())
    {
        it.set("erased");
        std::cout << it.get() << std::endl;
    }

    for (auto it = d.iterator(); it.has_current(); it.next())
        std::cout << it.get() << std::endl;
  
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
