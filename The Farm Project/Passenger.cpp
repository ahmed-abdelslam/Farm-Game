#include "Passenger.h"
#include "TextureManager.h"
#include "Wagon.h"

//to share this variable
bool Passenger::collision_farmer;

Passenger::Passenger(const char* texture, int x, int y) {
	//create a texture
	objTexture = TextureManager::LoadTexture(texture);

	//position of the passenger (farmer or farmer with a crop) x-axis and y-axis
	xpos = x;
	ypos = y;

}

Passenger::~Passenger()
{
}

// default position of the passenger (farmer or farmer with a crop)
void Passenger::Default() {

	//set the height and width, x-axis and y-axis of the rectangle
	//this rectangle specifies the size of the passenger (farmer or farmer with a crop)
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	//set the height and width same as srcRect, and change the x-axis and y-axis same as xpos and ypos of the 
	//the passenger (farmer or farmer with a crop)
	//this rectangle called the destination rectangle and the SDL use it to send it to the render
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	//don't flip
	flip = SDL_FLIP_NONE;


	//this is a transparent rectangle of the farmer used to check the collision with the head
	rectOfFarmer.x = xpos + 5;
	rectOfFarmer.y = ypos + 5;
	rectOfFarmer.h = 26;
	rectOfFarmer.w = 26;

}


//this function checks if the sides of the rectangles of the head or the farmer are colliding with each other or not
void Passenger::checkCollisionTheHeadWithFarmer(SDL_Rect a, SDL_Rect b)
{
	//The sides of the two rectangles (head and farmer)
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	//which means there is no collision
	if (bottomA <= topB)
		collision_farmer = false;
	else if (topA >= bottomB)
		collision_farmer = false;
	else if (rightA <= leftB)
		collision_farmer = false;
	else if (leftA >= rightB)
		collision_farmer = false;
	else {

		//If none of the sides from A are outside B
		//which means there is a collision
		collision_farmer = true;
	}
}

//this function is responsible for changing the location of the passenger (farmer or farmer with a crop) 
void Passenger::changeLocation(int newPosX, int newPosY) {

	//change the x-axis of the farmer
	xpos = newPosX;

	//change the y-axis of the farmer
	ypos = newPosY;


	//this is a transparent rectangle of the farmer used to check the collision with the head
	rectOfFarmer.x = xpos;
	rectOfFarmer.y = ypos;
	rectOfFarmer.h = 30;
	rectOfFarmer.w = 30;

}

void Passenger::Render() {
	//rendering the passenger (farmer or farmer with a crop)
	SDL_RenderCopyEx(trainingGame::renderer, objTexture, &srcRect, &destRect, degree, &center, flip);
	
	//call this function to check every time if the head collided with the any type of farmer
	checkCollisionTheHeadWithFarmer(Wagon::rectOfHead[1], rectOfFarmer);
}