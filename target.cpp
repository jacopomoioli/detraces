#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "user32.lib")

int main(void){
    MessageBox(NULL, "test", "test", MB_OKCANCEL);
    return 0;
}