// MemoryAllocator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "FSAAllocator.h"

int main()
{
    FSAAllocator FSA{};
    FSA.Init();
    int size1 = 128;
    char* block1 = (char*)FSA.Alloc(size1);


	__try
	{
		for (int i = 0; i < size1; ++i)
		{
			block1[i] = '0';
		}
	}

	// If there's a page fault, commit another page and try again.

	__except (FSA.PageFaultExceptionFilter(GetExceptionCode()))
	{		// This code is executed only if the filter function
			// is unsuccessful in committing the next page.

		_tprintf(TEXT("Exiting process.\n"));

		ExitProcess(GetLastError());

	}


	for (int i = 0; i < size1; ++i)
	{
		std::cout<< block1[i] << ' ';
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