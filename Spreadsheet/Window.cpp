#include "Window.h"

Window::Window() : m_winWidth(1000),
	m_winHeight(600),
	m_hwnd(nullptr),
	m_winLastErrorMsg(nullptr),
	m_winClass(L"WinClass"),
	m_winName(L"Title")
{

}



BOOL Window::create(
	PCWSTR lpWindowName,
	PCWSTR lpWindowClass,
	DWORD  dwStyle,
	int    nWidth,
	int    nHeight,
	int    x,
	int    y,
	DWORD  dwExStyle,
	HWND   hwndParent,
	HMENU  hMenu
)
{
	if (getWindowHwnd()) { 
		setWinLastErrorMsg(L"This window has been already created");
		return FALSE; 
	}

	// init class variables
	setWinName(lpWindowName);
	setWinClass(lpWindowClass);
	setWinWidth(nWidth);
	setWinHeight(nHeight);

	// register window
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = winProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground = (HBRUSH)(COLOR_MENU + 1);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = getWinClass();

	if (!RegisterClass(&wc)) {
		setWinLastErrorMsg(L"RegisterClass failed");
		return FALSE;
	}

	// create window
	m_hwnd = CreateWindowEx(
		dwExStyle,						// extended window style
		getWinClass(),					// class name
		getWinName(),					// window name
		dwStyle,						// window style
		x,								// window position X
		y,								// window position Y
		getWinWidth(),					// window width
		getWinHeight(),					// window height
		hwndParent,						// parent window descriptor
		hMenu,							// menu descriptor
		GetModuleHandle(NULL),			// program instance descriptor
		this							// pointer to window data
	);

	if (!getWindowHwnd()) {
		setWinLastErrorMsg(L"CreateWindowEx failed");
		return FALSE;
	}

	return TRUE;
}



LRESULT CALLBACK Window::winProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* pThis = nullptr;

	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT* pCS = (CREATESTRUCT*)lParam;
		pThis = (Window*)pCS->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

		pThis->m_hwnd = hwnd;
	}
	else {
		pThis = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}

	if (pThis) {
		return pThis->msgHandler(uMsg, wParam, lParam);
	}
	else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}



LRESULT Window::msgHandler(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(getWindowHwnd(), uMsg, wParam, lParam);
}



// window handle
HWND Window::getWindowHwnd() { return m_hwnd; }

// window width
void Window::setWinWidth(int winWidth) { m_winWidth = winWidth; }
int Window::getWinWidth() { return this->m_winWidth; }

// window height
void Window::setWinHeight(int winHeight) { m_winHeight = winHeight; }
int Window::getWinHeight() { return m_winHeight; }

// window class
void Window::setWinClass(const wchar_t* winClass) { m_winClass = winClass; }
const wchar_t* Window::getWinClass() { return m_winClass; }

// window title
void Window::setWinName(const wchar_t* winName) { m_winName = winName; }
const wchar_t* Window::getWinName() { return m_winName; }

// window last error message
void Window::setWinLastErrorMsg(const wchar_t* msg) { m_winLastErrorMsg = msg; }
const wchar_t* Window::getLastWindowError() { return m_winLastErrorMsg; }
