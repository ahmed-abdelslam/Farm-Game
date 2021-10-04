#include "Wagon.h"
#include "TextureManager.h"
#include "Cart.h"
#include "trainingCourse.h"
#include "Stages.h"
#include "Obstacle.h"

//to share these variables
bool Wagon::collision_cart[100];
int Wagon::xpos;
int Wagon::ypos;
SDL_Rect Wagon::rectOfHead[2];

Wagon::Wagon(const char* texture, int x, int y) {
	//create a texture
	objTexture = TextureManager::LoadTexture(texture);

	// position of the head x-axis and y-axis
	xpos = x;
	ypos = y;
}

Wagon::~Wagon()
{
}

// default position of the head 
void Wagon::Default() {
	
	//set the height and width, x-axis and y-axis of the rectangle
	//this rectangle specifies the size of the head 
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	//set the height and width same as srcRect, and change the x-axis and y-axis same as xpos and ypos of the head
	//this rectangle called the destination rectangle and the SDL use it to send it to the render
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	//this is a transparent rectangle used to check the collisions later
	rectOfHead[0].x = xpos + 10;
	rectOfHead[0].y = ypos + 10;
	rectOfHead[0].w = 13;
	rectOfHead[0].h = 13;

	rectOfHead[1].x = xpos;
	rectOfHead[1].y = ypos;
	rectOfHead[1].w = 32;
	rectOfHead[1].h = 32;
	
}

// moving up the head
void Wagon::movingUp() {

	//decreasing the y-axis to move the head to the north
	ypos--;

	//set the height and width, x-axis and y-axis of the rectangle
	//this rectangle specifies the size of the head 
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	//set the height and width same as srcRect, and change the x-axis and y-axis same as xpos and ypos of the head
	//this rectangle called the destination rectangle and the SDL use it to send it to the render
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	//setting the center point of the head
	center.x = srcRect.w / 2;
	center.y = srcRect.h / 2;

	//rotating and flipping the head to be directed to the north
	degree = -90;
	flip = SDL_FLIP_VERTICAL;

	//this is a transparent rectangle used to check the collisions later
	//change the position of this recatngle to be as the position of the head
	rectOfHead[0].x = xpos + 10;
	rectOfHead[0].y = ypos + 10;
	rectOfHead[0].w = 13;
	rectOfHead[0].h = 13;

	rectOfHead[1].x = xpos;
	rectOfHead[1].y = ypos;
	rectOfHead[1].w = 32;
	rectOfHead[1].h = 32;

	// to reenter form south and inform the trainingGame to decrease the points
	if (ypos == 0) {
		ypos = 640;

		//decrease the points by one 
		trainingCourse::points -= 1;

		//update the information on the screen
		trainingCourse::textTexture = TextureManager::TextTexture(trainingCourse::points, trainingCourse::maxPoints, trainingCourse::length, trainingCourse::min, trainingCourse::sec, trainingCourse::stage, 800, 20);
	}
}

// moving down the head
void Wagon::movingDown() {
	
	//increasing the y-axis to move the head to the south
	ypos++;

	//set the height and width, x-axis and y-axis of the rectangle
	//this rectangle specifies the size of the head 
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	//set the height and width same as srcRect, and change the x-axis and y-axis same as xpos and ypos of the head
	//this rectangle called the destination rectangle and the SDL use it to send it to the render
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	//setting the center point of the head
	center.x = srcRect.w / 2;
	center.y = srcRect.h / 2;

	//rotating and flipping the head to be directed to the south
	degree = 90;
	flip = SDL_FLIP_VERTICAL;
	
	//this is a transparent rectangle used to check the collisions later
	//change the position of this recatngle to be as the position of the head
	rectOfHead[0].x = xpos + 10;
	rectOfHead[0].y = ypos + 10;
	rectOfHead[0].w = 13;
	rectOfHead[0].h = 13;

	rectOfHead[1].x = xpos;
	rectOfHead[1].y = ypos;
	rectOfHead[1].w = 32;
	rectOfHead[1].h = 32;

	// to reenter form north and inform the trainingGame to decrease the points
	if (ypos == 640) {
		ypos = 0;
		
		//decrease the points by one 
		trainingCourse::points -= 1;

		//update the information on the screen
		trainingCourse::textTexture = TextureManager::TextTexture(trainingCourse::points, trainingCourse::maxPoints, trainingCourse::length, trainingCourse::min, trainingCourse::sec, trainingCourse::stage, 800, 20);
	}
}

// moving right the head
void Wagon::movingRight() {
	//increasing the x-axis to move the head to the east
	xpos++;

	//set the height and width, x-axis and y-axis of the rectangle
	//this rectangle specifies the size of the head 
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	//set the height and width same as srcRect, and change the x-axis and y-axis same as xpos and ypos of the head
	//this rectangle called the destination rectangle and the SDL use it to send it to the render
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	//setting the center point of the head
	center.x = srcRect.w / 2;
	center.y = srcRect.h / 2;

	//rotating the head to be directed to the east
	degree = 0;
	
	//this is a transparent rectangle used to check the collisions later
	//change the position of this recatngle to be as the position of the head
	rectOfHead[0].x = xpos + 10;
	rectOfHead[0].y = ypos + 10;
	rectOfHead[0].w = 13;
	rectOfHead[0].h = 13;

	rectOfHead[1].x = xpos;
	rectOfHead[1].y = ypos;
	rectOfHead[1].w = 32;
	rectOfHead[1].h = 32;

	// to reenter form west and inform the trainingGame to decrease the points
	if (xpos == 800) {
		xpos = 0;
		
		//decrease the points by one 
		trainingCourse::points -= 1;

		//update the information on the screen
		trainingCourse::textTexture = TextureManager::TextTexture(trainingCourse::points, trainingCourse::maxPoints, trainingCourse::length, trainingCourse::min, trainingCourse::sec, trainingCourse::stage, 800, 20);
	}
}

// moving left the head
void Wagon::movingLeft() {
	//decreasing the x-axis to move the head to the west
	xpos--;
	
	//set the height and width, x-axis and y-axis of the rectangle
	//this rectangle specifies the size of the head
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	//set the height and width same as srcRect, and change the x-axis and y-axis same as xpos and ypos of the head
	//this rectangle called the destination rectangle and the SDL use it to send it to the render
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	//setting the center point of the head
	center.x = srcRect.w / 2;
	center.y = srcRect.h / 2;

	//rotating and flipping the head to be directed to the west
	degree = 0;
	flip = SDL_FLIP_HORIZONTAL;
	
	//this is a transparent rectangle used to check the collisions later
	//change the position of this recatngle to be as the position of the head
	rectOfHead[0].x = xpos + 10;
	rectOfHead[0].y = ypos + 10;
	rectOfHead[0].w = 13;
	rectOfHead[0].h = 13;

	rectOfHead[1].x = xpos;
	rectOfHead[1].y = ypos;
	rectOfHead[1].w = 32;
	rectOfHead[1].h = 32;

	// to reenter form east and inform the trainingGame to decrease the points
	if (xpos == 0) {
		xpos = 800;
		
		//decrease the points by one 
		trainingCourse::points -= 1;

		//update the information on the screen
		trainingCourse::textTexture = TextureManager::TextTexture(trainingCourse::points, trainingCourse::maxPoints, trainingCourse::length, trainingCourse::min, trainingCourse::sec, trainingCourse::stage, 800, 20);
	}
}

//this function checks if the sides of the rectangles of the head and the carts are colliding with each other or not
//we need a parameter called a number which specifies the number of the carts
void Wagon::checkCollisionTheHeadWithCart(SDL_Rect a, SDL_Rect b, int number)
{
	//The sides of the two rectangles (head and cart)
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
		collision_cart[number] = false;
	else if (topA >= bottomB)
		collision_cart[number] = false;
	else if (rightA <= leftB)
		collision_cart[number] = false;
	else if (leftA >= rightB)
		collision_cart[number] = false;

	//If none of the sides from A are outside B
	//which means there is a collision
	else {
		collision_cart[number] = true;
	}
}

// inform trainingGame a detailed information about the head
// this data will be used to let the carts simulate the head movement with some calculations!
int* Wagon::trackPostiotion() {
	infoPostiotion[0] = xpos; infoPostiotion[1] = ypos; infoPostiotion[2] = degree;
	infoPostiotion[3] = center.x; infoPostiotion[4] = center.y; infoPostiotion[5] = flip;
	
	return infoPostiotion;
}

//this function used to reset the position of the head 
//this function used when there is a request to restart the game
void Wagon::reset() {
	xpos = 180;
	ypos = 320;
	degree = 0;
	flip = SDL_FLIP_HORIZONTAL;
	flip = SDL_FLIP_VERTICAL;
}

void Wagon::Render() {
	//rendering the head
	SDL_RenderCopyEx(trainingGame::renderer, objTexture, &srcRect, &destRect, degree, &center, flip);

	//a for loop to check every time if there is a collision between the head and one of the carts
	for (int n = 0; n < trainingGame::nTail; n++) {
		checkCollisionTheHeadWithCart(rectOfHead[0], Cart::rectOfCart[n], n);
	}

}