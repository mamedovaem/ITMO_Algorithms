#pragma once
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <iostream>

#define PAGELIMIT 60

class FSAAllocator final
{
public:

	BOOL isSuccess;
	LPTSTR lpNxtPage;               // Address of the next page to ask for
	DWORD dwPages = 0;              // Count of pages gotten so far
	DWORD dwPageSize;
	//SIZE_T page_minimum;

	LPVOID lpvBase;               // Base address of the test memory
	LPTSTR lpPtr;                 // Generic character pointer
	SYSTEM_INFO sSysInfo;         // Useful information about the system

	const int pointeSize = sizeof(char*);


	int FSAType[6] = { 512, 256, 128, 64, 32, 16 };
	int FSASize[6];
	void* headPtr[6]{ nullptr };
	int pagesToFSA[PAGELIMIT]{ 0 };

	bool isInitialized = false;

	FSAAllocator()
	{}

	void Init();
	void Destroy();

	void* Alloc(size_t size);
	void Free(void* p);

	void WriteBytes(char* target, char* bytes, size_t size);
	char* ReadBytes(char* bytes, char* target, size_t size);

	INT PageFaultExceptionFilter(DWORD dwCode);

	VOID ErrorExit(LPTSTR lpMsg);

	VOID ReservePages(VOID);
	LPVOID CommitPage();

	void SetLayout(int type);

	int ChooseFSA(size_t size);
	int ChooseFSA(void* ptr);

	void SetFSASize();
};