// MemoryAllocator.cpp
//

#include <iostream>
#include "FSAAllocator.h"

int main()
{
    FSAAllocator FSA{};
    FSA.Init();
    int size1 = 128;
    char* block1 = (char*)FSA.Alloc(size1);
	int size2 = 256;
	int* block2 = (int*)FSA.Alloc(size2);
	//FSA.Free(block2);
	//FSA.Free(block1);

	for (int i = 0; i < size1; ++i)
	{
		block1[i] = '0';
	}

	for (int i = 0; i < size2; ++i)
	{
		block2[i] = i;
	}

	for (int i = 0; i < size1; ++i)
	{
		std::cout<< block1[i] << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < size2; ++i)
	{
		std::cout << block2[i] << ' ';
	}
}
