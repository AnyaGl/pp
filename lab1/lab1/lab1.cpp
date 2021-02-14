#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	std::cout << "thread number " << *static_cast<int*>(lpParam) << " is working\n";

	ExitThread(0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		return 1;
	}
	int numberOfThreads = std::stoi(argv[1]);

	HANDLE* handles = new HANDLE[numberOfThreads];

	for (int i = 0; i < numberOfThreads; i++)
	{
		handles[i] = CreateThread(NULL, 0, &ThreadProc, new int(i), CREATE_SUSPENDED, NULL);
		ResumeThread(handles[i]);
	}

	WaitForMultipleObjects(numberOfThreads, handles, true, INFINITE);

	return 0;
}
