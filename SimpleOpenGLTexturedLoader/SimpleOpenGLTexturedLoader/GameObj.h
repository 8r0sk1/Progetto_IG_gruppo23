#pragma once
#include <math.h>
#include <stdio.h>

class GameObj
{
public:
	float x, z, angle, dim_x, dim_z;

	GameObj() {}
	GameObj(float pos_x, float pos_z);
	GameObj(float pos_x, float pos_z, float r_angle);
	GameObj(float pos_x, float pos_z, float r_angle, float dim_x, float dim_z);

	bool isColliding(float pos_x, float pos_z);

	int trial();
};

