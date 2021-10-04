#pragma once
#include "trainingGame.h"

class Obstacle {
public:
	Obstacle(const char* texture);
	~Obstacle();

	void Render();
	void checkCollisionTheHeadWithObstacle(SDL_Rect a, SDL_Rect b, int number);

	bool static collision_obs[6];
	bool static noCollision;

	int static numberOfObstacle;

	static SDL_Rect obstacle[6], destRect[6];

private:
	int x = 365, width = 25, height = 115;

	SDL_Texture* objTexture;
	

};