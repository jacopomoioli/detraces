#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "user32.lib")

int main() {
    HANDLE hFile;
    char windowTitle[256];
    int length;
    HWND hwnd;
    DWORD bytesWritten;
    const char* fileName = "testfile.txt";
    const char* newFileName = "renamedfile.txt";
    const char* fileContent = "This is sample text written to the file.\n";

    // Get the handle of the foreground window
    hwnd = GetForegroundWindow();
    if (hwnd == NULL) {
        printf("Failed to get foreground window.\n");
        return 1;
    }

    // Get the window title
    length = GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    if (length == 0) {
        printf("Window has no title or an error occurred.\n");
        return 1;
    }

    // Print title to console
    printf("Foreground Window Title: %s\n", windowTitle);

    // Show a message box with the title
    MessageBoxA(NULL, windowTitle, "Active Window Title", MB_OK | MB_ICONINFORMATION);


    hFile = CreateFileA(
        fileName,                
        GENERIC_WRITE,           
        0,                       
        NULL,                    
        CREATE_ALWAYS,           
        FILE_ATTRIBUTE_NORMAL,   
        NULL);                   

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to create file (%lu)\n", GetLastError());
        return 1;
    }

    if (!WriteFile(hFile, fileContent, (DWORD)strlen(fileContent), &bytesWritten, NULL)) {
        printf("Failed to write to file (%lu)\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }

    printf("Wrote %lu bytes to %s\n", bytesWritten, fileName);

    CloseHandle(hFile);

    if (!MoveFileA(fileName, newFileName)) {
        printf("Failed to rename file (%lu)\n", GetLastError());
        return 1;
    }

    printf("File renamed to %s\n", newFileName);

    if (!DeleteFileA(newFileName)) {
        printf("Failed to delete file (%lu)\n", GetLastError());
        return 1;
    }

    printf("File %s deleted successfully.\n", newFileName);
    return 0;
}
