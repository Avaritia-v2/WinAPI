// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("WinAPI Practice");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("WinAPI Practice Title");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		650, 650,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Эрлихман Роман");
	HBRUSH tbrush;

	hdc = BeginPaint(hWnd, &ps);

	POINT tr1[6];
	const BYTE T[6] = { PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO };

	tr1[0].x = 50; tr1[0].y = 450;
	tr1[1].x = 150; tr1[1].y = 450;
	tr1[2].x = 200; tr1[2].y = 500;
	tr1[3].x = 100; tr1[3].y = 600;
	tr1[4].x = 0; tr1[4].y = 500;
	tr1[5].x = 50; tr1[5].y = 450;

	POINT polygon[13] = { tr1[0].x, tr1[0].y, tr1[1].x, tr1[1].y, tr1[2].x, tr1[2].y, tr1[3].x, tr1[3].y, tr1[4].x, tr1[4].y, tr1[5].x, tr1[5].y };
	tbrush = CreateSolidBrush(RGB(255, 255, 0));
	SelectObject(hdc, tbrush);
	Polygon(hdc, polygon, 5);

	PolyDraw(hdc, tr1, T, 6);

	TextOut(hdc, 500, 5, greeting, _tcslen(greeting));
	EndPaint(hWnd, &ps);

	return DefWindowProc(hWnd, message, wParam, lParam);
}