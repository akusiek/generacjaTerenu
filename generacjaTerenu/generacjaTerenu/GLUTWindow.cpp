#include "GLUTWindow.h"

glm::vec3 GLUTWindow::cameraPos;
glm::vec3 GLUTWindow::cameraFront;
glm::vec3 GLUTWindow::cameraUp;


float GLUTWindow::lastX;
float GLUTWindow::lastY;

float GLUTWindow::yaw;
float GLUTWindow::pitch;

int GLUTWindow::win_width;
int GLUTWindow::win_height;

float GLUTWindow::forwardSpeed;
float GLUTWindow::backwardSpeed;
float GLUTWindow::leftSpeed;
float GLUTWindow::rightSpeed;
float GLUTWindow::upSpeed;
float GLUTWindow::downSpeed;

bool GLUTWindow::isFirstMouse;
bool GLUTWindow::firstRender;

Lights* GLUTWindow::lights = new Lights();
OperacjeNaWektorach* GLUTWindow::operacjeNaWektorach = new OperacjeNaWektorach();
SystemDrzew* GLUTWindow::systemDrzew = new SystemDrzew();

Terrain* GLUTWindow::terrain = new Terrain();

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
	isFirstMouse = true;
	firstRender = true;
	forwardSpeed = 0.0f;
	backwardSpeed = 0.0f;
	leftSpeed = 0.0f;
	rightSpeed = 0.0f;
	upSpeed = 0.0f;
	downSpeed = 0.0f;
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
	isFirstMouse = true;
	firstRender = true;
	forwardSpeed = 0.0f;
	backwardSpeed = 0.0f;
	leftSpeed = 0.0f;
	rightSpeed = 0.0f;
	upSpeed = 0.0f;
	downSpeed = 0.0f;
}

void GLUTWindow::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lights->obsluzOswietlenie();

	glLoadIdentity();

	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
			cameraPos.x+cameraFront.x, cameraPos.y+cameraFront.y, cameraPos.z+cameraFront.z,
			cameraUp.x, cameraUp.y, cameraUp.z);

	glShadeModel(GL_SMOOTH);
	glColor3f(0.5f, 0.5f, 0.5f);
	terrain->render(1);
	glColor3f(0.5, 0.1, 0.1);
	glShadeModel(GL_FLAT);
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
	case 'a': leftSpeed = -0.1f; break;
	case 'd': rightSpeed = 0.1f; break;
	case 'w': forwardSpeed = 0.1f; break;
	case 's': backwardSpeed = -0.1f; break;
	case '-': lights->changBackgroundLignt(-0.1); break;
	case '+': lights->changBackgroundLignt(0.1); break;
	case ' ': upSpeed = 0.1f; break;
	case 'c': downSpeed = -0.1f; break;
	}
}

void GLUTWindow::keyReleased(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0); break;
	case 'a': leftSpeed = 0.0f; break;
	case 'd': rightSpeed = 0.0f; break;
	case 'w': forwardSpeed = 0.0f; break;
	case 's': backwardSpeed = 0.0f; break;
	case ' ': upSpeed = 0.0f; break;
	case 'c': downSpeed = 0.0f; break;
	}
}

void GLUTWindow::calculatePosition() {
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (leftSpeed + rightSpeed) + (forwardSpeed+backwardSpeed)*cameraFront + (upSpeed + downSpeed)*cameraUp;
	glutPostRedisplay();
}

void GLUTWindow::keyStrokes() {
	if (((forwardSpeed + backwardSpeed) != 0) || ((leftSpeed + rightSpeed) != 0) || ((upSpeed + downSpeed) != 0)) {
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

void GLUTWindow::init() {	
	terrain->generate(3000, 1, 0.4f);
	terrain->smoother(0);

	systemDrzew->generuj(terrain);

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
