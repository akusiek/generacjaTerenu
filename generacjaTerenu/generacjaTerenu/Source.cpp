#include"OknoOpenGL.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return okno.WndProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!okno.rejestrujOkno(hInstance, { 25,25 }, { 1400, 700 }, (WNDPROC)::WndProc))
	{
		return EXIT_FAILURE;
	}

	return okno.run();
}

