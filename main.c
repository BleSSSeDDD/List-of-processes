#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <TlHelp32.h>

int main()
{
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snap == NULL) return 1;

	Process32First(snap, &pe);

	do {
		HANDLE op = OpenProcess(PROCESS_ALL_ACCESS, 0, pe.th32ProcessID);
		if (op != NULL) {
			printf("%S\n", pe.szExeFile);
			CloseHandle(op);
		}
	} while (Process32Next(snap, &pe));

	return 0;
}
