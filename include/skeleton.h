#ifndef SKELETON_H
#define SKELETON_H

#include "raylib.h"
#include "texture_data.h"
class Character;

class Skeleton
{
public:
	Vector2 pos, vel;
	bool attacking, facingRight, dying;
	float walk_speed,frame_width,frame_height, attack_range;
	int dying_counter = 0;
	int attack_counter = 0;

	TextureData atck, idle, walk, death;
	
	// Constructor
	Skeleton();

	bool isWalking(),onGround();
	void draw(), update_state(Character &character);
	void load_textures();
	Vector2 getRealPos();
	void update_render_frame(Rectangle &render_frame, int animation_frames);
	bool in_attack_range(int targetX);
};

#endif