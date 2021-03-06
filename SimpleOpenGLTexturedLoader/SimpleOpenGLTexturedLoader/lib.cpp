#include "lib.h"

void* font = GLUT_BITMAP_TIMES_ROMAN_24;
void output(int x, int y, std::string str)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.f, 5.f, -3.3f, 3.3f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glColor3f(1, 1, 1);
	glPushMatrix();
		glRasterPos2f(x, y);
		//glRasterPos3f(x, y, 5.f);
		int len = str.length();
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(font, str[i]);
		}
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

}

void renderUI(void)
{
	std::string text_row_1 = "This is written in a GLUT bitmap font.";
	std::string text_row_2 = "(positioned in pixels with upper - left origin).";
	output(-5, -3.3f, text_row_1);
	output(-5, 3.3f, text_row_2);
}