#pragma once
#include "OperacjeNaWektorach.h"
#include <GL/freeglut.h>
#include <ctime>

class Terrain
{
	float** terrain;
	int terrain_size;
	float smooth_factor;
public:
	Terrain();
	Terrain(int, float);
	void generate(int, int, float);
	void smoother(unsigned int);
	void render(unsigned int);
	int getTerrainSize();
	float** getTerrainTable();
	~Terrain();
};

