#define UNICODE
#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main(void) {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	const LPCWSTR windowClassName = L"Window Class";
	WNDCLASS windowClass = {};

	windowClass.lpfnWndProc = WindowProc;
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
		printf("Error creating window, with error code: %lu\n", GetLastError());
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);

	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}
