#include "SystemDrzew.h"



SystemDrzew::SystemDrzew()
{
	float pozycja[3] = { 2.0, 0.0, 3.0 };
	drzewa.push_back(new Drzewo(pozycja));

	float pozycja2[3] = { 2.0, 0.0, 2.0 };
	drzewa.push_back(new Drzewo(pozycja2));
}


SystemDrzew::~SystemDrzew()
{
}

void SystemDrzew::Rysuj()
{
	for (int i = 0; i < drzewa.size(); i++){
		drzewa[i]->Rysuj();
	}
	
}
