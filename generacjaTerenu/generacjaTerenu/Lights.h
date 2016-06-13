#pragma once
#include <Windows.h>
#include <gl/GL.h>
class Lights
{
protected:
	float natezenie_tla = 1.0;
	void mlecznaZarowka(float jasnosc);
public:
	Lights();
	~Lights();
	void obsluzOswietlenie();
    void changBackgroundLignt(float howMuch);
};

