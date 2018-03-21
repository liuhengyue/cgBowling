#include "application.hpp"

static Application * application;

static int near = 1;
static int far = 999;

/**
 * Window resize event handler.
 */
void resize(int width, int height)
{
	if (width == 0 || height == 0)
		return;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / height, near, far);
	glMatrixMode(GL_MODELVIEW);

	display();
}

/**
 * The main drawing function.
 */
void display()
{
	//if not paused
	if(!application->isPaused()){
		View & view = application->getView();
		Model & model = application->getModel();

		model.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		view.render(model);

		glFlush();
		glutSwapBuffers();
	}
	// std::cout << "called" << std::endl;
	// glutTimerFunc(1000, timerFPS, 2);
}

/**
 * Context menu handler.
 */
void contextMenuEvent(int value)
{
	application->getController().contextMenuEvent(value);
}
void fpsMenuEvent(int value)
{
	application->getController().fpsMenuEvent(value);
}

void keyPressed(unsigned char key, int x, int y)
{
	application->getController().keyPressed(key);
}

void specialKeyPressed(int key, int x, int y)
{
	application->getController().specialKeyPressed(key);
}

/**
 * Timer elapsed event handler.
 * If animation stops, reset the model to original position
 * control framerate
 */
void timer(int value)
{
	static unsigned int counter = 0;
	// std::cout << "FPS: " << FRAME_TIME << std::endl;
	Model & model = application->getModel();
	// std::cout << application->isPaused() << " ";
	// std::cout << counter << std::endl;
	//wait for a few ms to reset
	if (!application->isPaused() && model.isAnimating() && model.hasAnimationElapsed() && counter++ > model.WAITING_TIME)
	{
		counter = 0;
		model.reset();
	}
	// std::cout << application->isPaused() << " ";
	glutPostRedisplay();
	glutTimerFunc(1000.0/model.FRAME_TIME, timer, value);
}

/**
 * Main function.
 */
int main(int argc, char * argv[])
{
	application = new Application(&argc, argv);

	View & view = application->getView();
	Model & model = application->getModel();

	view.texturize(model);

	application->start();

	return 0;
}
