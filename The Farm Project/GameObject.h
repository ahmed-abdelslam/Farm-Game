#pragma once
#include "trainingGame.h"
class GameObject {

public:
	GameObject(const char* texture, int x, int y, int size);
	~GameObject();

	void Update();
	void UpdateU(int pre);
	void UpdateS(int pre);
	void UpdateD(int pre);
	void UpdateA(int pre);
	void Render();
	void randPositionFarmerInfo(int x, int y);
	SDL_RendererFlip flip;
	SDL_Point center;
	int degree = 0;
	int requestForUpdate;

private:

	int xpos;
	int ypos;
	int xposOfFarmer, yposOfFarmer;
	int imageSize;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};