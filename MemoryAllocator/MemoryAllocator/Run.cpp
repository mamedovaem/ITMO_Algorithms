// MemoryAllocator.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
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

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.