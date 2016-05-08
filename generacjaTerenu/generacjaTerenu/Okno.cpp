#include "Okno.h"

LRESULT Okno::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		RECT rect;
		GetClientRect(hWnd,&rect);
		this->width = rect.right - rect.left;
		this->height = rect.bottom - rect.top;
		break;

	default: 
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return 0;
}

bool Okno::rejestrujOkno(HINSTANCE hInstance, POINT polozenie, POINT rozmiar, WNDPROC wndProc)
{
	// WYPE£NIANIE STRUKTURY
	WNDCLASSEX wc;

	LPSTR nazwaOkna = "Klasa Okienka";
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = nazwaOkna;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
   
    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( NULL, "Blad przy rejestracji okna", "Niestety...",
        MB_ICONEXCLAMATION | MB_OK );
		return false;
    }
   
    // TWORZENIE OKNA
    HWND hwnd;
   
    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, nazwaOkna, "Oto okienko", WS_OVERLAPPEDWINDOW,
    polozenie.x, polozenie.y, rozmiar.x, rozmiar.y, NULL, NULL, hInstance, NULL );
   
    if( hwnd == NULL )
    {
        MessageBox( NULL, "Okno odmówi³o przyjœcia na œwiat!", "Niestety...", MB_ICONEXCLAMATION );
		return false;
    }
   
	ShowWindow(hwnd, SW_SHOW);
    UpdateWindow( hwnd );
   

	return true;
	
}

WPARAM Okno::run()
{
	// Pêtla komunikatów
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;;
}

