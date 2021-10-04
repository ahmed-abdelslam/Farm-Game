#include "Obstacle.h"
#include "Wagon.h"
#include "TextureManager.h"

//to share these variables
bool Obstacle::collision_obs[6];
bool Obstacle::noCollision = true;
int Obstacle::numberOfObstacle = 4;
SDL_Rect Obstacle::obstacle[6];
SDL_Rect Obstacle::destRect[6];


Obstacle::Obstacle(const char* texture) {
	//create the texture
	objTexture = TextureManager::LoadTexture(texture);
	
	//for loop to set the x, y, width and height of the 6 obstacles
	for (int n = 0; n < 6; n++) {
		obstacle[n].x = 0;
		obstacle[n].y = 0;
		obstacle[n].w = width;
		obstacle[n].h = height;
	}

	//destination rectangle of obstacle 1 with changing the value of y axis 
	destRect[0].x = x;
	destRect[0].y = 18;
	destRect[0].w = width;
	destRect[0].h = height;

	//destination rectangle of obstacle 2 with changing the value of y axis 
	destRect[1].x = x;
	destRect[1].y = 183;
	destRect[1].w = width;
	destRect[1].h = height;

	//destination rectangle of obstacle 3 with changing the value of y axis 
	destRect[2].x = x;
	destRect[2].y = 348;
	destRect[2].w = width;
	destRect[2].h = height;

	//destination rectangle of obstacle 4 with changing the value of y axis 
	destRect[3].x = x;
	destRect[3].y = 525;
	destRect[3].w = width;
	destRect[3].h = height;

	//destination rectangle of obstacle 5 with changing the value of y axis 
	destRect[4].x = x;
	destRect[4].y = 450;
	destRect[4].w = width;
	destRect[4].h = height;

	//destination rectangle of obstacle 6 with changing the value of y axis 
	destRect[5].x = x;
	destRect[5].y = 100;
	destRect[5].w = width;
	destRect[5].h = height;
}

Obstacle::~Obstacle() {}

//this function checks if the sides of the rectangles of the head and the obstacles are colliding with each other or not
//we need a parameter called a number which specifies the number of the obstacle
void Obstacle::checkCollisionTheHeadWithObstacle(SDL_Rect a, SDL_Rect b, int number)
{
	//The sides of the two rectangles (head and obstacle)
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
		collision_obs[number] = false;
	
	else if (topA >= bottomB) 
		collision_obs[number] = false;

	else if (rightA <= leftB) 
		collision_obs[number] = false;
	
	else if (leftA >= rightB) 
		collision_obs[number] = false;
	
	//If none of the sides from A are outside B
	//which means there is a collision
	else {
		/*The reason that I added this if statement is to avoid the recursion loop 
		Of the function of showing loss notification Even when the user presses key R to restart 
		it is still showing the loss notification So after setting collision_obs[number] to true 
		set noCollision to false To stop assigning true to collision_obs[number] over and over again*/
		if (noCollision) {
			collision_obs[number] = true;
			noCollision = false;
		}
	}
}


void Obstacle::Render() {
	//a for loop to render the obstacles based on the number of the obstacles
	//at the same time we check every time if there is a collision between the head and one of the obstacles
	for (int n = 0; n < numberOfObstacle; n++) {
		SDL_RenderCopy(trainingGame::renderer, objTexture, &obstacle[n], &destRect[n]);
		checkCollisionTheHeadWithObstacle(Wagon::rectOfHead[1], destRect[n], n);
	}
}