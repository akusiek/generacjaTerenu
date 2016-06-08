#pragma once
#include <string>
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>
#include "glm.hpp"

#define terrain_size 50

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
	static void generateTerrain(int iterations);
	static void renderTerrain(unsigned int);

	//new stuff
	static glm::vec3 cameraPos; 
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;

	static bool isFirstMouse;
	static float lastX, lastY;
	static float yaw, pitch;
	
	//terrain
	static float terrain[terrain_size][terrain_size];
	static void printTerrain();
public:
	GLUTWindow(int* , char**);
	GLUTWindow(int , int , int , int , unsigned int , std::string , int* , char** );
	void init();
	~GLUTWindow();
};

