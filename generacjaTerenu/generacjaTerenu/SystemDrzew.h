#pragma once
#include "Drzewo.h"
#include <vector>
class SystemDrzew
{
	vector<Drzewo *> drzewa;
public:
	SystemDrzew();
	~SystemDrzew();
	void Rysuj();
};

