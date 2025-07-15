#ifndef HOOK_H
#define HOOK_H

#include <windows.h>

int DetachHooks();
int AttachHooks();

HWND HookedGetForegroundWindow(
    void
);

int HookedGetWindowTextA(
	HWND hWnd, 
	LPSTR lpString, 
	int nMaxCount
);

HANDLE HookedCreateFileA (
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
);

BOOL HookedWriteFile (
  HANDLE hFile,
  LPCVOID lpBuffer,
  DWORD nNumberOfBytesToWrite,
  LPDWORD lpNumberOfBytesWritten,
  LPOVERLAPPED lpOverlapped
);

BOOL HookedCloseHandle (
  HANDLE hObject
);

BOOL HookedDeleteFileA(
  LPCSTR lpFileName
);

#endif