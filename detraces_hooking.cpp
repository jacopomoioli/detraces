#include <stdio.h>
#include <windows.h>
#include "detours.h"
#pragma comment(lib, "user32.lib")

int (WINAPI * pMessageBox)(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType) = MessageBox;
HWND (WINAPI * pGetForegroundWindow)() = GetForegroundWindow;
int (WINAPI * pGetWindowTextA)(HWND hWnd, LPSTR lpString, int nMaxCount) = GetWindowTextA;

int AddHook(void);
int RemoveHook(void);

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
	printf("GetWindowTextA(0x%p, %s, %d)\n", hWnd, lpString, nMaxCount);
	returnValue = pGetWindowTextA(hWnd, lpString, nMaxCount);
	return returnValue;
}

int AddHook(void) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	DetourAttach(&(PVOID&)pMessageBox, HookedMessageBox);
	DetourAttach(&(PVOID&)pGetForegroundWindow, HookedGetForegroundWindow);
	DetourAttach(&(PVOID&)pGetWindowTextA, HookedGetWindowTextA);
	
	DetourTransactionCommit();

	return 1;
}

int RemoveHook(void) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	DetourDetach(&(PVOID&)pMessageBox, HookedMessageBox);
	DetourDetach(&(PVOID&)pGetForegroundWindow, HookedGetForegroundWindow);
	DetourDetach(&(PVOID&)pGetWindowTextA, HookedGetWindowTextA);

	DetourTransactionCommit();

	return 1;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {

    switch (dwReason)  {
		case DLL_PROCESS_ATTACH:
			AddHook();
			break;
			
		case DLL_THREAD_ATTACH:
			break;
			
		case DLL_THREAD_DETACH:
			break;
			
		case DLL_PROCESS_DETACH:
			RemoveHook();
			break;
	}
	
    return TRUE;
}

