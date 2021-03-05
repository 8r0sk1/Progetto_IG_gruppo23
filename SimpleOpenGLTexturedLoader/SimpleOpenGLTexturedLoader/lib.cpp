#include "lib.h"

void* font = GLUT_BITMAP_TIMES_ROMAN_24;
void output(int x, int y, std::string str)
{
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 900, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int len, i;
	glRasterPos2f(x, y);
	len = str.length();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glutPostRedisplay(); */

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 900, 0, 600);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(50, 50);  // move in 10 pixels from the left and bottom edges
	int len = str.length();
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, str[i]);
	}
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void renderUI(void)
{
	std::string text_row_1 = "This is written in a GLUT bitmap font.";
	std::string text_row_2 = "(positioned in pixels with upper - left origin).";
	output(50, 50, text_row_1);
	output(50, 145, text_row_2);
}