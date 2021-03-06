#include "lib.h"
#include <sstream>

void* font = GLUT_BITMAP_9_BY_15; //for bitmap
//void* font = GLUT_STROKE_ROMAN; //for stroke

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

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
			//glScalef(5.f, 5.f, 5.f); //NOT WORKING
			glutBitmapCharacter(font, str[i]);
			//glutStrokeCharacter(font, str[i]);
		}
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

}

void renderUI(float velocity_str, float time_str, float balls_str)
{
	output(-4.8f, -0.5f, to_string(velocity_str)+" m/s");
	output(-4.8f, 1.f, to_string(time_str)+" seconds");
}

void renderDeadText()
{
	output(-0.8f, 0.f, "You're dead");
	output(-1.75f, -1.f, "Press R or SPACEBAR to restart");
}

void renderPressToPlayText() {
	output(-1.5f, -1.f, "Press SPACEBAR to start");
}

void renderScoreText() {
	output(-1.5f, 0.f, "LEVEL 1 completed");
}