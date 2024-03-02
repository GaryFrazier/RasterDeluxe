#define UNICODE
#include <stdio.h>
#include <windows.h>

int main(void) {
	printf("Hello World!\n");

	LPCSTR title = "Title!";
	LPCSTR message = "HEY!";
	MessageBoxA(NULL, message, title, MB_OKCANCEL);	
	return 0;
}
