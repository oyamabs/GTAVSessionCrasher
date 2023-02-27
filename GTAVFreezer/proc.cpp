#include "proc.h"

DWORD getPid(const wchar_t* processname) {
	DWORD pId = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pEntry;
		pEntry.dwSize = sizeof(pEntry);

		if (Process32First(hSnap, &pEntry)) {
			bool found = false;

			do {
				if (!_wcsicmp(pEntry.szExeFile, processname)) {
					pId = pEntry.th32ProcessID;
					found = true;
				}

			} while (!found && Process32Next(hSnap, &pEntry));
		}
	}

	CloseHandle(hSnap);

	return pId;
}

/*
	https://cyberstoph.org/posts/2021/05/fun-with-processes-suspend-and-resume/ pour les deux fonction non documentées
*/

void freeze(DWORD pid) {
	// import de la fonction non documentée NtSuspendProcess
	
		// on obtient l'adresse de la fonction
	typedef LONG(NTAPI* NtSuspendProcess)(IN HANDLE ProcessHandle);
	NtSuspendProcess pNtSuspendProcess = (NtSuspendProcess)GetProcAddress(GetModuleHandle(L"ntdll"), "NtSuspendProcess");

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	pNtSuspendProcess(hProc);

	CloseHandle(hProc);
}


void unfreeze(DWORD pid) {
	// import de la fonction non documentée NtResumeProcess

		// on obtient l'adresse de la fonction
	typedef LONG(NTAPI* NtResumeProcess)(IN HANDLE ProcessHandle);
	NtResumeProcess pNtResumeProcess = (NtResumeProcess)GetProcAddress(GetModuleHandle(L"ntdll"), "NtResumeProcess");

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	pNtResumeProcess(hProc);

	CloseHandle(hProc);
}