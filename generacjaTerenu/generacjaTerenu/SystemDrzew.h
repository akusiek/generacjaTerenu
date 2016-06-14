#pragma once
#include "Drzewo.h"
#include "Definicje.h"
#include "Terrain.h"
#include <vector>
class SystemDrzew
{
	vector<Drzewo *> drzewa;
public:
	SystemDrzew();
	~SystemDrzew();
	void generuj(Terrain* terrain);
	void Rysuj();
};

