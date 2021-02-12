#pragma once
#include "lib.h"
//#include <chrono>

#define pi 3.14159265359

state_type state = paused;
GameObj player = GameObj(0.f,0.f,0.f,player_tag);
GameObj floor_carpet = GameObj(0.f, 0.f, floor_base);

//velocità di spostamento player
float angles = 22.5f; //attorno a y, per click (a-d)
float speed = 0.003f; //del player

//bumpyness obstacles
float bumpyness = 4;

//cronometro di gioco
float chronometer;

//variabile tempo
int prev_time;

//POSIZIONAMENTO OGGETTI (statica --> DA MODIFICARE)
int const obj_dim = 3;
GameObj obj[obj_dim];
void setup() {
	obj[0] = GameObj(5.f, 10.f, 60.f, 2.f, 2.f, bumpy_obstacle);
	obj[1] = GameObj(-7.f, 8.f, 45.f, 1.5f, 1.5f, deadly_obstacle);
	obj[2] = GameObj(0.f, 15.f, 15.f, 1.5f, 1.5f, collectable);
}

GameManager::GameManager() {
	state = paused;
	player = GameObj(0.f, 0.f, 0.f, player_tag);
	floor_carpet = GameObj(0.f, 0.f, floor_base);

	setup(); //vedi sopra
}

//funzione di RENDER OBJ
 void GameManager::drawObj(GameObj obj) {
	if (obj.toRender) { //controllo se obj è da renderizzare
		glPushMatrix();
		//render per ostacoli diversi
		switch (obj.tag) {

		case deadly_obstacle:
		case bumpy_obstacle:
			glTranslatef(obj.x, 0.f, obj.z - player.z);
			glRotatef(obj.angle, 0.f, 1.0f, 0.f);
			RenderModelByIndex(2);
			//glutSolidCube(obj.dim_x);
			break;

		case collectable:
			glTranslatef(obj.x, 0.f, obj.z - player.z);
			glRotatef(obj.angle, 0.f, 1.0f, 0.f);
			RenderModelByIndex(3);
			//glutSolidSphere(obj.dim_x, 10, 10);
			break;

		case player_tag:
			glTranslatef(obj.x, 0.f, 0.f);
			//glRotatef(90.f, 1.f, 0.f, 0.f); //per sistemare rotazione
			glRotatef(obj.angle, 0.f, 1.0f, 0.f);
			RenderModelByIndex(0);
			//glutSolidCone(0.5, 1, 12, 12); //DA MODIFICARE IL TIPO DI OSTACOLO
			break;

		case floor_base:
			glTranslatef(obj.x, 0.f, 0.f - player.z);
			RenderModelByIndex(1);
			break;

		}
		glPopMatrix();
	}
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
				//fprintf(stdout, "pos_x = %f\n", player.x);
			}
			break;
		case 'd':
			if (player.angle <= angles) {
				player.angle += angles;
				//fprintf(stdout, "pos_x = %f\n", player.x);
			}
			break;
		//reset
		case 'r':
			state = paused;
			setup();
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
			setup();
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

	switch ((int)state) {
	case play:
		drawObj(floor_carpet);
		//RENDER DEGLI OGGETTI
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i]);
		}
		drawObj(player);
		//FINE RENDER

		//COLLISION DETECTION
		for (int i = 0; i < obj_dim; i++) {
			if (obj[i].isColliding(player.x, player.z) && obj[i].toRender) { //controllo che avvenga collisione e che oggetto sia renderizzato a schermo
				fprintf(stdout, "Collisione con OBJ n%d of type %d\n", (i + 1), obj[i].tag);
				
				float xs, zs, radians;
				//BEHAVIOR di COLLISIONE con OBJ
				switch (obj[i].tag) {
				case bumpy_obstacle:
					//SCIVERE ANIMAZIONEEEEEEEEEEEEE
					radians = player.angle * 2 * pi / 360;
					zs = cos(radians) * bumpyness;
					xs = sin(radians) * bumpyness;
					player.moveOf(-xs,-zs);
					break;
				case deadly_obstacle:
					state = dead;
					break;
				case collectable:
					obj[i].toRender = false;
					break;
				}
			}
		}
		break;

	case paused:
		player.reset();
		drawObj(floor_carpet);
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i]);
		}
		drawObj(player);
		break;

	case dead:
		drawObj(floor_carpet);
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i]);
		}
		drawObj(player);
		break;
	}
}
