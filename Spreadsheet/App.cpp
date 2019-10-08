#include "App.h"

App::App() : m_hInst(nullptr),
	m_hPrevInst(nullptr),
	m_lpCmdLine(nullptr),
	m_nCmdShow(0),
	m_appLastErrorMsg(nullptr)
{

}



BOOL App::start(
	HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	if (getInstance()) {
		setAppLastErrorMsg(L"The App has been already started");
		return FALSE;
	}

	// init class variables
	setInstance(hInst);
	setPrevInstance(hPrevInst);
	setCmdLine(lpCmdLine);
	setCmdShow(nCmdShow);

	if (!m_window.create(L"Spreadsheet", L"SpreadsheetClass", WS_OVERLAPPEDWINDOW, 1000, 600)) {
		setAppLastErrorMsg(L"Call to create window failed");
		return FALSE;
	}

	ShowWindow(m_window.getWindow(), nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return TRUE;
}



BOOL App::release()
{
	return TRUE;
}



BOOL App::close()
{
	return TRUE;
}



// program instance
void App::setInstance(HINSTANCE hInst) { m_hInst = hInst; }
HINSTANCE App::getInstance() { return m_hInst; }

// program prev instance
void App::setPrevInstance(HINSTANCE hPrevInst) { m_hPrevInst = hPrevInst; }
HINSTANCE App::getPrevInstance() { return m_hPrevInst; }

// program cmd line
void App::setCmdLine(LPSTR lpCmdLine) { m_lpCmdLine = lpCmdLine; }
LPSTR App::getCmdLine() { return m_lpCmdLine; }

// program show
void App::setCmdShow(int nCmdShow) { m_nCmdShow = nCmdShow; }
int App::getCmdShow() { return m_nCmdShow; }

// main window
Window App::getWindow() { return m_window; }

// app last erro message
void App::setAppLastErrorMsg(const wchar_t* msg) { m_appLastErrorMsg = msg; }
const wchar_t* App::getAppLastErrorMsg() { return m_appLastErrorMsg; }
