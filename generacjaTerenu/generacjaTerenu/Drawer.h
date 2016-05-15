#pragma once
#include <Windows.h>
#include <gl/GL.h>

class Drawer
{
protected:
	HDC * dcHandle;
public:
	Drawer(HDC * dcHandle);
	~Drawer();
	void draw();
};

