#pragma once
#include "Okno.h"

class OknoOpenGL :
	public Okno
{
protected:
	HGLRC rcHandle;
	HDC dcHandle;
	bool initWGL(HWND handle);
	bool deinitWGL(HWND handle);
	bool setPixelFormat(HDC handle);
public:
	OknoOpenGL();
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};
static OknoOpenGL window;

