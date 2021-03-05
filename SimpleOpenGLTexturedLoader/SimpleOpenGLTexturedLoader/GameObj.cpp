#pragma once
#include "GameObj.h"
#include <math.h>


	float dim_def = 0.75;

	float x, z; //posizione (x,z)
	float angle; //angolo di rotazione attorno ad y
	float dim_x, dim_z; //dimensioni dell'oggetto
	bool toRender = true; //flag di render

	type tag; //è obstacle di default

	GameObj::GameObj() {
		x = 0;
		z = 0;
		angle = 0;
		dim_x = dim_def;
		dim_z = dim_def;
		tag = bumpy_obstacle;
		toRender = true;
	};

	GameObj::GameObj(float pos_x, float pos_z, type obj_tag) {
		x = pos_x;
		z = pos_z;
		angle = 0;
		dim_x = dim_def;
		dim_z = dim_def;
		tag = obj_tag;
		toRender = true;
	}

	GameObj::GameObj(float pos_x, float pos_z, float r_angle, type obj_tag) {
		x = pos_x;
		z = pos_z;
		angle = r_angle;
		dim_x = dim_def;
		dim_z = dim_def;
		tag = obj_tag;
		toRender = true;
	}

	GameObj::GameObj(float pos_x, float pos_z, float r_angle, float l_x, float l_z, type obj_tag) {
		x = pos_x;
		z = pos_z;
		angle = r_angle;
		dim_x = l_x;
		dim_z = l_z;
		tag = obj_tag;
		toRender = true;
	}

	void GameObj::reset() {
		if (tag == player_tag) {
			x = 0;
			z = 4.f; //decentro player rispetto alla camera
			angle = 0;
		}
	};

	bool GameObj::isColliding(float pos_x, float pos_z) { //controlla se un punto (x,z) si trova nell'area di collisione dell'oggetto
		float dx = pos_x - x;
		float dz = pos_z - z;
		//fprintf(stdout, "dx=%f dz=%f\n", dx, dz);
		if (fabsf(dx) < dim_x/2 && fabsf(dz) < dim_z/2) {
			return true;
		}
		else return false;
	}

	void GameObj::moveOf(float xs, float zs) {
		x += xs;
		z += zs;
	}
