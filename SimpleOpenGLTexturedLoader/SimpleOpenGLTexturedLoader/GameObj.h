#pragma once

enum type { player_tag, floor_tag, stair, deadly_obstacle, bumpy_obstacle, collectable, collectable_ui, button };

class GameObj
{
public:
	float x, z, angle, dim_x, dim_z;
	bool toRender;
	type tag;

	GameObj();
	GameObj(float pos_x, float pos_z, type tag);
	GameObj(float pos_x, float pos_z, float r_angle, type tag);
	GameObj(float pos_x, float pos_z, float r_angle, float dim_x, float dim_z, type tag);

	void reset();
	bool isColliding(float pos_x, float pos_z);
	void moveOf(float xs, float zs);
};

