#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "user32.lib")

int main() {
    // Get the handle of the foreground window
    HWND hwnd = GetForegroundWindow();
    if (hwnd == NULL) {
        printf("Failed to get foreground window.\n");
        return 1;
    }

    // Get the window title
    char windowTitle[256];
    int length = GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    if (length == 0) {
        printf("Window has no title or an error occurred.\n");
        return 1;
    }

    // Print title to console
    printf("Foreground Window Title: %s\n", windowTitle);

    // Show a message box with the title
    MessageBoxA(NULL, windowTitle, "Active Window Title", MB_OK | MB_ICONINFORMATION);

    return 0;
}
