#ifndef APP_H
#define APP_H

#include "Window.h"

#include <windows.h>

class App
{
public:
	App();

	BOOL start(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow);
	BOOL release();
	BOOL close();

	HINSTANCE getInstance();
	HINSTANCE getPrevInstance();
	LPSTR getCmdLine();
	int getCmdShow();
	Window getWindow();
	const wchar_t* getAppLastErrorMsg();

private:
	HINSTANCE m_hInst;
	HINSTANCE m_hPrevInst;
	LPSTR m_lpCmdLine;
	int m_nCmdShow;

	Window m_window;
	const wchar_t* m_appLastErrorMsg;

	void setInstance(HINSTANCE hInst);
	void setPrevInstance(HINSTANCE hPrevInst);
	void setCmdLine(LPSTR lpCmdLine);
	void setCmdShow(int nCmdShow);
	void setAppLastErrorMsg(const wchar_t* msg);
};

#endif // !APP_H
