#include <Windows.h>

#ifndef WINDOW_H
#define WINDOW_H
	
class Window
{
public:
	Window();

	BOOL create(
		PCWSTR lpWindowName,
		PCWSTR lpWindowClass,
		DWORD  dwStyle,
		int    nWidth,
		int    nHeight,
		int    x = CW_USEDEFAULT,
		int    y = CW_USEDEFAULT,
		DWORD  dwExStyle = 0,
		HWND   hwndParent = nullptr,
		HMENU  hMenu = nullptr
	);

	static LRESULT CALLBACK winProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT msgHandler(UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND getWindow();
	int getWinWidth();
	int getWinHeight();
	const wchar_t* getWinClass();
	const wchar_t* getWinName();
	const wchar_t* getLastWindowError();

protected:
	HWND m_hwnd;
	int m_winWidth;
	int m_winHeight;
	const wchar_t* m_winClass;
	const wchar_t* m_winName;
	const wchar_t* m_winLastErrorMsg;

	void setWinWidth(int winWidth);
	void setWinHeight(int winHeight);
	void setWinClass(const wchar_t* winClass);
	void setWinName(const wchar_t* winTitle);
	void setWinLastErrorMsg(const wchar_t* msg);
};

#endif // !WINDOW_H
