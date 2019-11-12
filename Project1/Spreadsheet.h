#pragma once

#include <windows.h>

// variables
TCHAR szWindowClass[] = L"Spreadsheet";
TCHAR szTitle[] = L"Spreadsheet";
HINSTANCE hInst;

constexpr auto WND_WIDTH = 1000.0;
constexpr auto WND_HEIGHT = 600.0;
constexpr auto ROWS = 5;
constexpr auto COLUMNS = 3;

LPCWSTR LPTEXT = L"ajdfhgjk hadgfjkadhgjkhsadgfjkadhgfjkhg gjfhgdskajfhgjakdhgfjkhg gjhgjkhgajsdgf g jgakjsdhgfjhgasdjfkhgjaksdhgfjadgf";


// forward declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
