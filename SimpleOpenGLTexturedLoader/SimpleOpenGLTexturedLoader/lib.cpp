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

void get3Dpos(float* x, float* y) {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble object_x, object_y, object_z;
	float mouse_x = *x;
	float mouse_y = *y;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)mouse_x;
	winY = (float)viewport[3] - (float)mouse_y - 1.0f;
	glReadBuffer(GL_BACK);
	glReadPixels(mouse_x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &object_x, &object_y, &object_z);
	*x = object_x;
	*y = object_y;
	//*pp.z = object_z;
}