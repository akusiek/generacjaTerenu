#pragma once

#include <Windows.h>
#include <GL/GL.h>
#include "Galaz.h"
#include "OperacjeNaWektorach.h"

class GalazOpenGL : public Galaz
{
	float obrot[3];
	static OperacjeNaWektorach operacjeNaWektorach;
public:
	GalazOpenGL(float pozycja[3], float grubosc, Galaz* prev, float obudowa[4][3], float obrot[3]);
	~GalazOpenGL();
	void Rysuj();
};

