#include "Drzewo.h"

OperacjeNaWektorach Drzewo::operacjeNaWektorach;

void Drzewo::obroc(float pozycjaGalezi[3], float obudowa[4][3], float obrot[3])
{
	if (obrot[2] != 0)
	{
		operacjeNaWektorach.obrocZ(pozycjaGalezi, 1.67f / 90.0f*obrot[2]);
		for (int i = 0; i < 4; i++) {
			operacjeNaWektorach.obrocZ(obudowa[i], 1.67f / 90.0f*obrot[2]);
		}
	}

	if (obrot[1] != 0)
	{
		operacjeNaWektorach.obrocY(pozycjaGalezi, 1.67f / 90.0f*obrot[1]);
		for (int i = 0; i < 4; i++) {
			operacjeNaWektorach.obrocY(obudowa[i], 1.67f / 90.0f*obrot[1]);
		}
	}

	if (obrot[0] != 0)
	{
		operacjeNaWektorach.obrocX(pozycjaGalezi, 1.67f / 90.0f*obrot[0]);
		for (int i = 0; i < 4; i++) {
			operacjeNaWektorach.obrocX(obudowa[i], 1.67f / 90.0f*obrot[0]);
		}
	}


}
void Drzewo::stworzObudowe(float obudowa[4][3], float wysokosc, float szerokoscPnia)
{
	float obudowaTmp[4][3] = {
		{ -szerokoscPnia, wysokosc , szerokoscPnia },
		{ szerokoscPnia, wysokosc , szerokoscPnia },
		{ -szerokoscPnia, wysokosc , -szerokoscPnia },
		{ szerokoscPnia, wysokosc , -szerokoscPnia }
	};

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			obudowa[i][j] = obudowaTmp[i][j];
}
void Drzewo::generujDrzewo(float maxDlugosc, int iloscRozgalezien, Galaz* galaz, float szerokoscGalezi)
{
	vector<Galaz*>* next = galaz->getNext();

	for (int i = 0; i < iloscRozgalezien; i++){

		int dlugoscLosowa = (int)(maxDlugosc * 1000 )/2;
		int dlugoscPodstawowa = (int)(maxDlugosc * 1000)/2;

		float dlugosc = (float)((rand() % dlugoscLosowa) + dlugoscPodstawowa) / 1000.0;

		float pozycjaGalezi[3] = {0, dlugosc, 0 };

		
		float obudowa[4][3];

		stworzObudowe(obudowa, dlugosc /1000, szerokoscGalezi);

		float obrot[3] = {0, (float)(rand() % 360) , (float)(rand() % 50 + 30) };
		obroc(pozycjaGalezi, obudowa, obrot);

		pozycjaGalezi[0] += galaz->getPosition()[0];
		pozycjaGalezi[1] += galaz->getPosition()[1];
		pozycjaGalezi[2] += galaz->getPosition()[2];
		for (int i = 0; i < 4; i++)
		{
			obudowa[i][0] += galaz->getPosition()[0];
			obudowa[i][1] += galaz->getPosition()[1];
			obudowa[i][2] += galaz->getPosition()[2];
		}

		next->push_back(new GalazOpenGL(pozycjaGalezi, szerokoscPnia, galaz, obudowa, obrot));
		generujDrzewo(maxDlugosc/2, iloscRozgalezien-1, (*next)[i] , szerokoscGalezi/2);
	}
}

Drzewo::Drzewo(float pozycjaDrzewa[3])
{
	srand( (int) time( NULL ) );
	szerokoscPnia = 0.02f;

	float szerokoscGalezi = 0.04f;

	float obudowa[4][3];
	stworzObudowe(obudowa, 0, szerokoscGalezi);

	szerokoscGalezi /= 2;
	for (int i = 0; i < 4; i++)
	{
		obudowa[i][0] += pozycjaDrzewa[0];
		obudowa[i][1] += pozycjaDrzewa[1];
		obudowa[i][2] += pozycjaDrzewa[2];
	}
	float obrot[3] = { 0, 0, 0 };
	pien = new GalazOpenGL(pozycjaDrzewa, szerokoscGalezi, nullptr, obudowa, obrot);
	vector<Galaz*>* next = pien->getNext();
	int iloscRozgalezien = 1;
	pozycjaDrzewa[1] = 0.4f;

	float obudowa2[4][3];
	stworzObudowe(obudowa2, 0, szerokoscGalezi);
	for (int i = 0; i < 4; i++)
	{
		obudowa2[i][0] += pozycjaDrzewa[0];
		obudowa2[i][1] += pozycjaDrzewa[1];
		obudowa2[i][2] += pozycjaDrzewa[2];
	}

	next->push_back(new GalazOpenGL(pozycjaDrzewa, szerokoscGalezi, pien, obudowa2, obrot));

	generujDrzewo(0.4f, 4, (*next)[0], szerokoscGalezi);
}

Drzewo::~Drzewo()
{
}

void Drzewo::Rysuj()
{
	pien->Rysuj();
}
