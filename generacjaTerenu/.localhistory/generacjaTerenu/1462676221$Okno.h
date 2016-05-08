#pragma once
#include<windows.h>
class OknoOpenGL;
static OknoOpenGL * okno = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class Okno
{
	
public:
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool rejestrujOkno(HINSTANCE hInstance, POINT polozenie, POINT rozmiar);
	WPARAM run();
	~Okno();
	Okno()
	{

	}
};
