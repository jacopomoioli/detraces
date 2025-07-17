#define SECURITY_WIN32

#include <stdio.h>
#include <windows.h>
#include <sspi.h>
#include "hooks.h"
#include "detours.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Secur32.lib")


int AttachHooks();
int DetachHooks();

// MessageBox
int (WINAPI * pMessageBox)(
	HWND hWnd, 
	LPCTSTR lpText, 
	LPCTSTR lpCaption, 
	UINT uType
) = MessageBox;

int HookedMessageBox(
	HWND hWnd, 
	LPCTSTR lpText, 
	LPCTSTR lpCaption, 
	UINT uType
) {
	int returnValue;
	printf("[!] MessageBox(0x%p, %s, %s, %d)\n", hWnd, lpText, lpCaption, uType);
	returnValue = pMessageBox(hWnd, lpText, lpCaption, uType);
	return returnValue;
}


// GetForegroundWindow
HWND (WINAPI * pGetForegroundWindow)(
) = GetForegroundWindow;

HWND HookedGetForegroundWindow(){
	HWND returnValue;
	printf("[!] GetForegroundWindow()\n");
	returnValue = pGetForegroundWindow();
	return returnValue;
}


// GetWindowTextA
int (WINAPI * pGetWindowTextA)(
	HWND hWnd, 
	LPSTR lpString, 
	int nMaxCount
) = GetWindowTextA;

int HookedGetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount){
	int returnValue;
	printf("[!] GetWindowTextA(0x%p, 0x%p, %d)\n", hWnd, lpString, nMaxCount);
	returnValue = pGetWindowTextA(hWnd, lpString, nMaxCount);
	return returnValue;
}


// CreateFileA
HANDLE (WINAPI * pCreateFileA) (
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
) = CreateFileA;

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
	printf("[!] CreateFileA(%s, 0x%x, 0x%x, 0x%p, 0x%p, 0x%p, 0x%p)\n", lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	returnValue = pCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	return returnValue;
}


// WriteFile
BOOL (WINAPI * pWriteFile) (
	HANDLE hFile,
	LPCVOID lpBuffer,
	DWORD nNumberOfBytesToWrite,
	LPDWORD lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped
) = WriteFile;

BOOL HookedWriteFile (
  HANDLE hFile,
  LPCVOID lpBuffer,
  DWORD nNumberOfBytesToWrite,
  LPDWORD lpNumberOfBytesWritten,
  LPOVERLAPPED lpOverlapped
){
	BOOL returnValue;
	printf("[!] WriteFile(0x%p, %.*s, %d, %d, 0x%x)\n", hFile, nNumberOfBytesToWrite, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	returnValue = pWriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	return returnValue;
}


// ReadFile
BOOL (WINAPI * pReadFile) (
  HANDLE hFile,
  LPVOID lpBuffer,
  DWORD nNumberOfBytesToRead,
  LPDWORD lpNumberOfBytesRead,
  LPOVERLAPPED lpOverlapped
) = ReadFile;

BOOL HookedReadFile (
	HANDLE hFile,
	  LPVOID lpBuffer,
	  DWORD nNumberOfBytesToRead,
	  LPDWORD lpNumberOfBytesRead,
	  LPOVERLAPPED lpOverlapped
) {
	BOOL returnValue;
	printf("[!] ReadFile(0x%p, 0x%p, %d, 0x%p, 0x%x)\n", hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
	returnValue = pReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
	return returnValue;
}


// CloseHandle
BOOL (WINAPI * pCloseHandle) (
  HANDLE hObject
) = CloseHandle;

BOOL HookedCloseHandle (
  HANDLE hObject
){
	BOOL returnValue;
	printf("[!] CloseHandle(0x%p)\n", hObject);
	returnValue = CloseHandle(hObject);
	return returnValue;
}


// DeleteFileA
BOOL (WINAPI * pDeleteFileA)(
  LPCSTR lpFileName
) = DeleteFileA;


BOOL HookedDeleteFileA(
	LPCSTR lpFileName
){
	BOOL returnValue;
	printf("[!] DeleteFileA(%s)\n", lpFileName);
	returnValue = DeleteFileA(lpFileName);
	return returnValue;	
}


// SspiPrepareForCredRead
SECURITY_STATUS (WINAPI * pSspiPrepareForCredRead)(
	PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthIdentity,
	PCWSTR pszTargetName,
	PULONG pCredmanCredentialType,
	PCWSTR *ppszCredmanTargetName
) = SspiPrepareForCredRead;

SECURITY_STATUS HookedSspiPrepareForCredRead(
	PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthIdentity,
	PCWSTR pszTargetName,
	PULONG pCredmanCredentialType,
	PCWSTR *ppszCredmanTargetName
){
	SECURITY_STATUS returnValue;
	printf("[!] SspiPrepareForCredRead(0x%p, %s, %d, %s)\n", AuthIdentity, pszTargetName, *pCredmanCredentialType, ppszCredmanTargetName);
	returnValue = pSspiPrepareForCredRead(AuthIdentity, pszTargetName, pCredmanCredentialType, ppszCredmanTargetName);
	return returnValue;
}



int AttachHooks(){
	DetourAttach(&(PVOID&)pMessageBox, HookedMessageBox);
	DetourAttach(&(PVOID&)pGetForegroundWindow, HookedGetForegroundWindow);
	DetourAttach(&(PVOID&)pGetWindowTextA, HookedGetWindowTextA);
	DetourAttach(&(PVOID&)pCreateFileA, HookedCreateFileA);
	DetourAttach(&(PVOID&)pWriteFile, HookedWriteFile);
	DetourAttach(&(PVOID&)pReadFile, HookedReadFile);
	//DetourAttach(&(PVOID&)pCloseHandle, HookedCloseHandle);
	//DetourAttach(&(PVOID&)pDeleteFileA, HookedDeleteFileA);
	return 0;
}

int DetachHooks(){
	DetourDetach(&(PVOID&)pMessageBox, HookedMessageBox);
	DetourDetach(&(PVOID&)pGetForegroundWindow, HookedGetForegroundWindow);
	DetourDetach(&(PVOID&)pGetWindowTextA, HookedGetWindowTextA);
	DetourDetach(&(PVOID&)pCreateFileA, HookedCreateFileA);
	DetourDetach(&(PVOID&)pWriteFile, HookedWriteFile);
	DetourDetach(&(PVOID&)pReadFile, HookedReadFile);
	//DetourAttach(&(PVOID&)pCloseHandle, HookedCloseHandle);
	//DetourAttach(&(PVOID&)pDeleteFileA, HookedDeleteFileA);
	return 0;
}