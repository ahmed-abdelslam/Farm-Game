#include "Notification.h"
#include "TextureManager.h"

Notification::Notification(const char* texture, int x, int y) {
	//create the texture
	objTexture = TextureManager::LoadTexture(texture);

	//x position and y position of the notification
	xpos = x;
	ypos = y;

}

Notification::~Notification() {}

void Notification::Render() {
	//set the height and width, x-axis and y-axis of the source rectangle (notification itself)
	//this rectangle specifies the size of the notification
	srcRect.h = 324;
	srcRect.w = 600;
	srcRect.x = 0;
	srcRect.y = 0;

	//set the height and width same as srcRect, and change the x-axis and y-axis same as xpos and ypos of
	//the notification
	//this rectangle called the destination rectangle and the SDL use it to send it to the render
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	//rendering the notification
	SDL_RenderCopy(trainingGame::renderer, objTexture, &srcRect, &destRect);

}