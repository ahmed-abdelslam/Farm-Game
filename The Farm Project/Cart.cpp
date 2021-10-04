#include "Cart.h"
#include "TextureManager.h"

//to share these variables
int Cart::startPosOfCartNO[100];
SDL_Rect Cart::rectOfCart[100];

Cart::Cart(const char* texture, int x, int y) {
	//create a texture
	objTexture = TextureManager::LoadTexture(texture);

	// position of the cart x-axis and y-axis
	xpos = x;
	ypos = y;
}

Cart::~Cart()
{
}


void Cart::setRect(int cartNO) {
	//set the rectangle of the cart based on its number , xposition, yposition, height, width
	rectOfCart[cartNO].x = xpos + 10;
	rectOfCart[cartNO].y = ypos + 10;
	rectOfCart[cartNO].h = 13;
	rectOfCart[cartNO].w = 13;
}

//this function simulate the previous actions of the head 
//the carts will be move as the movement of the head
void Cart::simulator(int tailNO) {

	//to create a transparent rectangle around the cart
	//will be used later to detect if there is a collision between the head and one of the carts 
	setRect(tailNO);

	//reset to 0 if the index reach to the maximum value
	if (Cart::startPosOfCartNO[tailNO] == 49999) {
		Cart::startPosOfCartNO[tailNO] = 0;
	}

	//set the height and width, x-axis and y-axis of the source rectangle (the car itself)
	//this rectangle specifies the size of the cart
	srcRect.h = 35;
	srcRect.w = 35;
	srcRect.x = 0;
	srcRect.y = 0;

	//set the height and width same as srcRect, and change the x-axis and y-axis same as xpos and ypos of the cart
	//this rectangle called the destination rectangle and the SDL use it to send it to the render
	//destination of the car on the screen (always changing)
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	// position  x-axis and y-axis , degree, center point and flip of the cart same as the previous actions of the head
	xpos = trainingGame::storageOfMovement[Cart::startPosOfCartNO[tailNO]][0];
	ypos = trainingGame::storageOfMovement[Cart::startPosOfCartNO[tailNO]][1];
	degree = trainingGame::storageOfMovement[Cart::startPosOfCartNO[tailNO]][2];
	center.x = trainingGame::storageOfMovement[Cart::startPosOfCartNO[tailNO]][3];
	center.y = trainingGame::storageOfMovement[Cart::startPosOfCartNO[tailNO]][4];
	if (trainingGame::storageOfMovement[Cart::startPosOfCartNO[tailNO]][5] == 1) // 1 means the head was flipped horizontal
		flip = SDL_FLIP_HORIZONTAL;
	else // else means the head was flipped vertical
		flip = SDL_FLIP_VERTICAL;

	//increment to the next action if there is no collision or the user didn't win yet
	if (!trainingGame::collisionWithCart && !trainingGame::collisionWithObstacle && !trainingGame::win) {
		Cart::startPosOfCartNO[tailNO] = Cart::startPosOfCartNO[tailNO] + 1;
	}

}
void Cart::Render() {
	//rendering the cart
	SDL_RenderCopyEx(trainingGame::renderer, objTexture, &srcRect, &destRect, degree, &center, flip);
}