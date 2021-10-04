#pragma once
#include "trainingGame.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture *LoadTexture(const char* texture);
	
	static SDL_Texture *TextTexture(int points, int maxPoints, int length, int min, int sec, int stage, int width, int height);
	
	static std::string IntToString(int n);
	
private:
	
};