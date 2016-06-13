#pragma once
#include "GalazOpenGL.h"
#include <Windows.h>
#include <GL/GL.h>
#include "OperacjeNaWektorach.h"
#include <cstdlib>
#include <time.h>

class Drzewo
{
protected:
	float szerokoscPnia;
	float pozycjaDrzewa[3];
	Galaz * pien;
	void generujDrzewo(float maxDlugosc, int iloscRozgalezien, Galaz* galaz, float szerokoscGalezi);
	static OperacjeNaWektorach operacjeNaWektorach;
	void stworzObudowe(float obudowa[4][3], float wysokosc, float szerokoscPnia);
	void obroc(float pozycjaGalezi[3], float obudowa[4][3], float obrot[3]);
public:
	Drzewo(float pozycjaDrzewa[3]);
	~Drzewo();
	void Rysuj();
};

