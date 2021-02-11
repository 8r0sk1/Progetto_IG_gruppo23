#pragma once
#include"GameObj.h"

enum state_type { menu, play, score, paused, dead };

class GameManager
{
public:
	float state;
	GameObj player;

	GameManager();

	void drawObj(GameObj obj);
	void my_idle(int time);
	void every_frame();
	void inputManager(unsigned char key, int x, int y);
};

