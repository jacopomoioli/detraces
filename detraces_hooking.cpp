#include <stdio.h>
#include <windows.h>
#include "hooks.h"
#include "detours.h"
#pragma comment(lib, "user32.lib")

int AddHook(void) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	AttachHooks();
	DetourTransactionCommit();

	return 1;
}

int RemoveHook(void) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetachHooks();
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

