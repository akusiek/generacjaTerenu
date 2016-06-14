#include "Terrain.h"


Terrain::Terrain()
{
	srand(time(NULL));
	terrain_size = 100;
	smooth_factor = 0.111111f;
	terrain = new float*[terrain_size];
	for (int i = 0; i < terrain_size; ++i) {
		terrain[i] = new float[terrain_size];
	}
	for (int i = 0; i < terrain_size; ++i) {
		for (int j = 0; j < terrain_size; ++j) {
			terrain[i][j] = 0;
		}
	}
}

Terrain::Terrain(int size, float smooth_f) {
	srand(time(NULL));	
	terrain_size = size;
	smooth_factor = smooth_f;
	terrain = new float*[terrain_size];
	for (int i = 0; i < terrain_size; ++i) {
		terrain[i] = new float[terrain_size];
	}
	for (int i = 0; i < terrain_size; ++i) {
		for (int j = 0; j < terrain_size; ++j) {
			terrain[i][j] = 0;
		}
	}
}

Terrain::~Terrain()
{
	for (int i = 0; i < terrain_size; ++i) {
		delete[] terrain[i];
	}
}


void Terrain::smoother(unsigned int type) {
	switch (type) {
	case 0:
		for (int x = 1; x < terrain_size; x++) {
			for (int z = 0; z < terrain_size; z++) {
				terrain[x][z] = terrain[x - 1][z] * (1 - smooth_factor) + terrain[x][z] * smooth_factor;
			}
		}
		for (int x = terrain_size - 2; x < -1; x--) {
			for (int z = 0; z < terrain_size; z++) {
				terrain[x][z] = terrain[x + 1][z] * (1 - smooth_factor) +
					terrain[x][z] * smooth_factor;
			}
		}
		for (int x = 0; x < terrain_size; x++) {
			for (int z = 1; z < terrain_size; z++) {
				terrain[x][z] = terrain[x][z - 1] * (1 - smooth_factor) +
					terrain[x][z] * smooth_factor;
			}
		}

		for (int x = 0; x < terrain_size; x++) {
			for (int z = terrain_size; z < -1; z--) {
				terrain[x][z] = terrain[x][z + 1] * (1 - smooth_factor) +
					terrain[x][z] * smooth_factor;
			}
		}
		break;
	case 1:
		float smooth_matrix[3][3] = { { 0 } };
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				smooth_matrix[i][j] = smooth_factor;
			}
		}
		for (int x = 1; x < terrain_size - 1; ++x) {
			for (int z = 1; z < terrain_size - 1; ++z) {
				terrain[x][z] = smooth_matrix[0][0] * terrain[x - 1][z - 1] + smooth_matrix[0][1] * terrain[x - 1][z] + smooth_matrix[0][2] * terrain[x - 1][z + 1] +
					smooth_matrix[1][0] * terrain[x][z - 1] + smooth_matrix[1][1] * terrain[x][z] + smooth_matrix[1][2] * terrain[x][z + 1] +
					smooth_matrix[2][0] * terrain[x + 1][z - 1] + smooth_matrix[2][1] * terrain[x + 1][z] + smooth_matrix[2][2] * terrain[x + 1][z + 1];
			}
		}
		break;
	}

}

void Terrain::render(unsigned int mode) {
	OperacjeNaWektorach* operacjeNaWektorach = new OperacjeNaWektorach();
	switch (mode) {
	case 0: //dots
		for (int x = 0; x < terrain_size; ++x) {
			for (int z = 0; z < terrain_size; ++z) {
				glColor3f(0.0f, 1.0f, 0.0f);
				glScalef(1.5f, 1.5f, 1.5f);
				glBegin(GL_POINTS);
				glVertex3f((GLfloat)x, (GLfloat)terrain[x][z], (GLfloat)z);
				glEnd();
			}
		}
		break;
	case 1: // TODO: terrain rendering with triangle usage 
		for (int x = 0; x < terrain_size - 1; ++x) {
			for (int z = 0; z < terrain_size - 1; ++z) {
				glColor3f(0.1f, 0.6f, 0.0f);
				glBegin(GL_TRIANGLES);

				float vector1[3] = { (GLfloat)x*0.1f, (GLfloat)terrain[x][z] * 0.1f, (GLfloat)z*0.1f };
				float vector2[3] = { (GLfloat)x*0.1f, (GLfloat)terrain[x][z + 1] * 0.1f, (GLfloat)(z + 1)*0.1f };
				float vector3[3] = { (GLfloat)(x + 1)*0.1f, (GLfloat)terrain[x + 1][z + 1] * 0.1f, (GLfloat)(z + 1)*0.1f };
				float vector4[3] = { (GLfloat)(x + 1)*0.1f, (GLfloat)terrain[x + 1][z + 1] * 0.1f, (GLfloat)(z + 1)*0.1f };
				float vector5[3] = { (GLfloat)(x + 1)*0.1f, (GLfloat)terrain[x + 1][z] * 0.1f, (GLfloat)z*0.1f };
				float vector6[3] = { (GLfloat)x*0.1f, (GLfloat)terrain[x][z] * 0.1f, (GLfloat)z*0.1f };
				float wynik[3];
				glNormal3fv(operacjeNaWektorach->jednostkowyWektorNormalny3fv(vector1, vector2, vector3, wynik));
				glVertex3fv(vector1);

				glVertex3fv(vector3);
				glVertex3fv(vector2);
				float wynik2[3];
				glNormal3fv(operacjeNaWektorach->jednostkowyWektorNormalny3fv(vector4, vector5, vector6, wynik2));
				glVertex3fv(vector4);

				glVertex3fv(vector6);
				glVertex3fv(vector5);

				glEnd();
			}
		}
		break;
	case 2: //squares
		for (int x = 0; x < terrain_size - 1; ++x) {
			for (int z = 0; z < terrain_size - 1; ++z) {
				glColor3f(0.1f, 0.7f, 0.2f);
				const float scale = 0.1f;
				glBegin(GL_QUADS);

				float vector1[3] = { x*scale, terrain[x][z] * scale, z*scale };
				float vector2[3] = { x*scale, terrain[x][z + 1] * scale, (z + 1)*scale };
				float vector3[3] = { (x + 1)*scale, terrain[x + 1][z + 1] * scale, (z + 1)*scale };
				float vector4[3] = { (x + 1)*scale, terrain[x + 1][z] * scale, z*scale };
				float wynik[3];
				glNormal3fv(operacjeNaWektorach->jednostkowyWektorNormalny3fv(vector1, vector2, vector3, wynik));
				glVertex3fv(vector1);
				glVertex3fv(vector2);
				glVertex3fv(vector3);
				glVertex3fv(vector4);

				glEnd();
			}
		}
		break;
	}
	delete operacjeNaWektorach;
}

void Terrain::generate(int iterations, int which, float increment) { // TODO: flatten the terrain and maybe try another algorithm
	int i = 0;
	switch (which) {
	case 0: {
		int x1 = rand() % terrain_size;
		int z1 = rand() % terrain_size;
		while (i < iterations) {
			terrain[x1][z1] += increment;
			int move = rand() % 4;
			switch (move) {
			case 0:
				if (x1 + 1 > terrain_size - 1)
					x1 = 0;
				else
					x1++;
				break;
			case 1:
				if (x1 - 1 < 0)
					x1 = terrain_size - 1;
				else
					x1--;
				break;
			case 2:
				if (z1 + 1 > terrain_size - 1)
					z1 = 0;
				else
					z1++;
				break;
			case 3:
				if (z1 - 1 < 0)
					z1 = terrain_size - 1;
				else
					z1--;
				break;
			}
			++i;
		}
	}
		break;
	case 1:
	{
		while (i < iterations) {
			int x1 = rand() % terrain_size;
			int z1 = rand() % terrain_size;
			int x2 = rand() % terrain_size;
			int z2 = rand() % terrain_size;
			int a = (z2 - z1);
			int b = -(x2 - x1);
			int c = -(x1*(z2 - z1)) + z1*(x2 - x1);
			for (int x = 0; x < terrain_size; x++) {
				for (int z = 0; z < terrain_size; z++) {
					if (a * x + b * z - c > 0)
						terrain[x][z] += increment;
					else
						terrain[x][z] -= increment;
				}
			}
			++i;
		}
	}
		break;

	}
}

int Terrain::getTerrainSize() {
	return terrain_size;
}

float** Terrain::getTerrainTable() {
	return terrain;
}