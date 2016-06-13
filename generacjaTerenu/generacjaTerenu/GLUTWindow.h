#pragma once
#include <string>
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>
#include "glm.hpp"
#include "Lights.h"
#include "OperacjeNaWektorach.h"
#include "SystemDrzew.h"
#include "Definicje.h"

//#define terrain_size 50

class GLUTWindow
{
	int win_pos_x, win_pos_y;
	static int win_width, win_height;
	unsigned int displ_mod;
	std::string win_name;
	int* argc;
	char** argv;
	//static float smooth_factor;
	static void renderScene();
	static void changeSize(int w, int h);
	//static void processKeys(unsigned char key, int x, int y);
	static void keyPressed(unsigned char, int, int);
	static void keyReleased(unsigned char, int, int);
	static void keyStrokes();
	static void processMouseKeys(int button, int state, int x, int y);
	static void processMouseMovement(int x,int y);
	static void generateTerrain(int iterations, int, float);
	static void renderTerrain(unsigned int);
	static void whereIsCursor(int state);
	static void calculatePosition();
	static void smootherTerrain(unsigned int);
	//new stuff
	static glm::vec3 cameraPos; 
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;

	static bool isFirstMouse, firstRender;
	static float lastX, lastY;
	static float yaw, pitch;
	
	static float moveSpeedFrontBack;
	static float moveSpeedLeftRight;
	static float moveSpeedUpDown;
	//terrain
	static float terrain[terrain_size][terrain_size];
	static void printTerrain();

	static Lights * lights;
	static OperacjeNaWektorach * operacjeNaWektorach;
	static SystemDrzew * systemDrzew;
public:
	GLUTWindow(int* , char**);
	GLUTWindow(int , int , int , int , unsigned int , std::string , int* , char** );
	void init();
	~GLUTWindow();
};

