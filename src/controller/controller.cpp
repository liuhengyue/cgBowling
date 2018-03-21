#include "controller.hpp"

Controller::Controller(Application* app)
{
	this->application = app;
}

void Controller::contextMenuEvent(int value)
{
	switch (value)
	{
		case NORMAL_CAMERA:
			application->getModel().setCameraMode(NORMAL);
			break;

		case SIDE_CAMERA:
			application->getModel().setCameraMode(SIDE);
			break;

		case FOLLOWING_CAMERA:
			application->getModel().setCameraMode(FOLLOWING);
			break;

		case FPS:
			application->getModel().setCameraMode(FOLLOWING);
			break;

		case EXIT:
			application->exit();
			break;
	}
}

void Controller::fpsMenuEvent(int value)
{
	application->getModel().setFPS(value);
	// std::cout << value << " " << FRAME_TIME <<  std::endl;
}

void Controller::keyPressed(unsigned char key)
{
	if (application->getModel().isAnimating())
	{
		if (key == 27)
		{
			application->exit();
		}
		
		else if (key == 32)//SPACEBAR key
		{
			application->pause();
		}
		return;
	}

	switch (key)
	{
		case 'e':
			application->getModel().setDirection(RIGHT);
			break;

		case 'q':
			application->getModel().setDirection(LEFT);
			break;

		case 'd':
			application->getModel().setRotation(RIGHT);
			break;

		case 'a':
			application->getModel().setRotation(LEFT);
			break;

		case 32://SPACEBAR key
			application->pause();
			break;

		case 13://Enter key
			application->getModel().startAnimation();
			break;

		case 27:// Escape key
			application->exit();
			break;
	}
}
//https://www.opengl.org/resources/libraries/glut/spec3/node54.html
void Controller::specialKeyPressed(int key)
{
	if (application->getModel().isAnimating())
	{
		return;
	}

	switch (key)
	{
		case GLUT_KEY_UP:
			application->getModel().setPower(INCREASE);
			break;

		case GLUT_KEY_DOWN:
			application->getModel().setPower(DECREASE);
			break;

		case GLUT_KEY_RIGHT:
			application->getModel().setPosition(RIGHT);
			break;

		case GLUT_KEY_LEFT:
			application->getModel().setPosition(LEFT);
			break;
	}
}
