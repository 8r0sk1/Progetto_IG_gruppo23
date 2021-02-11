#pragma once
#include "lib.h"

#define pi 3.14159265359

state_type state;
GameObj player = GameObj(0.f,0.f,0.f);
std::list<GameObj> objList;

//velocità di spostamento player
float angles = 22.5f; //attorno a y, per click (a-d)
float speed = 0.003f; //del player

//variabile tempo
int prev_time;

GameManager::GameManager() {
	state = paused;
	GameObj player = GameObj(0.f, 0.f, 0.f);
}

//funzione di RENDER OBJ
void GameManager::drawObj(GameObj obj) {
	glPushMatrix();
		glTranslatef(obj.x, 0.f, obj.z - player.z);
		glRotatef(obj.angle, 0.f, 1.0f, 0.f);
		glutSolidCube(1); //DA MODIFICARE IL TIPO DI OSTACOLO
	glPopMatrix();
	return;
}

//funzione di RENDER PLAYER
void GameManager::drawPlayer() {
	glPushMatrix();
		glTranslatef(player.x, 0.f, 0.f);
		glRotatef(90.f, 1.f, 0.f, 0.f); //per sistemare rotazione
		glRotatef(player.angle, 0.f, 1.0f, 0.f);
		glutSolidCone(0.5,1,12,12); //DA MODIFICARE IL TIPO DI OSTACOLO
	glPopMatrix();
	return;
}

//gestione dell'IDLE
void GameManager::my_idle(int time) {
	//PLAY
	if (state == play) {
		float radians = player.angle * 2 * pi / 360;
		float zs = speed * cos(radians) * (time - prev_time);
		float xs = speed * sin(radians) * (time - prev_time);
		player.moveOf(xs,zs); //muovo il player
	}
	prev_time = time;
	glutPostRedisplay();
}

//gestione dell'input a seconda dello stato
void GameManager::inputManager(unsigned char key, int x, int y) {

	//fprintf(stdout, "Key pressed: %c\n", key);

	switch ((int)state) {
		//stato PLAY
	case play:
		switch (key) {
		case 'a':
			if (player.angle >= -angles) {
				player.angle -= angles;
				fprintf(stdout, "pos_x = %f\n", player.x);
			}
			break;
		case 'd':
			if (player.angle <= angles) {
				player.angle += angles;
				fprintf(stdout, "pos_x = %f\n", player.x);
			}
			break;
		//reset
		case 'r':
			state = paused;
			glutPostRedisplay();
			break;
		}
		break;

		//stato PAUSED
	case paused:
		switch (key) {
		//spacebar
		case 32:
			state = play;
			glutPostRedisplay();
			break;
		}
		break;

		//stato DEAD
	case dead:
		switch (key) {
		//spacebar
		case 32:
		case 'r':
			state = paused;
			glutPostRedisplay();
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

//BEHAVIOR per ogni REDISPLAY
void GameManager::every_frame() {

	//POSIZIONAMENTO OGGETTI (statica --> DA MODIFICARE)
	GameObj cube1 = GameObj(5.f, 10.f, 60.f, 2.f, 2.f);
	GameObj cube2 = GameObj(-7.f, 8.f, 45.f, 3.f, 3.f);

	switch ((int)state) {
	case play:
		//RENDER DEGLI OGGETTI
		drawObj(cube1);
		drawObj(cube2); //passo player_z per movimento ambiente all'indietro
		drawPlayer(); //player è sempre disegnato in z=0;

		//FINE RENDER

		//COLLISION DETECTION
		if (cube1.isColliding(player.x, player.z)) {
			fprintf(stdout, "Collisione con CUBE1\n");
			state = dead;
		}
		if (cube2.isColliding(player.x, player.z)) {
			fprintf(stdout, "Collisione con CUBE2\n");
			state = dead;
		}
		break;

	case paused:
		player = GameObj(0.f, 0.f, 0.f);
		drawObj(cube1);
		drawObj(cube2);
		drawPlayer();
		break;

	case dead:
		drawObj(cube1);
		drawObj(cube2);
		drawPlayer();
		break;
	}
}
