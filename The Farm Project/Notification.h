#pragma once
#include "trainingGame.h"

class Notification {
public:

	Notification(const char* texture, int x, int y);
	~Notification();

	void Render();

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};