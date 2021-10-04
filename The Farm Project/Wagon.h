#pragma once
#include "trainingGame.h"
class Wagon {

public:
	Wagon(const char* texture, int x, int y);
	~Wagon();

	void Default();
	void movingUp();
	void movingDown();
	void movingRight();
	void movingLeft();
	void Render();
	void checkCollisionTheHeadWithCart(SDL_Rect a, SDL_Rect b, int number);
	bool static collision_cart[100];
	void reset();

	SDL_RendererFlip flip;
	SDL_Point center;

	int degree = 0;
	int infoPostiotion[6];
	int* trackPostiotion();
	int static xpos;
	int static ypos;
	

	SDL_Rect static rectOfHead[2];

private:

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Rect  rectOfFarmer;

};