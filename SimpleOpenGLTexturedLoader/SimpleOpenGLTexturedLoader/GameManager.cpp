#pragma once
#include "lib.h"

#define pi 3.14159265359

state_type state = menu;
menu_state_type menu_state = empty;
level_type level = lvl1;

GameObj player;
GameObj floor_carpet;

int z_finish_lvl1 = -125;
float x_border_abs = 2.1f;

//velocità di spostamento player
float angles = 22.5f; //attorno a y, per click (a-d)
float speed = 0; //del player
float maxSpeed = 0.003f;
float minSpeed_factor = 3.f; //it is divided by maxSpeed
float deltaSpeed = 0.000025f;
float steering_speedFactor = 1.f;

bool isJumping = false;
float jump_time_start;
float jump_time = 500; //jumping time in ms

//boosts
int boosts = 0;

//obstacles init
float bumpyness = 1.2;
float collectable_speed = 0.005;
float deadly_speed = 0.01;

//cronometro di gioco
float chronometer = 0;
float chronometer_start = 1;

//variabile tempo
int prev_time = 0;
int fps;

//POSIZIONAMENTO OGGETTI (statica --> DA MODIFICARE)
int const obj_dim = 31;
GameObj obj[obj_dim];
int const bObj_dim = 4;
Button bObj[bObj_dim];
int const images_dim = 3;
Button images[images_dim];

void playerSetup() {
	speed = 0; //resetto velocità player
	chronometer = 0;
	boosts = 0; //resetto boost

		//reimposto collectable balls
	for (int i = 0; i < obj_dim; i++) {
		if (obj[i].tag == collectable) {
			obj[i].toRender = true;
		}
	}
}

void lvl2_setup() {
	for (int i = 0; i < obj_dim; i++) {
		obj[i].toRender = true;
	}

	playerSetup();
}

void lvl1_setup() {
	for (int i = (obj_dim-1)/2; i < obj_dim; i++) {
	//for (int i = 0; i < obj_dim; i++) {
		obj[i].toRender = false;
	}
	obj[obj_dim - 1].toRender = true;

	playerSetup();
}

void menu_setup() {
	for (int index = 0; index < bObj_dim; index++) {
		bObj[index].toRender = true;
	}
	for (int index = 0; index < images_dim; index++) {
		images[index].toRender = true;
	}
	images[1].toRender = false;
	images[2].toRender = false;
}

GameManager::GameManager() {
	state = menu;
	level = lvl1;

	player = GameObj(0.f, 0.f, 0.f, player_tag);
	player.reset(); //faccio reset = setup

	floor_carpet = GameObj(0.f, -5.5f, floor_tag); //da -5.5 a 119 z

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
	obj[22] = GameObj(1.f, -60.f, 0.f, collectable);
	obj[23] = GameObj(-1.f, -116.f, 0.f, deadly_obstacle);
	obj[24] = GameObj(0.f, -76.f, 0.f, stair);
	obj[25] = GameObj(-1.f, -20.f, 0.f, bumpy_obstacle);
	obj[26] = GameObj(0.f, -44.f, 0.f, bumpy_obstacle);
	obj[27] = GameObj(1.f, -64.f, 0.f, bumpy_obstacle);
	obj[28] = GameObj(-1.f, -80.f, 0.f, bumpy_obstacle);
	obj[29] = GameObj(1.f, -104.f, 0.f, bumpy_obstacle);

	//UI gameObj
	obj[30] = GameObj(-4.45f, -1.f, 0.f, collectable_ui);

	for (int i = 0; i < obj_dim; i++) {
		switch (obj[i].tag) {
		case stair:
			obj[i].dim_x = 5.f;
			obj[i].dim_z = 3.f;
			break;
		}
	}

	bObj[0] = Button(-4.f, 2.f, 1.5f, 0.8f, bPlay);
	bObj[1] = Button(-4.f, 1.f, 3.f, 0.8f, bTutorial);
	bObj[2] = Button(-4.f, 0.f, 3.f, 0.8f, bCredits);
	bObj[3] = Button(-4.f, -1.f, 1.5f, 0.8f, bExit);
	
	images[0] = Button(0.f, 0.f, 1.f, 1.f, image);
	images[1] = Button(2.f, 0.f, 1.f, 1.f, tutorial_image);
	images[2] = Button(2.f, 0.f, 1.f, 1.f, credits_image);

	images[1].toRender = false;
	images[2].toRender = false;

	playerSetup(); //vedi sopra
}

/*
0 -> Tricilo
1 -> Floor
2 -> Sofa
3 -> Chair
4 -> Ball
5 -> Stairs
6 -> Doll
7 -> Menu
8 -> TxtPlay
9 -> TxtTutorial
10 -> TxtCredits
11 -> TxtExit
12 -> ImgTutorial
13 -> ImgCredits
*/

//funzione di RENDER BUTTONS
void GameManager::drawButton(Button but){
	if (but.toRender) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			//glOrtho(-6, 6, -3.375f, 3.375f, 0, -100);
			gluOrtho2D(-6, 6, -3.375f, 3.375f);

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();

				switch (but.bType) {
				
				case image:
					//glTranslatef(but.x, but.z, 0.f); //object z become y of 2D
					glTranslatef(but.x, but.z, -0.1f);
					glRotatef(90.f, 0.f, 0.f, 1.f);
					RenderModelByIndex(7); 
					break;
				case tutorial_image:
					//glTranslatef(but.x, but.z, 0.f); //object z become y of 2D
					//glRotatef(90.f, 0.f, 0.f, 1.f);
					glTranslatef(but.x, but.z, 0.f);
					glRotatef(90.f, 0.f, 0.f, 1.f);
					RenderModelByIndex(12);
					break; 
				case credits_image:
					//glTranslatef(but.x, but.z, 0.f); //object z become y of 2D
					glTranslatef(but.x, but.z, 0.f);
					glRotatef(90.f, 0.f, 0.f, 1.f);
					RenderModelByIndex(13);
					break;
				case bPlay:
					//glTranslatef(but.x, but.z, 0.f); //object z become y of 2D
					glTranslatef(but.x, but.z, 0.f);
					RenderModelByIndex_button(8, but.isMouseOn);
					//RenderModelByIndex(8);
					break;
				case bTutorial:
					//glTranslatef(but.x, but.z, 0.f); //object z become y of 2D
					glTranslatef(but.x, but.z, 0.f);
					RenderModelByIndex_button(9, but.isMouseOn);
					//RenderModelByIndex(9);
					break;
				case bCredits:
					//glTranslatef(but.x, but.z, 0.f); //object z become y of 2D
					glTranslatef(but.x, but.z, 0.f);
					RenderModelByIndex_button(10, but.isMouseOn);
					//RenderModelByIndex(10);
					break;
				case bExit:
					//glTranslatef(but.x, but.z, 0.f); //object z become y of 2D
					glTranslatef(but.x, but.z, 0.f);
					RenderModelByIndex_button(11, but.isMouseOn);
					//RenderModelByIndex(11);
					break;
				}
			glPopMatrix();
		glPopMatrix();
	}
}

//funzione di RENDER OBJ
void GameManager::drawObj(GameObj obj, int i) {
	//SETUP PER PLAY
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//aspect ratio 1.5 tra bordi orizzontali e verticali (900x600)
	glOrtho(-5.f, 5.f, -3.3f, 3.3f, 0.f, 100.f); //SETUP PROIEZIONE

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
		gluLookAt(0.f, 5.f, 0.3f,
				0.f, 0.f, -2.f,
				0.f, 1.f, 0.f);
	if (obj.toRender) { //obj.toRender
		//render per ostacoli diversi

		if (obj.tag == player_tag) {
			glTranslatef(obj.x, 0.2f, 0.f);
			if (isJumping) {
				glTranslatef(0.f, 1.f, 0.f);
				glRotatef(30.f, 1.f, 0, 0);
			}
			glRotatef(-obj.angle, 0.f, 1.0f, 0.f);
			if (state == dead) glRotatef(60.f, 0.f, 0.f, 1.f);
			RenderModelByIndex_triciclo(0, (state_type)state, speed);
		}

		if (obj.tag == floor_tag) {
			glTranslatef(0.f, 0.f, obj.z - player.z);
			RenderModelByIndex(1);
		}

		if (obj.tag == collectable_ui){
			glTranslatef(obj.x, 1.f, obj.z);
			RenderModelByIndex(4);
		}

		if (obj.z - 3 < player.z && obj.z + 7 > player.z) {
			switch (obj.tag) {

			case stair:
				glTranslatef(obj.x, 0.f, obj.z - player.z);
				RenderModelByIndex(5);
				break;

			case deadly_obstacle:
				glTranslatef(obj.x, 0.f, obj.z - player.z);
				RenderModelByIndex(6);
				break;

			case bumpy_obstacle:
				glTranslatef(obj.x, 0.f, obj.z - player.z);
				if(i % 2 == 0)
					RenderModelByIndex(2);
				else
					RenderModelByIndex(3);
				break;

			case collectable:
				glTranslatef(obj.x, 0.f, obj.z - player.z);
				RenderModelByIndex(4);
				break;
			}
		}

	glPopMatrix();
	glPopMatrix();
	}
	return;
}

//gestione dell'IDLE
void GameManager::my_idle(int time) {
	
	float radians, xs, zs;

	//PLAY
	switch((int)state) {
	case play:
		//PLAYER MOVEMENT
		radians = player.angle * 2 * pi / 360;
		zs = -speed * cos(radians) * (time - prev_time) * steering_speedFactor;
		xs = speed * sin(radians) * (time - prev_time) * steering_speedFactor;
		player.moveOf(xs, zs); //muovo il player

		//SPEED CONTROL
		if (speed < maxSpeed) {
			speed = speed + deltaSpeed;
		}

		//COLLISION DETECTION
		for (int i = 0; i < obj_dim; i++) {
			if (obj[i].isColliding(player.x, player.z) && obj[i].toRender) { //controllo che avvenga collisione e che oggetto sia renderizzato a schermo
				//fprintf(stdout, "Collisione con OBJ n%d of type %d\n", (i + 1), obj[i].tag);

				//float xs, zs, radians;
				//BEHAVIOR di COLLISIONE con OBJ
				switch (obj[i].tag) {
				case bumpy_obstacle:
					/*radians = player.angle * 2 * pi / 360;
					zs = cos(radians) * bumpyness;
					xs = sin(radians) * bumpyness;
					player.moveOf(xs, zs);*/
					if (0 < speed) speed = -(maxSpeed + speed) / 5 * bumpyness;
					break;
				case deadly_obstacle:
					if (!isJumping) state = dead;
					break;
				case collectable:
					boosts++;
					obj[i].toRender = false;
					break;
				case stair:
					if (player.angle != 0) {
						if (abs(player.angle) < 45) {
							if (speed > maxSpeed / minSpeed_factor) speed = speed * (1 - deltaSpeed * 6000);
							else speed = maxSpeed / minSpeed_factor;
						}
						else state = dead;
					}
				}
			}
		}

		//CONTROLLO BORDER
		if (!(abs(player.x) < x_border_abs))
			state = dead;

		//CONTROLLO JUMP
		if (!isJumping) {
			jump_time_start = time;
		}
		else if (time - jump_time_start > jump_time) {
			isJumping = false;
		}

		//CONTROLLO FINE LVL
		if (player.z < z_finish_lvl1) {
			state = score;
		}

		//CONTROLLO CHRONOMETER
		chronometer = time - chronometer_start;

		//fps calculation
		fps = fps_calc(time, prev_time);

		//--- ANIMAZIONI DI SPOSTAMENTO ---
		for (int i = 0; i < obj_dim; i++) {
			if (obj[i].tag == collectable && (obj[i].z - 3 < player.z && obj[i].z + 7 > player.z)) {
				obj[i].moveOf(0, collectable_speed);
			}
			if (obj[i].tag == deadly_obstacle && (obj[i].z - 3 < player.z && obj[i].z + 7 > player.z)) {
				if (obj[i].x < -1.5 || obj[i].x > 1.5) {
					deadly_speed = -deadly_speed;
				}
				obj[i].moveOf(deadly_speed, 0);
			}
		}

		glutPostRedisplay();
		break;

	//PAUSE
	case paused:
		chronometer_start = time;

		break;
	}

	prev_time = time;
}

//gestione movimento del mouse
void GameManager::mouseMotion(int x, int y){
	float xf = (float)x;
	float yf = (float)y;
	get3Dpos(&xf, &yf);
	for (int i = 0; i < bObj_dim; i++) {
		if (bObj[i].isColliding(xf, yf)) {
			bObj[i].isMouseOn = true;
			printf("Mouse is on: button %d\n",i);
		}
		else bObj[i].isMouseOn = false;
		glutPostRedisplay();
	}
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
			playerSetup();
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
			//esc
		case 27:
			state = menu;
			menu_state = empty;
			menu_setup(); //NON FUNZIONA????
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
			playerSetup();
			glutPostRedisplay();
			break;
		}
		break;

		//stato MENU
	case menu:
		if (key == '*') {
			float xf = (float)x;
			float yf = (float)y;
			get3Dpos(&xf, &yf);
			//printf("Mouse clicked in (%f,%f)\n", (float) x * 12.f / 600.f - 6.f, (float)y * 6.750f / 900.f - 3.375f);
			//printf("Mouse clicked in (%d,%d)\n", x,y);
			printf("Mouse clicked in (%f,%f)\n", xf,yf);

			for (int i = 0; i < bObj_dim; i++) {
				//if(bObj[i].isColliding((float) x*12.f/600.f - 6.f, (float) y * 6.750f/900.f - 3.375f)){ //controllo posizione del mouse
				//if (bObj[i].isColliding(x,y)){
				if (bObj[i].isColliding(xf,yf)){

					//deactivate images (not background -> index 0)
					for (int index = 1; index < images_dim; index++) {
						images[index].toRender = false;
					}

					//controllo quale bottone è clicked
					switch ((int)bObj[i].bType) {
					case bPlay:
						printf("Play selected\n");
						for (int index = 1; index < bObj_dim; index++) {
							bObj[index].toRender = false;
						}
						state = paused;
						level = lvl1;
						playerSetup();
						lvl1_setup();
						glutPostRedisplay();
						break;
					case bTutorial:
						printf("Tutorial selected\n");
						images[1].toRender = true;
						menu_state = tutorial;
						glutPostRedisplay();
						break;
					case bCredits:
						printf("Credits selected\n");
						images[2].toRender = true;
						menu_state = credits;
						glutPostRedisplay();
						break;
					case bExit:
						printf("Exit selected\n");
						exit(0); //exits from the game
						break;
					}
				}
			}
		}
		break;

		//stato SCORE
	case score:
		switch (key) {
			//barra spaziatrice
		case 32:
			if (level == lvl1) {
				state = paused;
				level = lvl2;
				playerSetup();
				lvl2_setup(); //TO LEVEL 2
			}
			else {
				state = menu;
				menu_state = empty;
				menu_setup();
			}
			glutPostRedisplay();
			break;
		}
		break;
	}
}

//BEHAVIOR per ogni REDISPLAY
void GameManager::every_frame() {

	switch ((int)state) {
	
	//PLAY
	case play:
		//RENDER SCENA 3D
		drawObj(player, 0);
		drawObj(floor_carpet, 0);

		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i], i);
		}

		//UI render
		renderUI(speed/maxSpeed, chronometer / 1000, boosts);
		renderFps(fps);

		break;
	
	//PAUSED
	case paused:
		player.reset();
		drawObj(player, 0);
		drawObj(floor_carpet, 0);
		//RENDER DEGLI OGGETTI
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i], i);
		}

		//UI render
		renderUI(speed / maxSpeed, chronometer / 1000, boosts);
		renderPressToPlayText();

		break;
	
	//DEAD
	case dead:
		drawObj(player, 0);
		drawObj(floor_carpet, 0);
		//RENDER DEGLI OGGETTI
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i], i);
		}

		//UI render
		renderUI(speed / maxSpeed, chronometer / 1000, boosts);
		renderDeadText();

		break;
	
	//SCORE
	case score:
		drawObj(player, 0);
		drawObj(floor_carpet, 0);
		//RENDER DEGLI OGGETTI
		for (int i = 0; i < obj_dim; i++) {
			drawObj(obj[i], i);
		}

		renderUI(speed / maxSpeed, chronometer / 1000, boosts);
		if (level == lvl1)renderScoreText();
		else renderScore2Text();

		break;

	//MENU
	case menu:
		for (int i = 0; i < images_dim; i++) {
			drawButton(images[i]);
		}
		for (int i = 0; i < bObj_dim; i++) {
			drawButton(bObj[i]);
		}

		break;
	}
}
