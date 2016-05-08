#include"Okno.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!okno->rejestrujOkno(hInstance, { 25,25 }, { 1400, 700 }))
	{
		return EXIT_FAILURE;
	}
	return okno->run();
}