#include <iostream>
#include <new>
#include "raylib.h"
#include "character.h"
#include "skeleton.h"
#include "game_data.h"
#include "menu.h"

int main()
{
	InitWindow(800, 800, "Title");
	SetTargetFPS(30);

	// Initialize
	Character character;
	Texture2D bg = LoadTexture("assets/bg.PNG");
	Menu menu;

	// Mainloop
	while (!WindowShouldClose())
	{
		/////////////////////////////////////////////////// UPDATE STATE ////////////////////////////////////////////////////////
		if (character.isAlive())	
		{ // Handle input
			character.handle_input();
			// Update state
			character.update_state();
			for (auto &s : character.skeletons)
				s->update_state(character);
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
		/////////////////////////////////////////////////// DRAW ASSETS ////////////////////////////////////////////////////////
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(10, 10);

		// Draw static assets
		DrawTextureRec(bg, {0, 90, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, WHITE);

		// Draw dynamic assets
		character.draw();
		for (auto &s : character.skeletons)
			s->draw();

		if (!character.isAlive())
		{
			menu.draw();
			menu.handle_input();

			Rectangle bounds = {(float)(GetScreenWidth() - MeasureText("PLAY AGAIN", menu.font_size)) / 2, (float)GetScreenHeight() / 2 ,
													(float)MeasureText("PLAY AGAIN", menu.font_size), menu.font_size};
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), bounds))
				new (&character) Character;
		}
		EndDrawing();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	CloseWindow();
}
