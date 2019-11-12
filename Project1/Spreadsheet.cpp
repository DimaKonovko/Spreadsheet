#include "Spreadsheet.h"

// app entry point
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
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
	wcex.hbrBackground = (HBRUSH)(COLOR_MENU + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Spreadsheet",
			NULL);

		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(int)WND_WIDTH,
		(int)WND_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd) {
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Error",
			NULL);

		return 1;
	}
	ShowWindow(hWnd, nCmdShow);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static RECT WindowRect;

	switch (uMsg)
	{
	case WM_SIZE:
		GetClientRect(hWnd, &WindowRect);
		InvalidateRect(hWnd, &WindowRect, TRUE);
		break;
	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		HBRUSH br, obr;
		hDC = BeginPaint(hWnd, &ps); 
		br = CreateSolidBrush(RGB(255, 255, 255));
		obr = (HBRUSH)SelectObject(hDC, br);

		RECT rect;
		int column_width;
		int column_height;
		column_width = (WindowRect.right - WindowRect.left) / COLUMNS;
		column_height = (WindowRect.bottom - WindowRect.top) / ROWS;
		for (auto i = 0; i < ROWS; i++) {
			for (auto j = 0; j < COLUMNS; j++) {
				rect.left = column_width * j;
				rect.top = column_height * i;

				rect.right = column_width * (j + 1);
				rect.bottom = column_height * (i + 1);
				Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

				rect.left = column_width * j + 5;
				rect.top = column_height * i + 2;
				DrawText(hDC, LPTEXT, lstrlen(LPTEXT), &rect, DT_CALCRECT | DT_WORDBREAK | DT_CENTER | DT_WORD_ELLIPSIS);
				int height_text = rect.bottom - rect.top;
				rect.top = (column_height - height_text) / 2 + column_height * i;
				rect.bottom = (rect.top + height_text) + column_height * i;
				DrawText(hDC, LPTEXT, lstrlen(LPTEXT), &rect, DT_WORDBREAK | DT_CENTER | DT_WORD_ELLIPSIS);
			}
		}
		SelectObject(hDC, obr);
		DeleteObject(br);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}
