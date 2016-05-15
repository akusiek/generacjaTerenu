#include "OknoOpenGL.h"


OknoOpenGL::OknoOpenGL():Okno(), rcHandle(NULL), dcHandle(NULL)
{

}

bool OknoOpenGL::setPixelFormat(HDC handle)
{
	PIXELFORMATDESCRIPTOR pixelDescriptor;
	ZeroMemory(&pixelDescriptor, sizeof(pixelDescriptor));
	pixelDescriptor.nVersion = 1;
	pixelDescriptor.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pixelDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelDescriptor.cColorBits = 32;
	pixelDescriptor.cDepthBits = 16;
	pixelDescriptor.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(handle, &pixelDescriptor);

	if (!pixelFormat)
		return false;

	if (!SetPixelFormat(handle, pixelFormat, &pixelDescriptor))
		return false;

	return true;
}

LRESULT OknoOpenGL::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long tmp = Okno::WndProc(hWnd, message, wParam, lParam);

		switch (message)
		{
			case WM_CREATE:
			{
				initWGL(hWnd);
				break;
			}
			case WM_DESTROY:
			{
				deinitWGL(hWnd);
				break;
			}
		}

	return tmp;
}

bool OknoOpenGL::initWGL(HWND handle)
{
	dcHandle = ::GetDC(handle);
	if (!setPixelFormat(dcHandle))
		return false;

	if (! (rcHandle = wglCreateContext(dcHandle)) )
		return false;
	
	if (!wglMakeCurrent(dcHandle, rcHandle))
		return false;

	return true;
}

bool OknoOpenGL::deinitWGL(HWND handle)
{
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(rcHandle);
	::ReleaseDC(handle, dcHandle);
	return false;
}

