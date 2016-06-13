#include "GLUTWindow.h"

glm::vec3 GLUTWindow::cameraPos;
glm::vec3 GLUTWindow::cameraFront;
glm::vec3 GLUTWindow::cameraUp;

float GLUTWindow::terrain[terrain_size][terrain_size];

float GLUTWindow::lastX;
float GLUTWindow::lastY;

float GLUTWindow::yaw;
float GLUTWindow::pitch;

int GLUTWindow::win_width;
int GLUTWindow::win_height;

float GLUTWindow::moveSpeedFrontBack;
float GLUTWindow::moveSpeedLeftRight;
float GLUTWindow::moveSpeedUpDown;

bool GLUTWindow::isFirstMouse;
bool GLUTWindow::firstRender;

Lights* GLUTWindow::lights = new Lights();
OperacjeNaWektorach* GLUTWindow::operacjeNaWektorach = new OperacjeNaWektorach();
SystemDrzew* GLUTWindow::systemDrzew = new SystemDrzew();

//float GLUTWindow::smooth_factor;


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
	lastX = (float)win_width / 2;
	lastY = (float)win_height / 2;
	yaw = 0;
	pitch = 0;
	moveSpeedFrontBack = 0.0f;
	moveSpeedLeftRight = 0.0f;
	moveSpeedUpDown = 0.0f;
	isFirstMouse = true;
	firstRender = true;
	//smooth_factor = 0.11111f;
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
	lastX = (float)win_width / 2;
	lastY = (float)win_height / 2;
	yaw = 0;
	pitch = 0;
	moveSpeedFrontBack = 0.0f;
	moveSpeedLeftRight = 0.0f;
	moveSpeedUpDown = 0.0f;
	isFirstMouse = true;
	firstRender = true;
	//smooth_factor = 0.11111f;
}

void GLUTWindow::generateTerrain(int iterations, int which, float increment) { // TODO: flatten the terrain and maybe try another algorithm
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
				glVertex3f((GLfloat)x, (GLfloat)terrain[x][z], (GLfloat)z);
				glEnd();
			}
		}
		break;
	case 1: // TODO: terrain rendering with triangle usage 
		for (int x = 0; x < terrain_size - 1; ++x) {
			for (int z = 0; z < terrain_size - 1; ++z) {
				glColor3f(0.5f, 0.5f, 0.5f);
				glBegin(GL_TRIANGLES);
				glVertex3f((GLfloat)x*0.1f, (GLfloat)terrain[x][z] * 0.1f, (GLfloat)z*0.1f);
				glVertex3f((GLfloat)x*0.1f, (GLfloat)terrain[x][z + 1] * 0.1f, (GLfloat)(z + 1)*0.1f);
				glVertex3f((GLfloat)(x + 1)*0.1f, (GLfloat)terrain[x + 1][z + 1] * 0.1f, (GLfloat)(z + 1)*0.1f);
				glEnd();
				glBegin(GL_TRIANGLES);
				glVertex3f((GLfloat)(x + 1)*0.1f, (GLfloat)terrain[x + 1][z + 1] * 0.1f, (GLfloat)(z + 1)*0.1f);
				glVertex3f((GLfloat)(x + 1)*0.1f, (GLfloat)terrain[x + 1][z] * 0.1f, (GLfloat)z*0.1f);
				glVertex3f((GLfloat)x*0.1f, (GLfloat)terrain[x][z] * 0.1f, (GLfloat)z*0.1f);
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
}

void GLUTWindow::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lights->obsluzOswietlenie();

	glLoadIdentity();

	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
			cameraPos.x+cameraFront.x, cameraPos.y+cameraFront.y, cameraPos.z+cameraFront.z,
			cameraUp.x, cameraUp.y, cameraUp.z);

	glColor3f(0.0f, 0.0f, 0.5f);
	//glBegin(GL_QUADS);
	//	glVertex3f(0.0f, 0.1f, 0.0f);
	//	glVertex3f(0.0f, 0.1f, terrain_size*0.1f);
	//	glVertex3f(terrain_size*0.1f, 0.1f, terrain_size*0.1f);
	//	glVertex3f(terrain_size*0.1f, 0.1f, 0.0f);
	//glEnd();
	glShadeModel(GL_SMOOTH);
	glColor3f(0.5f, 0.5f, 0.5f);
	renderTerrain(2);
	glColor3f(1.0f, 1.0f, 1.0f);
	systemDrzew->Rysuj();
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
}

void GLUTWindow::keyPressed(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0); break;
	case 'a': (moveSpeedLeftRight == 0.0f) ? moveSpeedLeftRight = -0.1f : moveSpeedLeftRight = 0.1f; break;
	case 'd': (moveSpeedLeftRight == 0.0f) ? moveSpeedLeftRight = 0.1f : moveSpeedLeftRight = -0.1f; break;
	case 'w': (moveSpeedFrontBack == 0.0f) ? moveSpeedFrontBack = 0.1f : moveSpeedFrontBack = -0.1f; break;
	case 's': (moveSpeedFrontBack == 0.0f) ? moveSpeedFrontBack = -0.1f : moveSpeedFrontBack = 0.1f; break;
	case '-': lights->changBackgroundLignt(-0.1); break;
	case '+': lights->changBackgroundLignt(0.1); break;
	case ' ': (moveSpeedUpDown == 0.0f) ? moveSpeedUpDown = 0.1f : moveSpeedUpDown = -0.1f; break;
	case 'c': (moveSpeedUpDown == 0.0f) ? moveSpeedUpDown = -0.1f : moveSpeedUpDown = 0.1f; break;
	}
}

void GLUTWindow::keyReleased(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0); break;
	case 'a': 
	case 'd': moveSpeedLeftRight = 0.0f; break;
	case 'w': 
	case 's': moveSpeedFrontBack = 0.0f; break;
	case ' ': 
	case 'c': moveSpeedUpDown = 0.0f; break;
	}
}

void GLUTWindow::calculatePosition() {
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * moveSpeedLeftRight;
	cameraPos += moveSpeedFrontBack*cameraFront;
	cameraPos += moveSpeedUpDown*cameraUp;
	glutPostRedisplay();
}

void GLUTWindow::keyStrokes() {
	if ((moveSpeedFrontBack != 0) || (moveSpeedLeftRight != 0) || (moveSpeedUpDown != 0)) {
		calculatePosition();
	}
	if (firstRender) {
		glutPostRedisplay();
		firstRender = false;
	}
}
void GLUTWindow::processMouseMovement(int x, int y) {
	if (isFirstMouse) {
		lastX = (float)x;
		lastY = (float)y;
		isFirstMouse = false;
	}

	float offsetX = x - lastX;
	float offsetY = lastY - y;

	lastX = (float)x;
	lastY = (float)y;

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

	glutPostRedisplay();

	if ((x < win_width / 2) || (x > win_width / 2) || (y < win_height / 2) || (y > win_height / 2)) {
		glutWarpPointer(win_width/2, win_height/2);
		isFirstMouse = true;
	}
}

void GLUTWindow::whereIsCursor(int state) {
	if (state == GLUT_LEFT) {
		isFirstMouse = true;
	}
}

void GLUTWindow::smootherTerrain(unsigned int type) {
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

void GLUTWindow::init() {
	srand(time(NULL));
	//srand(0);
	//for (int i = 0; i < 100; i++)
		generateTerrain(1000, 1, 0.4f);

	smootherTerrain(0);
	printTerrain();

	glutInit(argc, argv);
	glutInitDisplayMode(displ_mod);
	glutInitWindowPosition(win_pos_x, win_pos_y);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow(win_name.c_str());
	//glutEnterGameMode();
	
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(keyStrokes); 
	glutKeyboardFunc(keyPressed); 
	glutKeyboardUpFunc(keyReleased);
	glutPassiveMotionFunc(processMouseMovement);
	glutEntryFunc(whereIsCursor);

	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);

	glutIgnoreKeyRepeat(1);

	glutPostRedisplay();
	glutMainLoop();
}

GLUTWindow::~GLUTWindow()
{
}
