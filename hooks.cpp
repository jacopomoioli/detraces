#include <stdio.h>
#include <windows.h>
#include "hooks.h"
#include "detours.h"

#pragma comment(lib, "user32.lib")

int AttachHooks();
int DetachHooks();

int (WINAPI * pMessageBox)(
	HWND hWnd, 
	LPCTSTR lpText, 
	LPCTSTR lpCaption, 
	UINT uType
) = MessageBox;

HWND (WINAPI * pGetForegroundWindow)() = GetForegroundWindow;

int (WINAPI * pGetWindowTextA)(
	HWND hWnd, 
	LPSTR lpString, 
	int nMaxCount
) = GetWindowTextA;

HANDLE (WINAPI * pCreateFileA) (
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
) = CreateFileA;

BOOL (WINAPI * pWriteFile) (
  HANDLE hFile,
  LPCVOID lpBuffer,
  DWORD nNumberOfBytesToWrite,
  LPDWORD lpNumberOfBytesWritten,
  LPOVERLAPPED lpOverlapped
) = WriteFile;

BOOL (WINAPI * pCloseHandle) (
  HANDLE hObject
) = CloseHandle;

BOOL (WINAPI * pDeleteFileA)(
  LPCSTR lpFileName
) = DeleteFileA;


int HookedMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType) {
	int returnValue;
	printf("MessageBox(0x%p, %s, %s, %d)\n", hWnd, lpText, lpCaption, uType);
	returnValue = pMessageBox(hWnd, lpText, lpCaption, uType);
	return returnValue;
}

HWND HookedGetForegroundWindow(){
	HWND returnValue;
	printf("GetForegroundWindow()\n");
	returnValue = pGetForegroundWindow();
	return returnValue;
}

int HookedGetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount){
	int returnValue;
	printf("GetWindowTextA(0x%p, 0x%p, %d)\n", hWnd, lpString, nMaxCount);
	returnValue = pGetWindowTextA(hWnd, lpString, nMaxCount);
	return returnValue;
}

HANDLE HookedCreateFileA (
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
){
	HANDLE returnValue;
	printf("CreateFileA(%s, 0x%x, 0x%x, 0x%p, 0x%p, 0x%p, 0x%p)\n", lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	returnValue = pCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	return returnValue;
}

BOOL HookedWriteFile (
  HANDLE hFile,
  LPCVOID lpBuffer,
  DWORD nNumberOfBytesToWrite,
  LPDWORD lpNumberOfBytesWritten,
  LPOVERLAPPED lpOverlapped
){
	BOOL returnValue;
	printf("WriteFile(0x%p, %s, %d, %d, 0x%x)\n", hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	returnValue = pWriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	return returnValue;
}

/*
BOOL HookedCloseHandle (
  HANDLE hObject
){

}

BOOL HookedDeleteFileA(
  LPCSTR lpFileName
){

}
*/

int AttachHooks(){
	DetourAttach(&(PVOID&)pMessageBox, HookedMessageBox);
	DetourAttach(&(PVOID&)pGetForegroundWindow, HookedGetForegroundWindow);
	DetourAttach(&(PVOID&)pGetWindowTextA, HookedGetWindowTextA);
	DetourAttach(&(PVOID&)pCreateFileA, HookedCreateFileA);
	DetourAttach(&(PVOID&)pWriteFile, HookedWriteFile);
	return 0;
}

int DetachHooks(){
	DetourDetach(&(PVOID&)pMessageBox, HookedMessageBox);
	DetourDetach(&(PVOID&)pGetForegroundWindow, HookedGetForegroundWindow);
	DetourDetach(&(PVOID&)pGetWindowTextA, HookedGetWindowTextA);
	DetourDetach(&(PVOID&)pCreateFileA, HookedCreateFileA);
	DetourDetach(&(PVOID&)pWriteFile, HookedWriteFile);
	return 0;
}