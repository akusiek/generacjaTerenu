#pragma once
#include<windows.h>

class Okno
{
	long height, width;
public:
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool rejestrujOkno(HINSTANCE hInstance, POINT polozenie, POINT rozmiar, WNDPROC wndProc);
	WPARAM run();

};

