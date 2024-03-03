#define UNICODE
#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	printf("Message Handled\n");
}

int main(void) {
	printf("Hello World!\n");

	HINSTANCE hInstance = GetModuleHandle(NULL);
	const LPCSTR windowClassName = "Window Class";
	WNDCLASS windowClass = {};

	windowClass.lpfWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = windowClassName;

	RegisterClass(&windowClass);

	HWND hwnd = CreateWindowEx(
			0,                              // Optional window styles.
			windowClassName,                     // Window class
			L"Learn to Program Windows",    // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,       // Parent window    
			NULL,       // Menu
			hInstance,  // Instance handle
			NULL        // Additional application data
			);

	if (hwnd == NULL)
	{
		return 0;
	}

	return 0;
}
