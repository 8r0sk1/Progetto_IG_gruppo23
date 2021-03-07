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

void output(float x, float y, std::string str)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();

		glColor3f(1, 1, 1);
		glRasterPos2f(x, y);
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
}

void renderFps(int fps) {
	output(-4.5f, -3.f, to_string(fps) + " fps");
}

void renderUI(float velocity_str, float time_str, float balls_str)
{
	output(-4.5f, -0.25f, to_string(velocity_str)+" m/s");
	output(-4.5f, 0.25f, to_string(time_str)+" seconds");
}

void renderDeadText()
{
	output(-0.5f, 0.f, "You're dead");
	output(-1.5f, -1.f, "Press R or SPACEBAR to restart");
}

void renderPressToPlayText() {
	output(-1.f, -1.f, "Press SPACEBAR to start");
}

void renderScoreText() {
	output(-0.75f, 0.f, "LEVEL 1 completed");
	output(-1.5f, -1.f, "Press SPACEBAR to start LEVEL 2");
}

int fps_calc(int time, int prev_time) {
	if(prev_time!=0)
		return (1 / ( (float) (time - prev_time) / 1000));
}