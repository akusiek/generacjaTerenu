#pragma once
#include <string>
#include <GL/freeglut.h>
#include <iostream>
#include "glm.hpp"
#include "Lights.h"
#include "OperacjeNaWektorach.h"
#include "SystemDrzew.h"
#include "Terrain.h"

class GLUTWindow
{
	int win_pos_x, win_pos_y;
	static int win_width, win_height;
	unsigned int displ_mod;
	std::string win_name;
	int* argc;
	char** argv;
	// GLUT functions
	static void renderScene();
	static void changeSize(int w, int h);
	static void keyPressed(unsigned char, int, int);
	static void keyReleased(unsigned char, int, int);
	static void keyStrokes();
	static void processMouseKeys(int button, int state, int x, int y);
	static void processMouseMovement(int x,int y);
	static void whereIsCursor(int state);
	static void calculatePosition();
	
	//Camera arguments
	static glm::vec3 cameraPos; 
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;

	static bool isFirstMouse, firstRender;
	static float lastX, lastY;
	static float yaw, pitch;

	static float forwardSpeed;
	static float backwardSpeed;
	static float leftSpeed;
	static float rightSpeed;
	static float upSpeed;
	static float downSpeed;

	// Objects
	static Terrain* terrain;
	static Lights * lights;
	static OperacjeNaWektorach * operacjeNaWektorach;
	static SystemDrzew * systemDrzew;
public:
	GLUTWindow(int* , char**);
	GLUTWindow(int , int , int , int , unsigned int , std::string , int* , char** );
	void init();
	~GLUTWindow();
};