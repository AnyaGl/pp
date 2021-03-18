#include <iostream>
#include <mutex>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <vector>


DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	std::cout << "thread number " + std::to_string(*static_cast<int*>(lpParam)) + " is working\n";

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
	std::vector<int> data;

	for (int i = 0; i < numberOfThreads; i++)
	{
		data.push_back(i);
	}
	for (int i = 0; i < numberOfThreads; i++)
	{
		handles[i] = CreateThread(NULL, 0, &ThreadProc, &data[i], CREATE_SUSPENDED, NULL);
		ResumeThread(handles[i]);
	}
	WaitForMultipleObjects(numberOfThreads, handles, true, INFINITE);

	return 0;
}
