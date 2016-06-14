#include "SystemDrzew.h"



SystemDrzew::SystemDrzew()
{


}


SystemDrzew::~SystemDrzew()
{
}

void SystemDrzew::generuj(Terrain* terrain)
{

	srand((int)time(NULL));
	float pozycja[3] = { 
		(terrain->getTerrainSize() / 2)*0.1f,
		terrain->getTerrainTable()[terrain->getTerrainSize() / 2][terrain->getTerrainSize() / 2] * 0.1f - 0.01f,
		(terrain->getTerrainSize() / 2)*0.1f
	};
	drzewa.push_back(new Drzewo(pozycja));

	float pozycja2[3] = {
		(terrain->getTerrainSize() / 4)*0.1f,
		terrain->getTerrainTable()[terrain->getTerrainSize() / 4][terrain->getTerrainSize() / 2] * 0.1f - 0.01f,
		(terrain->getTerrainSize() / 2)*0.1f
	};
	drzewa.push_back(new Drzewo(pozycja2));

	float pozycja3[3] = {
		(terrain->getTerrainSize() / 4)*0.1f,
		terrain->getTerrainTable()[terrain->getTerrainSize() / 4][terrain->getTerrainSize() / 4] * 0.1f - 0.01f,
		(terrain->getTerrainSize() / 4)*0.1f
	};
	drzewa.push_back(new Drzewo(pozycja3));

	float pozycja4[3] = {
		(terrain->getTerrainSize() / 4 * 3)*0.1f,
		terrain->getTerrainTable()[terrain->getTerrainSize() / 4 * 3][terrain->getTerrainSize() / 2] * 0.1f - 0.01f,
		(terrain->getTerrainSize() / 2)*0.1f
	};
	drzewa.push_back(new Drzewo(pozycja4));
}

void SystemDrzew::Rysuj()
{
	for (int i = 0; i < drzewa.size(); i++){
		drzewa[i]->Rysuj();
	}
	
}
