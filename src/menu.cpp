#include <new>
#include "menu.h"
#include "game_data.h"
#include "character.h"

// Constructor
Menu::Menu(int font_size) : font_size(font_size){};

// Draw
void Menu::draw()
{
	DrawText("GAME OVER", (GetScreenWidth() - MeasureText("GAME OVER", font_size)) / 2, GetScreenHeight() / 2 - 50, font_size, RED);
	DrawText("PLAY AGAIN", (GetScreenWidth() - MeasureText("PLAY AGAIN", font_size)) / 2, GetScreenHeight() / 2, font_size, WHITE);
	
}

// Handle Input
void Menu::handle_input()
{
	
	if (CheckCollisionPointRec(GetMousePosition(), {(float)(GetScreenWidth() - MeasureText("PLAY AGAIN", font_size)) / 2, (float)GetScreenHeight() / 2,
																									(float)MeasureText("PLAY AGAIN", font_size), 20}))
		SetMouseCursor(4); // Cursors pointer
	else
		SetMouseCursor(1);
}