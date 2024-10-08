#include "FSAAllocator.h"

void FSAAllocator::Init()
{
	if (!isInitialized)
	{
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

	//Look in which allocator we should write
	//write in the block at headPtr
	//change headPtr with headPtr+FSAType
	//if the free space is not enough, committing a page, setting layout, returning block's address
	
	int currentFSA = ChooseFSA(size);
	//if ((long int*)(*((long int*)head_ptr[currentFSA])) == nullptr)
	//if ((ReadBytes(((char*)(headPtr[currentFSA])), (char*)bytes, sizeof(char*))) == nullptr)
	if ((char*)headPtr[currentFSA] == nullptr)
	{
		void* ptr = headPtr[currentFSA];
		headPtr[currentFSA] = CommitPage();
		SetLayout(currentFSA);
		return ptr;
	}
	else
	{
		void* ptr = headPtr[currentFSA];
		headPtr[currentFSA] = (void*)ReadBytes((char*)(headPtr[currentFSA]), bytes, sizeof(char*));
		WriteBytes((char*)&headPtr[currentFSA], (char*)(&headPtr[currentFSA]) + FSASize[currentFSA], sizeof(char*));
		return ptr;
	}
}

void FSAAllocator::Free(void* p)
{
	//free memory
	// 
	//identify on which page and of which allocator the block is found
	//write a value of head_Ptr in the block
	//write the block's address in headPtr

	int currentFSA = ChooseFSA(p);
	WriteBytes((char*)p, (char*)(headPtr[currentFSA]), sizeof(char*));
	headPtr[currentFSA] = p;
}


void FSAAllocator::WriteBytes(char* target, char* bytes, size_t size)
{
	if (target == nullptr)
	{
		std::cout << "Target is nullptr!\n" << std::endl;
		return;
	}
	for (int i = 0; i < size; ++i)
	{
		target[i] = (char)((long int)(bytes + i) >> i);
	}
	std::cout << "INTO WRITEBYTES: " << std::endl;
	/*for (int i = 0; i < size; ++i)
	{
		std::cout << (void*)target[i] << " - target; " <<  (void*)&target[i] << " - target address; " << (void*)((int)(bytes + i) >> i)<< " - source";
	}*/
}
char* FSAAllocator::ReadBytes(char* bytes, char* target, size_t size)
{
	if (target == nullptr)
	{
		std::cout << "Target is nullptr!\n" << std::endl;
	}
	for (int i = 0; i < size; ++i)
	{

		target[i] = (char)((long int)((bytes + i)) >> (size - i - 1));
		//target[i] = (char)((int)(bytes + i) >> i);
	}
	std::cout << "INTO READBYTES: " << std::endl;
	/*for (int i = 0; i < size; ++i)
	{
		std::cout << (void*)target[i] << " - target; " << (void*)((int)(bytes + i) >> i) << " - source";
	}*/

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

	GetSystemInfo(&sSysInfo);     // Initialize the structure.

	_tprintf(TEXT("This computer has page size %d.\n"), sSysInfo.dwPageSize);

	dwPageSize = sSysInfo.dwPageSize;

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
	char* pageBase = static_cast<char*>(lpvBase) + (int)(dwPages - 1) * dwPageSize;
	char* ptr = pageBase;

	pagesToFSA[dwPages - 1] = currentFSA;

	if (headPtr[currentFSA] == nullptr)
	{
		//headPtr[currentFSA] = ptr;
	}
	else
	{
	//	headPtr[currentFSA] = (void*)ptr;
		//WriteBytes((char*)&headPtr[currentFSA], ptr, sizeof(char*));
	}

	for (int i = 0; (/*ptr + FSAType[currentFSA] < (char*)pageBase[currentFSA] + FSASize[currentFSA] - 1 && */(i < FSASize[currentFSA] / FSAType[currentFSA] - 1)); i++, ptr += FSAType[currentFSA])
	{
		if (i < FSASize[currentFSA] / FSAType[currentFSA] - 2)
		{
			WriteBytes(ptr, ptr + FSAType[currentFSA], sizeof(char*));
		}
		else {
			if (/*ptr + FSAType[type] < (char*)headPtr[type] + FSASize[type]&& */  i < FSASize[currentFSA] / FSAType[currentFSA] - 1)
			{
				WriteBytes(ptr, nullptr, sizeof(nullptr));
			}
		}

		//std::cout << (void*) (ptr) << " - address; " << (void*) (*ptr) << " - value " << std::endl;
	}
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
	FSASize[0] = (int)dwPageSize;
	FSASize[1] = (int)dwPageSize;
	FSASize[2] = (int)dwPageSize;
	FSASize[3] = (int)dwPageSize;
	FSASize[4] = (int)dwPageSize;
	FSASize[5] = (int)dwPageSize;

}