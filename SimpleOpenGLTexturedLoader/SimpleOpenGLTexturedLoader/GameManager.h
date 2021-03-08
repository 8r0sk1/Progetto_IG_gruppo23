#pragma once
#include"GameObj.h"
#include"Button.h"

enum state_type { menu, play, score, paused, dead};
enum level_type { lvl1, lvl2 };
enum menu_state_type {empty, tutorial, credits};

class GameManager
{
public:
	float state;
	GameObj player;

	GameManager();

	void drawButton(Button but);
	void drawObj(GameObj obj);
	void my_idle(int time);
	void every_frame();
	void inputManager(unsigned char key, int x, int y);
};

