#include "GameObj.h"

	float x = 0.f, z= 0.f; //posizione (x,z)
	float angle = 0.f; //angolo di rotazione attorno ad y
	float dim_x = 0.f, dim_z = 0.f; //dimensioni dell'oggetto

	GameObj::GameObj(float pos_x, float pos_z) {
		x = pos_x;
		z = pos_z;
	}

	GameObj::GameObj(float pos_x, float pos_z, float r_angle) {
		x = pos_x;
		z = pos_z;
		angle = r_angle;
	}

	GameObj::GameObj(float pos_x, float pos_z, float r_angle, float l_x, float l_z) {
		x = pos_x;
		z = pos_z;
		angle = r_angle;
		dim_x = l_x;
		dim_z = l_z;
	}

	bool GameObj::isColliding(float pos_x, float pos_z) { //controllo collisione, riceve in ingresso la posizione del player
		float dx = pos_x - x;
		float dz = pos_z - z;
		fprintf(stdout, "dx=%f dz=%f\n", dx, dz);
		if (fabsf(dx) < dim_x/2 && fabsf(dz) < dim_z/2) {
			return true;
		}
		else return false;
	}

	int GameObj::trial() {
		return 1;
	}
