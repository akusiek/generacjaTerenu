#pragma once
#include <string>
#include <GL/freeglut.h>

class GLUTWindow
{
	int win_pos_x, win_pos_y, win_width, win_height;
	unsigned int displ_mod;
	std::string win_name;
	int* argc;
	char** argv;
	static void renderScene();
	static void changeSize(int w, int h);
	static void processKeys(unsigned char key, int x, int y);
	static void processMouseKeys(int button, int state, int x, int y);
	static void processMouseMovement(int x,int y);
	//static void processSpecialKeys(int key, int x, int y);
	static float angleH, angleV;
	static float lx, ly, lz, x, y, z;
	static float deltaAngleX, deltaAngleY;
	static int xOrigin, yOrigin;
public:
	GLUTWindow(int* , char**);
	GLUTWindow(int , int , int , int , unsigned int , std::string , int* , char** );
	void init();
	~GLUTWindow();
};

