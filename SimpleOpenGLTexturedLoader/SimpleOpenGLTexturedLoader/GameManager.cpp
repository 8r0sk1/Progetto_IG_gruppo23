#pragma once
#include "lib.h"
#include <stdio.h>
#include <list>

state_type state;
GameObj player;
std::list<GameObj> objList;

//velocità di spostamento player
float xs = 0.25f; //lungo x, per click (a-d)
float zs = 0.003f; //lungo z, al secondo ???

//variabile tempo
int prev_time;

GameManager::GameManager() {
	state = paused;
	GameObj player = GameObj(0.f, 0.f, 0.f);
}

//funzione di RENDER
void GameManager::drawObj(GameObj obj) {
	glPushMatrix();
		glTranslatef(obj.x, 0.f, obj.z - player.z);
		glRotatef(obj.angle, 0.f, 1.0f, 0.f);
		glutSolidCube(1); //DA MODIFICARE IL TIPO DI OSTACOLO
	glPopMatrix();
}

void GameManager::drawPlayer() {
	glPushMatrix();
		glTranslatef(player.x, 0.f, 0.f);
		glRotatef(player.angle, 0.f, 1.0f, 0.f);
		glutSolidSphere(0.5,12,12); //DA MODIFICARE IL TIPO DI OSTACOLO
	glPopMatrix();
}

//gestione dell'IDLE
void GameManager::my_idle(int time) {
	if (state == play) {
		player.moveOf(0.f,(float)(time - prev_time) * zs); //muovo il player 
	}
	prev_time = time;
}

//gestione dell'input a seconda dello stato
void GameManager::inputManager(unsigned char key, int x, int y) {

	//fprintf(stdout, "Key pressed: %c\n", key);

	switch ((int)state) {
	//stato PLAY
	case play:
		switch (key) {
		case 'a':
			player.x -= xs;
			fprintf(stdout, "pos_x = %f\n", player.x);
			break;
		case 'd':
			player.x += xs;
			fprintf(stdout, "pos_x = %f\n", player.x);
			break;
			//reset
		case 'r':
			state = paused;
			break;
		}
		break;

	//stato PAUSED
	case paused:
		switch (key) {
		//spacebar
		case 32:
			state = play;
			player = GameObj(0.f, 0.f, 0.f); //inizializzo posizione player
			fprintf(stdout, "isStarted = %d\n", state==play);
			break;
		}
		break;

	//stato MENU
	case menu:
		//GESTIONE INPUT MENU
		break;

	//stato SCORE
	case score:
		//GESTIONE INPUT SCORE
		break;
	}
}
