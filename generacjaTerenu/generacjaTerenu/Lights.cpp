#include "Lights.h"



void Lights::mlecznaZarowka(float jasnosc)
{
	const float kolor[4] = { jasnosc,jasnosc ,jasnosc ,1.0f };
	const float pozycja[4] = { 5.0f,0.0f,5.0f ,1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, pozycja);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, kolor);

	glEnable(GL_LIGHT1);
}

Lights::Lights()
{
	natezenie_tla = 0.4;
}


Lights::~Lights()
{
}

void Lights::obsluzOswietlenie()
{
	glEnable(GL_LIGHTING);
	const float kolor_tla[] = { natezenie_tla,
		natezenie_tla,
		natezenie_tla };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, kolor_tla);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPushMatrix();
	glLoadIdentity();
	mlecznaZarowka(1.0f);
	glPopMatrix();
}

void Lights::changBackgroundLignt(float howMuch)
{
	natezenie_tla += howMuch;
	if (natezenie_tla > 2.0f)
		natezenie_tla = 2.0f;
}
