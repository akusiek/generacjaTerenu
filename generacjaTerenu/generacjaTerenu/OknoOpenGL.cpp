#include "OknoOpenGL.h"


OknoOpenGL::OknoOpenGL():Okno(), rcHandle(NULL), dcHandle(NULL), drawer(&dcHandle)
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

void OknoOpenGL::createScene()
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float) height / (float)width;
	glFrustum(-0.1, 0.1, ratio*-0.1, ratio*0.1, 0.3, 100);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

LRESULT OknoOpenGL::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long tmp = Okno::WndProc(hWnd, message, wParam, lParam);

		switch (message)
		{
			case WM_CREATE:
			{
				initWGL(hWnd);
				createScene();
				break;
			}
			case WM_SIZE:
			{
				createScene();
				break;
			}
			case WM_PAINT:
			{
				drawer.draw();
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

