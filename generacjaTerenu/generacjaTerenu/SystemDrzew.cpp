#include "SystemDrzew.h"



SystemDrzew::SystemDrzew()
{


}


SystemDrzew::~SystemDrzew()
{
}

void SystemDrzew::generuj(float terrain[terrain_size][terrain_size])
{
	srand((int)time(NULL));
	float pozycja[3] = { 
		(terrain_size / 2)*0.1f,
		terrain[terrain_size / 2][terrain_size / 2] * 0.1f - 0.01f,
		(terrain_size / 2)*0.1f 
	};
	drzewa.push_back(new Drzewo(pozycja));

	float pozycja2[3] = { 
		(terrain_size / 4)*0.1f,
		terrain[terrain_size / 4][terrain_size / 2]*0.1f - 0.01f,
		(terrain_size / 2)*0.1f 
	};
	drzewa.push_back(new Drzewo(pozycja2));
}

void SystemDrzew::Rysuj()
{
	for (int i = 0; i < drzewa.size(); i++){
		drzewa[i]->Rysuj();
	}
	
}
