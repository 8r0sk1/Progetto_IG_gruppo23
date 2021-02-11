#pragma once
#include "GameObj.h"

enum obstacle_type {deadly,bumpy};

class Obstacle :
    public GameObj
{
public: 
    Obstacle(obstacle_type);
	Obstacle(float pos_x, float pos_z, obstacle_type);
	Obstacle(float pos_x, float pos_z, float r_angle, obstacle_type);
	Obstacle(float pos_x, float pos_z, float r_angle, float dim_x, float dim_z, obstacle_type);
};

