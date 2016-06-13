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

void Drzewo::losujObrot(float obrot[3])
{
	obrot[0] = 0;
	obrot[1] = (float)(rand() % 360);
	obrot[2] = (float)(rand() % 50 + 30);
}
void Drzewo::znajdzKatyObrotuGalezi(float katyObrotu[5][3], float iloscRozgalezien)
{
	bool przelosuj = true;
	do
	{
		przelosuj = false;
		for (int i = 0; i < (int)iloscRozgalezien; i++) {
			losujObrot(katyObrotu[i]);
		}
		for (int i = 0; i < (int)iloscRozgalezien; i++) {
			for (int j = 0; j < (int)iloscRozgalezien; j++) {
				if (j != i){
					float kat1 = katyObrotu[i][1];
					float kat2 = katyObrotu[j][1];
					if (abs(kat1 - kat2) < 50){
						przelosuj = true;
					}
				}
			}
		}

	} while (przelosuj!=false);


}

void Drzewo::generujDrzewo(float maxDlugosc, int iloscRozgalezien, Galaz* galaz, float szerokoscGalezi)
{
	vector<Galaz*>* next = galaz->getNext();

	float katyObrotu[5][3];
	
	znajdzKatyObrotuGalezi(katyObrotu, iloscRozgalezien);

	for (int i = 0; i < iloscRozgalezien; i++){

		int dlugoscLosowa = (int)(maxDlugosc * 1000 )/2;
		int dlugoscPodstawowa = (int)(maxDlugosc * 1000)/2;

		float dlugosc = (float)((rand() % dlugoscLosowa) + dlugoscPodstawowa) / 1000.0;

		float pozycjaGalezi[3] = {0, dlugosc, 0 };

		float obudowa[4][3];

		stworzObudowe(obudowa, dlugosc/1000, szerokoscGalezi);

		//float obrot[3] = {0, (float)(rand() % 360) , (float)(rand() % 50 + 30) };
		obroc(pozycjaGalezi, obudowa, katyObrotu[i]);

		for (int j = 0; j < 3; j++) {
			pozycjaGalezi[j] += galaz->getPosition()[j];
		}
		
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 3; j++){
				obudowa[i][j] += galaz->getPosition()[j];
			}
		}

		next->push_back(new GalazOpenGL(pozycjaGalezi, szerokoscGalezi, galaz, obudowa, katyObrotu[i]));
		generujDrzewo(maxDlugosc/2, iloscRozgalezien-1, (*next)[i] , szerokoscGalezi/2);
	}
}

Drzewo::Drzewo(float pozycjaDrzewa[3])
{
	
	szerokoscPnia = 0.02f;

	float szerokoscGalezi = 0.04f;

	float obudowa[4][3];
	stworzObudowe(obudowa, 0, szerokoscGalezi);

	szerokoscGalezi /= 2;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			obudowa[i][j] += pozycjaDrzewa[j];
		}
	}
	float obrot[3] = { 0, 0, 0 };
	pien = new GalazOpenGL(pozycjaDrzewa, szerokoscGalezi, nullptr, obudowa, obrot);


	pozycjaDrzewa[1] += 0.2f;

	float obudowa2[4][3];
	stworzObudowe(obudowa2, 0, szerokoscGalezi);


	float obrot2[3] = { rand() % 16 - 8, 0, rand()%16 - 8};
	float zmianaPodczasObrotu[3] = { 0 , 0.2f, 0 };
	obroc(zmianaPodczasObrotu, obudowa2, obrot2);
	zmianaPodczasObrotu[1] -= 0.2f;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			obudowa2[i][j] += zmianaPodczasObrotu[j];
			obudowa2[i][j] += pozycjaDrzewa[j];
		}
	}
	vector<Galaz*>* next = pien->getNext();
	next->push_back(new GalazOpenGL(pozycjaDrzewa, szerokoscGalezi, pien, obudowa2, obrot));



	pozycjaDrzewa[1] += 0.2f;

	float obudowa3[4][3];
	stworzObudowe(obudowa3, 0, szerokoscGalezi);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			obudowa3[i][j] += pozycjaDrzewa[j];
		}
	}
	


	(*next)[0]->getNext()->push_back(new GalazOpenGL(pozycjaDrzewa, szerokoscGalezi, (*next)[0], obudowa2, obrot));

	generujDrzewo(0.4f, 4, (*(*next)[0]->getNext())[0], szerokoscGalezi);
}

Drzewo::~Drzewo()
{
}

void Drzewo::Rysuj()
{
	pien->Rysuj();
}
