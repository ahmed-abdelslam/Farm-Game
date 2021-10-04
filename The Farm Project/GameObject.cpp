#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* texture, int x, int y, int size) {
	
	objTexture = TextureManager::LoadTexture(texture);
	
	xpos = x;
	ypos = y;
	imageSize = size;
}

GameObject::~GameObject()
{
}
void GameObject::randPositionFarmerInfo(int x, int y) {
	xposOfFarmer = x;
	yposOfFarmer = y;
	cout << xposOfFarmer << " && " << yposOfFarmer << endl;
	
}
void GameObject::Update() {
		//if (imageSize == 32) {
			srcRect.h = 32;
			srcRect.w = 32;
			srcRect.x = 0;
			srcRect.y = 0;

			destRect.x = xpos;
			destRect.y = ypos;
			destRect.w = srcRect.w;
			destRect.h = srcRect.h;

		//}
		/*else if (imageSize == 64) {
			srcRect.h = 64;
			srcRect.w = 64;
			srcRect.x = 0;
			srcRect.y = 0;

			destRect.x = xpos;
			destRect.y = ypos;
			destRect.w = srcRect.w;
			destRect.h = srcRect.h;

		}*/
	flip = SDL_FLIP_NONE;
	if (xpos == 800)
		xpos = 0;
	if (ypos == 640)
		ypos = 0;
}
void GameObject::UpdateU(int pre) {
	//xpos++;
	ypos--;
	//if (imageSize == 32) {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	center.x = srcRect.w / 2;
	center.y = srcRect.h / 2;
	degree = -90;
	flip = SDL_FLIP_VERTICAL;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	
	//}
	/*else if (imageSize == 64) {
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	}*/

	if (ypos == 0)
		ypos = 640;
}
void GameObject::UpdateS(int pre) {
	//xpos++;
	ypos++;
	//if (imageSize == 32) {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	degree = 90;
	flip = SDL_FLIP_VERTICAL;
	//}
	/*else if (imageSize == 64) {
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	}*/
	if (xposOfFarmer == xpos && yposOfFarmer == ypos)
		cout << "Collision : " << endl;
	if (ypos == 640)
		ypos = 0;
}
void GameObject::UpdateD(int pre) {
	xpos++;
	//if (imageSize == 32) {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	degree = 0;
		//flip = SDL_FLIP_HORIZONTAL;
	//}
	/*else if (imageSize == 64) {
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	}*/
	if (xposOfFarmer == xpos && yposOfFarmer == ypos)
		cout << "Collision : " << endl;
	if (xpos == 800)
		xpos = 0;
}
void GameObject::UpdateA(int pre) {
	xpos--;
	//if (imageSize == 32) {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	center.x = srcRect.w / 2;
	center.y = srcRect.h / 2;
	degree = 0;
	flip = SDL_FLIP_HORIZONTAL;

	//}
	/*else if (imageSize == 64) {
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	}*/
	if (xposOfFarmer == xpos && yposOfFarmer == ypos)
		cout << "Collision : " << endl;
	if (xpos == 0)
		xpos = 800;
}
void GameObject::Render() {
	SDL_RenderCopyEx(trainingGame::renderer, objTexture, &srcRect, &destRect, degree, &center, flip);
}