#include "FSAAllocator.h"

void FSAAllocator::Init()
{
	if (!isInitialized)
	{
		//SetPrivilege();
		ReservePages();
		SetFSASize();
		for (int i = 0; i < 6;++i)
		{

			headPtr[i] = (void*)CommitPage();
			SetLayout(i);
			pagesToFSA[i] = i;
		}
		isInitialized = true;
	}

}

void FSAAllocator::Destroy()
{
	isInitialized = false;
	//free memory and return pages to OS

	isSuccess = VirtualFree(
		lpvBase,       // Base address of block
		0,             // Bytes of committed pages
		MEM_RELEASE);  // Decommit the pages

	_tprintf(TEXT("Release %s.\n"), isSuccess ? TEXT("succeeded") : TEXT("failed"));
}

void* FSAAllocator::Alloc(size_t size)
{
	//alloc memory
	char bytes[8];
	//ќпределить в какой тип аллокатора записац
	//записать в блок по адресу head_ptr
	//исправиц значение head_ptr head_ptr+FSA_type
	// return head_ptr - FSA_type
	// если размер не позвол€ет - выдел€ем страницу, размечаем, возвращаем блок
	int currentFSA = ChooseFSA(size);
	//if ((long int*)(*((long int*)head_ptr[currentFSA])) == nullptr)
	//if ((ReadBytes(((char*)(headPtr[currentFSA])), (char*)bytes, sizeof(char*))) == nullptr)
	if ((void*)*((char*)headPtr[currentFSA]) == nullptr)
	{
		void* ptr = headPtr[currentFSA];
		headPtr[currentFSA] = CommitPage();
		SetLayout(currentFSA);
		return ptr;
	}
	else
	{
		void* ptr = headPtr[currentFSA];
		headPtr[currentFSA] = (void*)*((char*)headPtr[currentFSA]);
		WriteBytes((char*)&headPtr[currentFSA], (char*)(&headPtr[currentFSA]) + FSASize[currentFSA], sizeof(char*));
		return ptr;
	}
}

void FSAAllocator::Free(void* p)
{
	//free memory
	//определить на какой странице и к какому аллокатору относитс€ блок
	//записать в блок значение хед птр
	//записать в хед птр адрес блока

	int currentFSA = ChooseFSA(p);
	//*(char**)p = (char*)head_ptr[currentFSA];
	WriteBytes((char*)p, (char*)(headPtr[currentFSA]), sizeof(char*));
	headPtr[currentFSA] = p;
}

void FSAAllocator::WriteBytes(char* target, char* bytes, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		//*(*((char**)(target) + i)) = *(*((char**)(bytes) + i));

		target[i] = (char)(bytes + i);
	}
}
char* FSAAllocator::ReadBytes(char* bytes, char* target, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		//(*((char**)(target)[i])) = (*((char**)(bytes)[i]));
		target[i] = (char)(bytes + i);
	}

	return target;
}

INT FSAAllocator::PageFaultExceptionFilter(DWORD dwCode)
{
	LPVOID lpvResult;

	// If the exception is not a page fault, exit.

	if (dwCode != EXCEPTION_ACCESS_VIOLATION)
	{
		_tprintf(TEXT("Exception code = %d.\n"), dwCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	_tprintf(TEXT("Exception is a page fault.\n"));

	// If the reserved pages are used up, exit.

	if (dwPages >= PAGELIMIT)
	{
		_tprintf(TEXT("Exception: out of pages.\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Otherwise, commit another page.
	lpvResult = CommitPage();

	if (lpvResult == NULL)
	{
		_tprintf(TEXT("VirtualAlloc failed.\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Continue execution where the page fault occurred.

	return EXCEPTION_CONTINUE_EXECUTION;
}


VOID FSAAllocator::ErrorExit(LPTSTR lpMsg)
{
	_tprintf(TEXT("Error! %s with error code of %ld.\n"),
		lpMsg, GetLastError());
	exit(0);
}

VOID FSAAllocator::ReservePages(VOID)
{
	//BOOL bSuccess;                // Flag
	DWORD i;                      // Generic counter
	//page_minimum = GetLargePageMinimum();
	/*if (!page_minimum)
	{
		_tprintf(TEXT("Large pages are not supported.\n"));

		ExitProcess(GetLastError());
	}*/
	GetSystemInfo(&sSysInfo);     // Initialize the structure.

	_tprintf(TEXT("This computer has page size %d.\n"), sSysInfo.dwPageSize);

	dwPageSize = sSysInfo.dwPageSize;
	//dwPageSize = page_minimum;

	// Reserve pages in the virtual address space of the process.

	lpvBase = VirtualAlloc(
		NULL,                 // System selects address
		PAGELIMIT * dwPageSize, // Size of allocation
		MEM_RESERVE,          // Allocate reserved pages
		PAGE_NOACCESS);       // Protection = no access
	if (lpvBase == NULL)
	{
		_tprintf(TEXT("VirtualAlloc failed.\n"));

		ExitProcess(GetLastError());
	}
	//ErrorExit(TEXT("VirtualAlloc reserve failed."));

	lpPtr = lpNxtPage = (LPTSTR)lpvBase;

	// Use structured exception handling when accessing the pages.
	// If a page fault occurs, the exception filter is executed to
	// commit another page from the reserved block of pages.

	for (i = 0; i < PAGELIMIT * dwPageSize; i++)
	{
		__try
		{
			//Write to memory.

			//lpPtr[i] = '0';
		}

		// If there's a page fault, commit another page and try again.

		__except (PageFaultExceptionFilter(GetExceptionCode()))
		{		// This code is executed only if the filter function
				// is unsuccessful in committing the next page.

			_tprintf(TEXT("Exiting process.\n"));

			ExitProcess(GetLastError());

		}



	}
}

LPVOID FSAAllocator::CommitPage()
{
	LPVOID lpvResult;

	lpvResult = VirtualAlloc(
		(LPVOID)lpNxtPage, // Next page to commit
		dwPageSize,         // Page size, in bytes
		MEM_COMMIT,         // Allocate a committed page
		PAGE_READWRITE);    // Read/write access

	if (lpvResult == NULL)
	{
		_tprintf(TEXT("VirtualAlloc failed.\n"));
		return NULL;
	}
	else
	{
		_tprintf(TEXT("Allocating another page.\n"));
	}

	// Increment the page count, and advance lpNxtPage to the next page.

	dwPages++;
	lpNxtPage = (LPTSTR)((PCHAR)lpNxtPage + dwPageSize);

	return lpvResult;
}

void FSAAllocator::SetLayout(int currentFSA)
{
	char* target = (char*)headPtr[currentFSA];
	char* ptr = static_cast<char*>(lpvBase) + (int)(dwPages - 1) * dwPageSize;
	headPtr[currentFSA] = (void*)(static_cast<char*>(lpvBase) + (int)(dwPages - 1) * dwPageSize);
	pagesToFSA[dwPages - 1] = currentFSA;
	if (headPtr[currentFSA] = nullptr)
	{
		headPtr[currentFSA] = ptr;
	}
	else
	{
		//head_ptr[type] = (void*)(*((char*)head_ptr[type]));
		WriteBytes((char*)&headPtr[currentFSA], (char*)ptr, sizeof(char*));

	}

	for (int i = 0; (ptr + FSAType[currentFSA] < (char*)headPtr[currentFSA] + FSASize[currentFSA] - 1)&&(i < FSASize[currentFSA]/FSAType[currentFSA] - 1); i++, ptr += FSAType[currentFSA])
	{
		if (/*ptr + 2 * FSAType[type] < (char*)headPtr[type] + FSASize[type] - 1*/ i < FSASize[currentFSA] / FSAType[currentFSA] - 2)
		{
			//*ptr =(ptr + FSA_type[i]);
			WriteBytes(ptr, ptr + FSAType[currentFSA], sizeof(char*));
		}
		else if (/*ptr + FSAType[type] < (char*)headPtr[type] + FSASize[type]&& */  i < FSASize[currentFSA] / FSAType[currentFSA] - 1)
		{
			//*ptr = (char)nullptr;
			WriteBytes((char*)ptr, nullptr, sizeof(nullptr));
		}
	}
	/*ptr = (char*)head_ptr[type] + FSA_size[type];*/

}

int FSAAllocator::ChooseFSA(size_t size)
{
	if (size > 512)
	{
		return -1;
	}
	for (int i = 0, threshold = 256; i < 6 && threshold > 0; ++i, threshold /= 2)
	{
		if (size > threshold)
		{
			return i;
		}
	}
}

int FSAAllocator::ChooseFSA(void* ptr)
{
	int pageNumber = (char*)ptr - (char*)lpvBase;
	if (dwPageSize)
	{
		pageNumber /= dwPageSize;
	}

	return pagesToFSA[pageNumber];
}

void FSAAllocator::SetFSASize()
{
	// from FSA 512 to FSA 16  
   //6144 + pointer_size,
	FSASize[0] = (int)dwPageSize;
	FSASize[1] = (int)dwPageSize;
	FSASize[2] = (int)dwPageSize;
	FSASize[3] = (int)dwPageSize;
	FSASize[4] = (int)dwPageSize;
	FSASize[5] = (int)dwPageSize;

}