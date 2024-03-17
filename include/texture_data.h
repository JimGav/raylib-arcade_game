#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H

#include "raylib.h"

class TextureData
{
public:
	Texture2D texture;
	Rectangle render_frame;
	int animation_frames;
};

#endif