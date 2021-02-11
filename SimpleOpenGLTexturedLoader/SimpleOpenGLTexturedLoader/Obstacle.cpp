#include "Obstacle.h"

obstacle_type ob_type;

Obstacle::Obstacle(obstacle_type inserted_type) {
	ob_type = inserted_type;
	tag = bumpy_obstacle;
}

Obstacle::Obstacle(float pos_x, float pos_z, obstacle_type) {
	GameObj(pos_x, pos_z, bumpy_obstacle);
}

Obstacle::Obstacle(float pos_x, float pos_z, float r_angle, obstacle_type) {
	GameObj(pos_x, pos_z,r_angle, bumpy_obstacle);
}

Obstacle::Obstacle(float pos_x, float pos_z, float r_angle, float dim_x, float dim_z, obstacle_type) {
	GameObj(pos_x, pos_z, r_angle, dim_x, dim_z, bumpy_obstacle);
}