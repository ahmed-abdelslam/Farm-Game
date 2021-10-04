#include "trainingGame.h"
class Passenger {

public:
	Passenger(const char* texture, int x, int y);
	~Passenger();

	void Default();
	void Render();
	void changeLocation(int newPosX, int newPosY);
	void checkCollisionTheHeadWithFarmer(SDL_Rect a, SDL_Rect b);

	bool static collision_farmer;

	SDL_RendererFlip flip;
	SDL_Point center;

	int degree = 0;
	

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Rect rectOfFarmer;

};

