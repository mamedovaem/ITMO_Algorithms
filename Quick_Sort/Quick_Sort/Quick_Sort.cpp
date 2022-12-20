// Quick_Sort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <windows.h>
#include "profileapi.h"
#include "Array.h"
#include "Qsort.h"

int main()
{
    std::cout << "Hello World!\n";
 
    int vec[]{ 5,2,9,6,1,8,3, 5, 2, 7 };
    int vec1[]{ 9,9,9,9,9,8,1 };
    int vec2[100];
    
    for (int i = 0; i < 100; i++)
    {
        vec2[i] = vec[i % 10];
        std::cout << vec2[i] << ' ';
    }

    std::cout << std::endl;

    qsort(vec, 10, [](int a, int b) { return (a < b); });
 
    for (int i = 0; i < 10; i++)
    {
        std::cout << vec[i] << ' ';
    }

    std::cout << std::endl;

   qsort(vec2, 100, [](int a, int b) { return (a < b); });

    for (int i = 0; i < 100; i++)
    {
        std::cout << vec2[i] << ' ';
    }
    std::cout << std::endl;

    /*                               *** BENCHMARK *** 
    LARGE_INTEGER frequency{ 0 }; // ticks per second
    LARGE_INTEGER init_ticks{ 0 };
    LARGE_INTEGER curr_ticks{ 0 };

    std::ofstream fout;
    fout.open("TimeOutput.txt", std::ios_base::trunc);
    if (!fout.is_open())
    {
        std::cout << "Ошибка при открытии файла!" << std::endl;
    }
    else
    {
        QueryPerformanceFrequency(&frequency);

        for (int sz = 2; sz <= 50; sz++)
        {
            int* arr = new int[sz];

            for (int i = 0; i < sz; i++)
            {
                arr[i] = i;
            }
           QueryPerformanceCounter(&init_ticks);
         
           for (int j = 0; j < 10000; j++)
            {
               qsort(arr, sz, [](int a, int b) { return a > b; });
               qsort(arr, sz, [](int a, int b) { return a < b; });
            }
           QueryPerformanceCounter(&curr_ticks);

           fout << "qsort, size: " << sz << "; time: "
               << (double)((curr_ticks.QuadPart - init_ticks.QuadPart) * 1000/ frequency.QuadPart) << std::endl;
               
           QueryPerformanceCounter(&init_ticks);
        
           for (int j = 0; j < 10000; j++)
           {
               insert_sort(arr, sz, [](int a, int b) { return a > b; });
               insert_sort(arr, sz, [](int a, int b) { return a < b; });
           }
           QueryPerformanceCounter(&curr_ticks);

           fout << "insert sort, size: " << sz << "; time: "
               << (double)((curr_ticks.QuadPart - init_ticks.QuadPart) * 1000 / frequency.QuadPart) << std::endl;;
               
            delete[] arr;

        }

        fout.close();
    } */


    class test_class
    {
    public:

        int id_;
        std::string name_;

        test_class()
        {
            id_ = 0;
            name_ = "NoName";

        }

        test_class(int id, std::string name)
        {
            id_ = id;
            name_ = name;
        }

    };

    Array<test_class> test_arr;

    test_arr.insert(test_class(1, "Alice"));
    test_arr.insert(test_class(3, "Helen"));
    test_arr.insert(test_class(5, "Milena"));
    test_arr.insert(test_class(4, "Irma"));
    test_arr.insert(test_class(2, "Scarlet"));

    qsort(&test_arr[0], 5, [](test_class cl1, test_class cl2) { return cl1.id_ < cl2.id_; });

    for (auto it = test_arr.iterator(); it.has_current(); it.next())
    {
        std::cout << it.get().id_ << ' ' << it.get().name_ << std::endl;
    }

    qsort(&test_arr[0], 5, [](test_class cl1, test_class cl2) { return cl1.name_ > cl2.name_; });

    for (auto it = test_arr.iterator(); it.has_current(); it.next())
    {
        std::cout << it.get().id_ << ' ' << it.get().name_ << std::endl;
    }

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
