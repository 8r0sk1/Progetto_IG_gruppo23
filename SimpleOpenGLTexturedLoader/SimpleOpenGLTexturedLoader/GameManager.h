#pragma once
#include "lib.h"

enum state_type { menu, play, score, paused };

class GameManager
{
public:
	float state;
	GameObj player;

	GameManager();

	void drawObj(GameObj obj);
	void drawPlayer();
	void my_idle(int time);
	void inputManager(unsigned char key, int x, int y);
};

