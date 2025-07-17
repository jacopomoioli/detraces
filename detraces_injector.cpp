#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>


int GetPidFromProcessName(const char *ProcessName){
    HANDLE hProcessSnapshot;
    PROCESSENTRY32 pe32;
    int pid = 0;

    hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnapshot, &pe32)){
        CloseHandle(hProcessSnapshot);
        return 0;
    }

    while(Process32Next(hProcessSnapshot, &pe32)){
        if (lstrcmpA(ProcessName, pe32.szExeFile) == 0){
			pid = pe32.th32ProcessID;
			break;
		}
    }

    CloseHandle(hProcessSnapshot);

    return pid;    
}

HMODULE loadDetracesLibrary(){
    HMODULE hModule = LoadLibraryA("C:\\Users\\Jacopo\\source\\repos\\jacopomoioli\\detraces\\build\\detraces.dll");  //FIXME: hardcoded path
    return hModule;
}


int main(int argc, char *argv[]){
    int pid = 0;
    HANDLE hProcess = NULL;
    PTHREAD_START_ROUTINE pLoadLibrary = NULL;
    PVOID remoteBuffer;
    const char *targetProcess = argv[1];
    const char dll[] = ".\\detraces.dll";

    pid = GetPidFromProcessName(targetProcess);

    pLoadLibrary = (PTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle("Kernel32.dll"), "LoadLibraryA");

    printf("%d", pid);

    if (pid){
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD) pid);
        if (hProcess != NULL){
            remoteBuffer = VirtualAllocEx(hProcess, NULL, sizeof(dll), MEM_COMMIT, PAGE_READWRITE);
            WriteProcessMemory(hProcess, remoteBuffer, (LPVOID) dll, sizeof(dll), NULL);
            CreateRemoteThread(hProcess, NULL, 0, pLoadLibrary, remoteBuffer, 0, NULL);
            printf("remBuf addr: %p\n", remoteBuffer);
            CloseHandle(hProcess);
        }else{
            printf("Cannot open process\n");
        }
    }
}