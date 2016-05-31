#include "GLUTWindow.h"

float GLUTWindow::angleH;
float GLUTWindow::angleV;
float GLUTWindow::x;
float GLUTWindow::y;
float GLUTWindow::z;
float GLUTWindow::lx;
float GLUTWindow::ly;
float GLUTWindow::lz;
float GLUTWindow::deltaAngleX;
float GLUTWindow::deltaAngleY;

int GLUTWindow::xOrigin;
int GLUTWindow::yOrigin;

GLUTWindow::GLUTWindow(int* argc_, char **argv_)
{
	win_pos_x = -1;
	win_pos_y = -1;
	win_width = 640;
	win_height = 480;
	displ_mod = GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA;
	win_name = "GLUT";
	argc = argc_;
	argv = argv_;
	angleH = 0.0f;
	angleV = 0.0f;
	x = 0.0f;
	y = 1.0f;
	z = 5.0f;
	lx = 0.0f;
	ly = 1.0f;
	lz = -1.0f;
	deltaAngleX = 0.0f;
	deltaAngleY = 0.0f;
	xOrigin = -1;
	yOrigin = -1;
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
	angleH = 0.0f;
	angleV = 0.0f;
	x = 0.0f;
	y = 0.0f;
	z = -20.0f;
	lx = 0.0f;
	ly = 1.0f;
	lz = -1.0f;
	deltaAngleX = 0.0f;
	deltaAngleY = 0.0f;
	xOrigin = -1;
	yOrigin = -1;
}

void GLUTWindow::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(x, y, z,
			 x+lx, y+ly, z+lz,
			 0.0f, 1.0f, 0.0f);

	//glBegin(GL_TRIANGLES);
	//	glVertex3f(-2.0f, -2.0f, -5.0f);
	//	glVertex3f(2.0f, 0.0f, -5.0f);
	//	glVertex3f(0.0f, 2.0f, -5.0f);
	//glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f(-5.0f, -10.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);
		glVertex3f(5.0f, -10.0f, 0.0f);
	glEnd();

	glutSwapBuffers();
}

void GLUTWindow::changeSize(int w, int h) {
	if(h == 0)
		h = 1;

	float ratio = 1.0*w / h;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);
	
	gluPerspective(45, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
}

void GLUTWindow::processKeys(unsigned char key, int x, int y) {
	
	float fraction = 0.2f;

	if (key == 27)
		exit(0);
	/*else if (key == 'a') {
		angleH -= 0.001f;
		lx = sin(angleH);
		lz = -cos(angleH);
	}
	else if (key == 'd') {
		angleH += 0.001f;
		lx = sin(angleH);
		lz = -cos(angleH);
	}*/
	else if (key == 'w') {
		x += lx * fraction;
		z += lz * fraction;
	}
	else if (key == 's') {
		x -= lx * fraction;
		z -= lz * fraction;
	}
}

void GLUTWindow::processMouseKeys(int button, int state, int x, int y) {

	if (button == GLUT_RIGHT_BUTTON) {

		if (state == GLUT_UP) {
			angleH += deltaAngleX;
			angleV += deltaAngleY;
			xOrigin = -1;
			yOrigin = -1;
		}
		else {
			xOrigin = x;
			yOrigin = y;
		}
	}
}

void GLUTWindow::processMouseMovement(int x, int y) {
	if (xOrigin >= 0) {
		deltaAngleX = (x - xOrigin) * 0.001f;
		deltaAngleY = (y - yOrigin) * 0.005f;

		lx = sin(angleH + deltaAngleX);
		lz = -cos(angleH + deltaAngleX);
		ly = cos(angleV + deltaAngleY);
	}
}

void GLUTWindow::init() {
	glutInit(argc, argv);
	glutInitDisplayMode(displ_mod);
	glutInitWindowPosition(win_pos_x, win_pos_y);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow(win_name.c_str());

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseKeys);
	glutMotionFunc(processMouseMovement);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}

GLUTWindow::~GLUTWindow()
{
}
