#include "skeleton.h"
#include "math.h"
#include "game_data.h"
#include "character.h"

// Constructor
Skeleton::Skeleton()
{
	if (GetRandomValue(-1, 1) > 0)
		pos = {(float)GetScreenWidth(), 580 + frame_height + 15};
	else
		pos = {0, 580 + frame_height + 15};
	load_textures();

	vel = {0, 0};
	attacking = false;
	facingRight = true;
	walk_speed = 10;
	attack_range = 30;
	dying = false;
	dying_counter = 0;
};

bool Skeleton::isWalking() { return vel.x != 0; };
bool Skeleton::onGround() { return getRealPos().y >= game_data::groundY; };
bool Skeleton::in_attack_range(int targetX) { return abs(getRealPos().x - targetX) < attack_range; };
Vector2 Skeleton::getRealPos() { return {pos.x + frame_width / 2, pos.y + frame_height / 2}; }

void Skeleton::update_state(Character& character)
{
	vel.x = character.getRealPos().x >= getRealPos().x ? 1 : -1;
	facingRight = character.getRealPos().x >= getRealPos().x;

	// Gravity
	if (!onGround())
		pos.y += game_data::gravity;

	if (dying)
	{
		dying_counter++;
		vel.x = 0;
		update_render_frame(death.render_frame, death.animation_frames);
	}
	if (in_attack_range(character.getRealPos().x))
	{
		if (attack_counter++ % 5 == 0)
			character.hp-=10;
	
		vel.x = 0;
		update_render_frame(atck.render_frame, atck.animation_frames);
	}
	else if (isWalking())
	{
		pos.x += vel.x;
		update_render_frame(walk.render_frame, walk.animation_frames);
	}
}

/////////////////////////////////////////////// HANDLE GRAPHICS ////////////////////////////////////////////
void Skeleton::load_textures()
{
	// Load Textures
	Texture2D skeleton_texture = LoadTexture("assets/skeleton.png");
	atck.texture = skeleton_texture;
	atck.animation_frames = 13;
	idle.texture = skeleton_texture;
	idle.animation_frames = 4;
	walk.texture = skeleton_texture;
	walk.animation_frames = 11;
	death.texture = skeleton_texture;
	death.animation_frames = 13;

	// Initialize render frames
	frame_height = skeleton_texture.height / 5;
	frame_width = skeleton_texture.width / 13;

	atck.render_frame = {0, 0, frame_width, frame_height};
	death.render_frame = {0, 1 * frame_height, frame_width, frame_height};
	walk.render_frame = {0, 2 * frame_height, frame_width, frame_height};
	idle.render_frame = {0, 3 * frame_height, frame_width, frame_height};
}
void Skeleton::update_render_frame(Rectangle &render_frame, int animation_frames)
{
	render_frame.x += frame_width;
	if (render_frame.x > frame_width * animation_frames)
		render_frame.x = 0;
	render_frame.width = facingRight ? frame_width : -frame_width;
}

void Skeleton::draw()
{
	if (dying)
		DrawTextureRec(death.texture, death.render_frame, pos, WHITE);
	else if (isWalking())
		DrawTextureRec(walk.texture, walk.render_frame, pos, WHITE);
	else if (atck.render_frame.x > 0)
		DrawTextureRec(atck.texture, atck.render_frame, pos, WHITE);
	else
		DrawTextureRec(idle.texture, idle.render_frame, pos, WHITE);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
