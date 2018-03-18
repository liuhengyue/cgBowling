#include "application.hpp"

Application::Application(int* argc, char * argv[])
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	this->windowID = initWindow("Project3 - 3D Bowling", 0, 0, 800, 800);

	this->model = new Model();
	this->view = new View();
	this->controller = new Controller(this);

	initLights();
	initCallbacks();
	initContextMenu();
}

/**
 * Run the application.
 */
void Application::start()
{
	glutMainLoop();
}

/**
 * Stop the application.
 */
void Application::exit()
{
	glutDestroyWindow(this->windowID);
	std::exit(0);
}

Controller& Application::getController()
{
	return *controller;
}

View& Application::getView()
{
	return *view;
}

Model& Application::getModel()
{
	return *model;
}

/**
 * Initializes application window.
 */
int Application::initWindow(const std::string& title, int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	int windowId = glutCreateWindow(title.c_str());

	glClearColor(0, 0, 0, 0);

	glEnable(GL_NORMALIZE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	return windowId;
}

/*
 * Initializes positions and direction of lights;
 * https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glLight.xml
 */
void Application::initLights()
{
	glEnable(GL_LIGHTING);

	//glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, 0 );
	glLightModelf( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
	//3 set pointing down lights for one lane
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	//light for pinsets
	glEnable(GL_LIGHT3);
	//light for back wall
	glEnable(GL_LIGHT4);
	float ambient[4] = { 0.2, 0.2, 0.2, 1 };
	float diffuse[4] = { 0.8, 0.8, 0.8, 1 };
	float specular[4] = { 0.7, 0.7, 0.7, 1 };
	float direction[3] = { 0, -1, 0 };
	float spot = 45;//spread angle
	float position0[4] = { 0, 85, 10, 1 };
	float position1[4] = { 0, 85, -190, 1 };
	float position2[4] = { 0, 85, -100, 1 };
	float position3[4] = { 0, 80, -170, 1 };
	float position4[4] = { 0, 60, -170, 1 };
	float direction3[3] = { 0, -1, -0.6 };
	float direction4[3] = { 0, 0.3, -1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5);//Effective light intensity is attenuated by the cosine of the angle 
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	float ambient1[4] = { 0.2, 0.2, 0.2, 1 };
	float diffuse1[4] = { 0.8, 0.8, 0.8, 1 };
	float specular1[4] = { 0.7, 0.7, 0.7, 1 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5);//Effective light intensity is attenuated by the cosine of the angle 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	float ambient2[4] = { 0.2, 0.2, 0.2, 1 };
	float diffuse2[4] = { 0.8, 0.8, 0.8, 1 };
	float specular2[4] = { 0.7, 0.7, 0.7, 1 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 5);//Effective light intensity is attenuated by the cosine of the angle 
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spot);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);

	float ambient3[4] = { 0.1, 0.1, 0.1, 1 };
	float diffuse3[4] = { 0.6, 0.6, 0.6, 1 };
	float specular3[4] = { 0.9, 0.9, 0.9, 1 };
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular3);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 1);//Effective light intensity is attenuated by the cosine of the angle 
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction3);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 40);
	glLightfv(GL_LIGHT3, GL_POSITION, position3);

	float ambient4[4] = { 0.1, 0.1, 0.1, 1 };
	float diffuse4[4] = { 0.6, 0.6, 0.6, 1 };
	float specular4[4] = { 0.2, 0.2, 0.2, 1 };
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambient4);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specular4);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 1);//Effective light intensity is attenuated by the cosine of the angle 
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction4);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 50);
	glLightfv(GL_LIGHT4, GL_POSITION, position4);

}

/**
 * Context menu initialization.
 */
void Application::initContextMenu()
{
	int fpsSubMenu = glutCreateMenu(fpsMenuEvent);
	glutAddMenuEntry("10", 10);
	glutAddMenuEntry("25", 25);
	glutAddMenuEntry("60", 60);
	glutCreateMenu(contextMenuEvent);
	glutAddMenuEntry("Exit", EXIT);
	glutAddMenuEntry("Normal camera", NORMAL_CAMERA);
	glutAddMenuEntry("Side camera", SIDE_CAMERA);
	glutAddMenuEntry("Following camera", FOLLOWING_CAMERA);
	glutAddSubMenu("FPS", fpsSubMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * Registers callbacks.
 * functions are defined in common.hpp
 */
void Application::initCallbacks()
{
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialKeyPressed);
	// glutIdleFunc(display);
	glutTimerFunc(model->FRAME_TIME, timer, 1);//wait for frame_time ms to do timer
	// glutTimerFunc(1000, timerFPS, 2);
}
