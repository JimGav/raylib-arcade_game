#ifndef MENU_H
#define MENU_H

#include "raylib.h"

class Menu
{
public:
	float font_size;

	// Constructor
	Menu(int font_size = 30);

	// Draw
	void draw();
	// Handle Input
	void handle_input();

};

#endif