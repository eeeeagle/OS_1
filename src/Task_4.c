#include <stdio.h>
#include <windows.h>

STARTUPINFO si;
PROCESS_INFORMATION pi;
WORD nopnop = 0x9090;
DWORD old_flags;
DWORD p = 0x004010B8;

int wmain(int argc, wchar_t* argv[])
{
	if (argc == 1)
	{
		puts("Locate path to file in argument\n\n"
			"EXAMPLE:\n"
			"   .../Task_4.exe <file_path>\n");
		_exit(EXIT_FAILURE);
	}
	
	CreateProcess(argv[1], L"", NULL, NULL, TRUE, 0, NULL, NULL, (STARTUPINFO*)&si, (PROCESS_INFORMATION*)&pi);
	HANDLE h = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, TRUE, pi.dwProcessId);
	VirtualProtectEx(h, (void*)p, 2, PAGE_EXECUTE_READWRITE, &old_flags);
	WriteProcessMemory(h, (void*)p, (void*)&nopnop, 2, NULL);
	CloseHandle(h);
	
	Sleep(2000);
	return 0;
}