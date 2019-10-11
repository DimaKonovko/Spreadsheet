#include "App.h"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	BOOL isCorrect;
	App app;
	isCorrect = app.start(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	if (!isCorrect) {
		MessageBox(nullptr, app.getAppLastErrorMsg(), nullptr, 0);
		return 1;
	}

	isCorrect = app.release();
	if (!isCorrect) {
		MessageBox(nullptr, app.getAppLastErrorMsg(), nullptr, 0);
		return 1;
	}

	isCorrect = app.close();
	if (!isCorrect) {
		MessageBox(nullptr, app.getAppLastErrorMsg(), nullptr, 0);
		return 1;
	}

	return 0;
}
