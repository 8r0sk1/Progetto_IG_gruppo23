#include "Button.h"


Button::Button() {
	x = 0;
	z = 0;
	angle = 0.f;
	dim_x = 0;
	dim_z = 0;
	tag = button;
	bType = bPlay;
	toRender = true;
}

Button::Button(float pos_x, float pos_z, float l_x, float l_z, button_type type) {
	x = pos_x;
	z = pos_z;
	angle = 0.f;
	dim_x = l_x;
	dim_z = l_z;
	tag = button;
	bType = type;
	toRender = true;
}