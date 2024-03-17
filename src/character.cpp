#include "character.h"
#include <list>
#include "game_data.h"

// Constructor
Character::Character()
{
	load_textures();
	pos = {((float)GetScreenWidth() - frame_width)/ 2 , (float)GetScreenHeight() / 2};
	vel = {0, 0};
	attacking = false;
	facingRight = true;
	jump_height = 7;
	attack_counter = 0;
	run_speed = 10;
	fall_speed = 10;
	jump_speed = 10;
	jump_counter = 0; // Count how many frames the character has been jumping for
	attack_range = 40;
	frame_counter = 0;
	hp = 100;
};

bool Character::isRunning() { return vel.x != 0; }
bool Character::isJumping() { return vel.y < 0; }
bool Character::isFalling() { return vel.y > 0; }
bool Character::isAlive() { return hp > 0;};
bool Character::in_attack_range(Skeleton *s) { return abs(getRealPos().x - s->getRealPos().x) < attack_range; };
Vector2 Character::getRealPos() { return {pos.x + frame_width / 2, pos.y + frame_height / 2}; }

//////////////////////////////////////////// HANDLE INPUT /////////////////////////////////////////
void Character::handle_input()
{
	// Run
	vel.x = IsKeyDown(KEY_D) ? run_speed : IsKeyDown(KEY_A) ? -run_speed
																													: 0;
	// Attack
	attacking = (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || attack_counter > 0) && !isRunning();

	// Jump
	if (IsKeyPressed(KEY_SPACE) && !isFalling())
		vel.y = -jump_speed;
};
///////////////////////////////////////////////////////////////////////////////////////////////////

void Character::update_state()
{
	// Handle fall
	if (getRealPos().y < game_data::groundY && !isJumping())
		vel.y = fall_speed;
	else if (!isJumping())
		vel.y = 0;

	spawn_skeletons();

	if (isRunning())
	{
		pos.x += vel.x;
		facingRight = vel.x >= 0;
		update_render_frame(run.render_frame, run.animation_frames);
	}
	else
		update_render_frame(idle.render_frame, idle.animation_frames);


	if (attacking)
	{
		if (attack_counter++ == atck.animation_frames)
			attack_counter = 0;
		for (auto &s : skeletons)
			if (in_attack_range(s))
				s->dying = true;
		update_render_frame(atck.render_frame, atck.animation_frames);
	}

	if (isFalling())
	{
		pos.y += vel.y;
		update_render_frame(j_down.render_frame, j_down.animation_frames);
	}
	else if (isJumping())
	{
		pos.y += vel.y;
		if (jump_counter++ == jump_height)
		{
			jump_counter = 0;
			vel.y = 10;
		}
		update_render_frame(j_up.render_frame, j_up.animation_frames);
	}

	remove_dead_skeletons();
	handle_screen_escape();
}

/////////////////////////////////////////////// HANDLE GRAPHICS ////////////////////////////////////////////

void Character::load_textures()
{
	// Load Textures
	atck.texture = LoadTexture("assets/atck.png");
	atck.animation_frames = 8;
	idle.texture = LoadTexture("assets/idle.png");
	idle.animation_frames = 8;
	run.texture = LoadTexture("assets/run.png");
	run.animation_frames = 8;
	j_up.texture = LoadTexture("assets/j_up.png");
	j_up.animation_frames = 3;
	j_down.texture = LoadTexture("assets/j_down.png");
	j_down.animation_frames = 3;

	frame_width = atck.texture.width / atck.animation_frames;
	frame_height = idle.texture.height;

	// Initialize render frames
	atck.render_frame = {0, 0, frame_width, frame_height};
	idle.render_frame = {0, 0, frame_width, frame_height};
	run.render_frame = {0, 0, frame_width, frame_height};
	j_up.render_frame = {0, 0, frame_width, frame_height};
	j_down.render_frame = {0, 0, frame_width, frame_height};
}

void Character::update_render_frame(Rectangle &render_frame, int animation_frames)
{
	render_frame.x += frame_width;
	if (render_frame.x > frame_width * animation_frames)
		render_frame.x = 0;
	render_frame.width = facingRight ? frame_width : -frame_width;
}

void Character::draw()
{
	if (isJumping())
		DrawTextureRec(j_up.texture, j_up.render_frame, pos, WHITE);
	else if (isFalling())
		DrawTextureRec(j_down.texture, j_down.render_frame, pos, WHITE);
	else if (isRunning())
		DrawTextureRec(run.texture, run.render_frame, pos, WHITE);
	else if (attacking)
		DrawTextureRec(atck.texture, atck.render_frame, pos, WHITE);
	else
		DrawTextureRec(idle.texture, idle.render_frame, pos, WHITE);
	
	DrawRectangle(getRealPos().x - hp/4, getRealPos().y + 10, hp/2, 3, GREEN);
	// DrawRectangle(getRealPos().x, getRealPos().y, 1, 1, YELLOW);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Spawn skeletons
void Character::spawn_skeletons()
{
	if (frame_counter++ % 50 == 0)
	{
		Skeleton *s = new Skeleton;
		skeletons.push_back(s);
	}
}

// Remove dead skeletons
void Character::remove_dead_skeletons()
{
	for (auto &s : skeletons)
		if (s->dying_counter > 11)
		{
			skeletons.remove(s);
			break; // Break to not remove two skeletons at the same frame. Removing this will break the program (cause of list)
		}
}

void Character::handle_screen_escape()
{
	// Reposition on screen escape
	if (getRealPos().x >= GetScreenWidth())
		pos.x -= vel.x;
	if (getRealPos().x < 0)
		pos.x -= vel.x;
}
