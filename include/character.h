#ifndef CHARACTER_H
#define CHARACTER_H

#include <list>
#include "raylib.h"
#include "math.h"
#include "texture_data.h"
#include "skeleton.h"

class Character
{
public:
	Vector2 pos, vel;
	bool attacking, facingRight;
	float jump_height, run_speed, fall_speed, jump_speed, frame_width, frame_height, attack_range;
	int jump_counter, attack_counter;
	int frame_counter; 
	int hp;
	std::list<Skeleton*> skeletons;

	TextureData atck, idle, run, j_up, j_down;

	// Constructor
	Character();

	bool isRunning(), isFalling(), isJumping(), isAlive(), in_attack_range(Skeleton* en);
	void handle_input(), update_state();
	void load_textures(),draw(),  update_render_frame(Rectangle &render_frame, int animation_frames);
	void remove_dead_skeletons(),spawn_skeletons(), handle_screen_escape();
	Vector2 getRealPos();
};

#endif