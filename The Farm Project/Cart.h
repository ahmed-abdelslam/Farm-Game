#pragma once
#include "trainingGame.h"

class Cart {

public:
	Cart(const char* texture, int x, int y);
	~Cart();

	void Render();
	void setRect(int cartNO);
	void simulator(int tailNO);

	int degree = 0;
	int n = 0;
	int static startPosOfCartNO[100];

	SDL_RendererFlip flip;
	SDL_Point center;
	SDL_Rect static rectOfCart[100];

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	
};