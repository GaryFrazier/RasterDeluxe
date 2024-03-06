#define UNICODE
#include <stdio.h>
#include <windows.h>

int width;
int height;
BYTE* pixelBuffer;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:; // nop
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps); // handle device context

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1)); // wipe screen

		BITMAPINFOHEADER bmh = {
			sizeof(BITMAPINFOHEADER),
			width,
			height,
			1, // 1
			24, // 8 8 8
			BI_RGB,
			0,
			0,
			0,
			0,
			0
		};

		RGBQUAD rgbQuad = {1,1,1,0};

		// possibly use pallette 
		BITMAPINFO pixelBufferBitmapInfo = {
			bmh,
			{rgbQuad}
		};

		SetDIBitsToDevice(
			hdc,
			0, // x
			0, // y
			width,
			height,
			0, // lower left x
			0, // lower left y
			0,
			height,
			pixelBuffer,
			&pixelBufferBitmapInfo,
			DIB_RGB_COLORS
		);
		
		EndPaint(hwnd, &ps);

		break;
	case WM_CLOSE:
		DestroyWindow(hwnd); // Close the window
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // Send a quit message to terminate the application
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}

int main(void)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	const LPCWSTR windowClassName = L"Window Class";
	WNDCLASS windowClass = {};

	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = windowClassName;

	RegisterClass(&windowClass);

	HWND hwnd = CreateWindowEx(
		0,					 // Optional window styles.
		windowClassName,	 // Window class
		L"Raster Deluxe",	 // Window text
		WS_OVERLAPPEDWINDOW, // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,	   // Parent window
		NULL,	   // Menu
		hInstance, // Instance handle
		NULL	   // Additional application data
	);

	if (hwnd == NULL)
	{
		printf("Error creating window, with error code: %lu\n", GetLastError());
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	width = clientRect.right - clientRect.left;
	height = clientRect.bottom - clientRect.top;

	pixelBuffer = calloc(width * height, 24);
	memset(pixelBuffer, 125, width * height * 3);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
