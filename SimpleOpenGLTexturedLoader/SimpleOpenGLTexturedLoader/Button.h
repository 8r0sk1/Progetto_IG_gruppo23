#pragma once

#include "GameObj.h"

enum button_type {image,tutorial_image,credits_image,bPlay,bCredits,bExit,bTutorial};

class Button : public GameObj
{
public:
	button_type bType;
	bool isMouseOn;
	bool buttonActive;

	Button();
	Button(float x,float z,float dim_x,float dim_z,button_type);
};

