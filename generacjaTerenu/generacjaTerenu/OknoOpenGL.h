#pragma once
#include "Okno.h"


class OknoOpenGL : public Okno
{
	HGLRC rcHandle;
	HDC dcHandle;

public:
	OknoOpenGL();
	~OknoOpenGL();
};
static OknoOpenGL okno;