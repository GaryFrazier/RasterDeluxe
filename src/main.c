#define UNICODE
#include <stdio.h>
#include <windows.h>

int width;
int height;
BYTE* pixelBuffer;
BYTE* pixelBuffer2;
BYTE* pixelBufferTemp;

const int TARGET_FPS = 60;
const double TARGET_FRAME_TIME = 1000.0 / TARGET_FPS; // Target frame time in milliseconds

// Timer ID
#define IDT_TIMER1 1

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_TIMER:
		// called when frame timer triggers
		InvalidateRect(hwnd, NULL, TRUE);
        break;
	case WM_PAINT:
		; // nop
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps); // handle device context

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

void GameLoop(unsigned int frame) {
	memcpy(pixelBuffer2, pixelBuffer, width * height * 3);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int rowOffset = j * width * 3;
			int columnOffset = i * 3;
			int totalOffset = rowOffset + columnOffset;
			pixelBuffer2[totalOffset] = (frame + i) % 0xff;
			pixelBuffer2[totalOffset + 1] = (frame + j) % 0xff;
			pixelBuffer2[totalOffset + 2] = (frame + i + j) % 0xff;
		}
	}

	pixelBufferTemp = pixelBuffer2;
	pixelBuffer2 = pixelBuffer;
	pixelBuffer = pixelBufferTemp;
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

	pixelBuffer2 = calloc(width * height, 24);
	memset(pixelBuffer2, 125, width * height * 3);
	SetTimer(hwnd, IDT_TIMER1, TARGET_FRAME_TIME, NULL);

	MSG msg;

	unsigned int frame = 0;

	while (1)
	{
		GameLoop(frame);

		if (!GetMessage(&msg, NULL, 0, 0))
		{
			return 0;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// Record the start time of the frame
        DWORD startTime = GetTickCount();

        // Your rendering code goes here

        // Calculate the time elapsed since the start of the frame
        DWORD elapsedTime = GetTickCount() - startTime;

        // Calculate the remaining time to maintain the desired framerate
        int remainingTime = (int)(TARGET_FRAME_TIME - elapsedTime);

        // If the remaining time is positive, sleep for that duration
        if (remainingTime > 0)
        {
            Sleep(remainingTime);
        }

		frame++;
	}

	return 0;
}
