#pragma once
#include "lib.h"
//#include <chrono>

#define pi 3.14159265359

state_type state = paused;
GameObj player;
GameObj floor_carpet;

int current_level = 1;
int num_obj_level = 15;

//velocità di spostamento player
float angles = 22.5f; //attorno a y, per click (a-d)
float speed = 0; //del player
float maxSpeed = 0.003f;
float deltaSpeed = 0.000025f;
float steering_speedFactor = 0.5f;

bool isJumping = false;
float jump_time_start;
float jump_time = 300; //jumping time in ms

//boosts
int boosts = 0;

//bumpyness obstacles
float bumpyness = 1;

//cronometro di gioco
float chronometer = 0;
float chronometer_start = 0;

//variabile tempo
int prev_time;

type type_obstacle() {
	int random_obstacle = rand() % 5 + 2;
	if (random_obstacle == 0) {
		return bumpy_obstacle;
	}
	else if (random_obstacle == 1) {
		return bumpy_obstacle;
	}
	else {
		return bumpy_obstacle;
	}
}

//POSIZIONAMENTO OGGETTI (statica --> DA MODIFICARE)
int const obj_dim = 30;
GameObj obj[30];
void setup() {
	speed = 0; //resetto velocità player
	boosts = 0; //resetto boost

	obj[0] = GameObj(-1.f, -40.f, 0.f, collectable); //first level
	obj[1] = GameObj(0.f, -84.f, 0.f, collectable);
	obj[2] = GameObj(1.f, -100.f, 0.f, collectable);
	obj[3] = GameObj(-1.f, -36.f, 0.f, deadly_obstacle);
	obj[4] = GameObj(1.f, -96.f, 0.f, deadly_obstacle);
	obj[5] = GameObj(0.f, -4.f, 0.f, stair);
	obj[6] = GameObj(0.f, -52.f, 0.f, stair);
	obj[7] = GameObj(1.f, 0.f, 0.f, bumpy_obstacle);
	obj[8] = GameObj(-1.f, -8.f, 0.f, bumpy_obstacle);
	obj[9] = GameObj(1.f, -24.f, 0.f, bumpy_obstacle);
	obj[10] = GameObj(-1.f, -32.f, 0.f, bumpy_obstacle);
	obj[11] = GameObj(0.f, -56.f, 0.f, bumpy_obstacle);
	obj[12] = GameObj(1.f, -72.f, 0.f, bumpy_obstacle);
	obj[13] = GameObj(-1.f, -92.f, 0.f, bumpy_obstacle);
	obj[14] = GameObj(1.f, -112.f, 0.f, bumpy_obstacle);
	obj[15] = GameObj(-1.f, -12.f, 0.f, collectable); //second level
	obj[16] = GameObj(0.f, -16.f, 0.f, deadly_obstacle);
	obj[17] = GameObj(0.f, -28.f, 0.f, stair);
	obj[18] = GameObj(0.f, -108.f, 0.f, stair);
	obj[19] = GameObj(1.f, -68.f, 0.f, bumpy_obstacle);
	obj[20] = GameObj(-1.f, -48.f, 0.f, bumpy_obstacle);
	obj[21] = GameObj(0.f, -120.f, 0.f, bumpy_obstacle);
	obj[22] = GameObj(1.f, -60.f, 0.f, collectable); //third level
	obj[23] = GameObj(-1.f, -116.f, 0.f, deadly_obstacle);
	obj[24] = GameObj(0.f, -76.f, 0.f, stair);
	obj[25] = GameObj(-1.f, -20.f, 0.f, bumpy_obstacle);
	obj[26] = GameObj(0.f, -44.f, 0.f, bumpy_obstacle);
	obj[27] = GameObj(1.f, -64.f, 0.f, bumpy_obstacle);
	obj[28] = GameObj(-1.f, -80.f, 0.f, bumpy_obstacle);
	obj[29] = GameObj(1.f, -104.f, 0.f, bumpy_obstacle);
}

GameManager::GameManager() {
	state = paused;

	player = GameObj(0.f, 0.f, 0.f, player_tag);
	player.reset(); //faccio reset = setup

	floor_carpet = GameObj(0.f, -5.5f, floor_tag); //da -5.5 a 119 z

	setup(); //vedi sopra
}

/*
0 -> Tricilo
1 -> Floor
2 -> Sofa
3 -> Chair
4 -> Bin
5 -> Ball
6 -> Stairs
7 -> Doll
*/

//funzione di RENDER OBJ
void GameManager::drawObj(GameObj obj) {
	if (obj.toRender) { //obj.toRender
		glPushMatrix();
		//render per ostacoli diversi

		if (obj.tag == player_tag) {
			glTranslatef(obj.x, 0.f, 0.f);
			glRotatef(-obj.angle, 0.f, 1.0f, 0.f);
			RenderModelByIndex(0);
		}

		if (obj.tag == floor_tag) {
			glTranslatef(0.f, 0.f, obj.z - player.z);
			RenderModelByIndex(1);
		}

		if (obj.z - 5 < player.z && obj.z + 5 > player.z) {
			switch (obj.tag) {

			case stair:
				glTranslatef(obj.x, 0.f, obj.z - player.z);
				RenderModelByIndex(6);
				break;

			case deadly_obstacle:
				glTranslatef(obj.x, 0.f, obj.z - player.z);
				RenderModelByIndex(7);
				break;

			case bumpy_obstacle:
				glTranslatef(obj.x, 0.f, obj.z - player.z);
				RenderModelByIndex(2);
				break;

			case collectable:
				glTranslatef(obj.x, 0.f, obj.z - player.z);
				RenderModelByIndex(5);
				break;
			}
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
		float zs = -speed * (time - prev_time);
		float xs = speed * sin(radians) * (time - prev_time) * steering_speedFactor;
		player.moveOf(xs, zs); //muovo il player

		if (speed < maxSpeed) {
			speed = speed + deltaSpeed;
		}

		//conteggio tempo
		chronometer = time - chronometer_start;
		//DEBUG
		float seconds = chronometer / 1000;
		printf("Chronometer : %f seconds\n", seconds);
	}
	prev_time = time;

	if (state == paused) {
		chronometer_start = time;
	}

	//controllo isJumping
	if (!isJumping) {
		jump_time_start = time;
	}
	else if (time - jump_time_start > jump_time){
		isJumping = false;
	}

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
		case 'w':
			if (boosts > 0) {
				boosts--;
				speed = speed + deltaSpeed * 100;
			}
			break;
		case 32:
			if (!isJumping) {
				isJumping = true;
				//da aggiungere animazione salto
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
		//RENDER SCENA 3D
		drawObj(player);
		drawObj(floor_carpet);
		//RENDER DEGLI OGGETTI
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i]);
		}
		//COLLISION DETECTION
		for (int i = 0; i < obj_dim; i++) {
			if (obj[i].isColliding(player.x, player.z) && obj[i].toRender) { //controllo che avvenga collisione e che oggetto sia renderizzato a schermo
				fprintf(stdout, "Collisione con OBJ n%d of type %d\n", (i + 1), obj[i].tag);

				//float xs, zs, radians;
				//BEHAVIOR di COLLISIONE con OBJ
				switch (obj[i].tag) {
				case bumpy_obstacle:
					/*radians = player.angle * 2 * pi / 360;
					zs = cos(radians) * bumpyness;
					xs = sin(radians) * bumpyness;
					player.moveOf(xs, zs);*/
					speed = -(maxSpeed+speed)/5 * bumpyness;
					break;
				case deadly_obstacle:
					if(!isJumping) state = dead;
					break;
				case collectable:
					boosts++;
					obj[i].toRender = false;
					break;
				}
			}
		}

		//RENDER UI
		renderUI();

		break;

	case paused:
		player.reset();
		drawObj(player);
		drawObj(floor_carpet);
		//RENDER DEGLI OGGETTI
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i]);
		}

		//RENDER UI
		//renderUI();

		break;

	case dead:
		drawObj(player);
		drawObj(floor_carpet);
		//RENDER DEGLI OGGETTI
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i]);
		}
		break;
	}
}
