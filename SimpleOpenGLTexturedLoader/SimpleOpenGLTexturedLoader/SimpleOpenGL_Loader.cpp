//NOSTRE LIBRERIE
//#include<stdlib.h>
#include "lib.h"

//FINE NOSTRE LIBRERIE

//VARIABILI NOSTRE
GameManager gameManager;
//FINE VARIABILI NOSTRE

void reshape(int width, int height)
{
	const double aspectRatio = (float)width / height, fieldOfView = 45.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
}

// ----------------------------------------------------------------------------

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//SETUP PER PLAY
	if (gameManager.state == play || gameManager.state == paused || gameManager.state == dead) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//aspect ratio 1.5 tra bordi orizzontali e verticali (900x600)
		glOrtho(-5.f, 5.f, -3.3f, 3.3f, 0.f, 100.f); //SETUP PROIEZIONE

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.f, 5.f, 0.3f,
			0.f, 0.f, -2.f,
			0.f, 1.f, 0.f);
	}

	gameManager.every_frame(); //definizione in GameManager
	glutSwapBuffers();
}

// ----------------------------------------------------------------------------

//CODICE NOSTRO
void keyboard(unsigned char key, int x, int y) {
	gameManager.inputManager(key, x, y);
	return;
}

void mouse(int button, int state, int x, int y) {
	gameManager.inputManager('*', x, y);
	return;
}

void mouseMotionFunc(int x, int y) {
	gameManager.mouseMotion(x, y);
}

void idle() {
	int time = glutGet(GLUT_ELAPSED_TIME);
	gameManager.my_idle(time);
	return;
}

//FINE CODICE NOSTRO

int main(int argc, char** argv)
{
	glutInitWindowSize(900, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	glutCreateWindow("Shining_project");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//CODICE NOSTRO
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMotionFunc);
	glutIdleFunc(idle);

	if (!LoadScene("..//_models//OpenGLModels.dae"))
	{
		fprintf(stderr, "Scene Loading failed");
		return 0;
	}

	gameManager = GameManager(); //inizializzo il GameManager

	glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	ReleaseScene();

	return 0;
}
