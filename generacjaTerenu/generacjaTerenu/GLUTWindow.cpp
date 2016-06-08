#include "GLUTWindow.h"

glm::vec3 GLUTWindow::cameraPos;
glm::vec3 GLUTWindow::cameraFront;
glm::vec3 GLUTWindow::cameraUp;

float GLUTWindow::terrain[terrain_size][terrain_size];

float GLUTWindow::lastX;
float GLUTWindow::lastY;

float GLUTWindow::yaw;
float GLUTWindow::pitch;

bool GLUTWindow::isFirstMouse;


GLUTWindow::GLUTWindow(int* argc_, char **argv_)
{
	win_pos_x = -1;
	win_pos_y = -1;
	win_width = 800;
	win_height = 600;
	displ_mod = GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA;
	win_name = "GLUT";
	argc = argc_;
	argv = argv_;
	cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	lastX = win_width / 2;
	lastY = win_height / 2;
	yaw = 0;
	pitch = 0;
	isFirstMouse = true;
}

GLUTWindow::GLUTWindow(int posX, int posY, int width, int height, unsigned int mode, std::string name, int* argc_, char **argv_) {
	win_pos_x = posX;
	win_pos_y = posY;
	win_width = width;
	win_height = height;
	displ_mod = mode;
	win_name = name;
	argc = argc_;
	argv = argv_;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	lastX = win_width / 2;
	lastY = win_height / 2;
	yaw = 0;
	pitch = 0;
	isFirstMouse = true;
}

void GLUTWindow::generateTerrain(int iterations) {
	int i = 0;
	int x = rand() % terrain_size;
	int z = rand() % terrain_size;
	while (i < iterations) {
		//terrain[x][z] += (float)(iterations / (i + 1)*10);
		terrain[x][z] += 2.0f;
		int move = rand() % 4;
		switch (move) {
		case 0:
			if (x + 1 > terrain_size-1)
				x = 0;
			else
				x++;
			break;
		case 1:
			if (x - 1 < 0)
				x = terrain_size-1;
			else
				x--;
			break;
		case 2:
			if (z + 1 > terrain_size-1)
				z = 0;
			else
				z++;
			break;
		case 3:
			if (z - 1 < 0)
				z = terrain_size-1;
			else
				z--;
			break;
		}
		++i;
	}
}

void GLUTWindow::printTerrain() {
	for (int x = 0; x < 9; x++) {
		for (int z = 0; z < 9; z++) {
			std::cout << terrain[x][z] << " ";
		}
		std::cout << std::endl;
	}
}

void GLUTWindow::renderTerrain(unsigned int mode) {
	switch (mode) {
	case 0: //dots
		for (int x = 0; x < terrain_size; ++x) {
			for (int z = 0; z < terrain_size; ++z) {
				glColor3f(0.0f, 1.0f, 0.0f);
				glScalef(1.5f, 1.5f, 1.5f);
				glBegin(GL_POINTS);
					glVertex3f(x, terrain[x][z], z);
				glEnd();
			}
		}
		break;
	case 1: //triangles
		break;
	case 2: //squares
		for (int x = 0; x < terrain_size - 1; ++x) {
			for (int z = 0; z < terrain_size - 1; ++z) {
				glColor3f(0.5f, 0.5f, 0.5f);
				glBegin(GL_QUADS);
					glVertex3f(x*0.1f, terrain[x][z]*0.1f, z*0.1f);
					glVertex3f(x*0.1f, terrain[x][z+1]*0.1f, (z+1)*0.1);
					glVertex3f((x+1)*0.1f, terrain[x+1][z+1]*0.1f, (z+1)*0.1f);
					glVertex3f((x+1)*0.1f, terrain[x+1][z]*0.1f, z*0.1f);
				glEnd();
			}
		}
		break;
	}
}

void GLUTWindow::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
			cameraPos.x+cameraFront.x, cameraPos.y+cameraFront.y, cameraPos.z+cameraFront.z,
			cameraUp.x, cameraUp.y, cameraUp.z);
	/*glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-5.0f, -10.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);
		glVertex3f(5.0f, -10.0f, 0.0f);
	glEnd();*/

	glColor3f(0.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.1f, 0.0f);
		glVertex3f(0.0f, 0.1f, terrain_size*0.1f);
		glVertex3f(terrain_size*0.1f, 0.1f, terrain_size*0.1f);
		glVertex3f(terrain_size*0.1f, 0.1f, 0.0f);
	glEnd();

	renderTerrain(2);

	glutSwapBuffers();
}

void GLUTWindow::changeSize(int w, int h) {
	if(h == 0)
		h = 1;

	double ratio = 1.0*w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	//glEnable(GL_LIGHTING);
}

void GLUTWindow::processKeys(unsigned char key, int x, int y) {
	
	float speed = 0.05f;

	if (key == 27)
		exit(0);
	else if (key == 'a') {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	}
	else if (key == 'd') {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	}
	else if (key == 'w') {
		cameraPos += speed*cameraFront;
	}
	else if (key == 's') {
		cameraPos -= speed*cameraFront;
	}
	else if (key == ' ') {
		cameraPos += speed*cameraUp;
	}
}

void GLUTWindow::processMouseMovement(int x, int y) {
	if (isFirstMouse) {
		lastX = x;
		lastY = y;
		isFirstMouse = false;
	}

	float offsetX = x - lastX;
	float offsetY = lastY - y;

	lastX = x;
	lastY = y;

	float sensitivity = 0.1f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);	
}

void GLUTWindow::init() {
	srand(time(NULL));
	generateTerrain(5000);

	printTerrain();
	glutInit(argc, argv);
	glutInitDisplayMode(displ_mod);
	glutInitWindowPosition(win_pos_x, win_pos_y);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow(win_name.c_str());
	//glutEnterGameMode();

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processKeys);
	glutPassiveMotionFunc(processMouseMovement);

	//glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}

GLUTWindow::~GLUTWindow()
{
}
