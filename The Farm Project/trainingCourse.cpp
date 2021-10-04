#include "trainingCourse.h"
#include "TextureManager.h"
#include "Stages.h"
#include "Obstacle.h"
#include <sstream>

//to share these variables
SDL_Texture* trainingCourse::textTexture;
int trainingCourse::points;
int trainingCourse::maxPoints;
int trainingCourse::length;
int trainingCourse::min;
int trainingCourse::sec;
int trainingCourse::stage;
int trainingCourse::milliSec;

trainingCourse::trainingCourse(const char* texture) {
	//setting the rectangle that will contain the information
	setRect();

	//default values
	points = 0, length = 0, milliSec = 100;
	// create a texture to the background
	objTexture = TextureManager::LoadTexture(texture);
	// create a texture to the text
	textTexture = TextureManager::TextTexture(points, maxPoints, length, min, sec, stage, 800, 20);
}
trainingCourse::~trainingCourse() {}

void trainingCourse::setRect() {
	// Rectangle of background
	srcRect.h = 640; srcRect.w = 800; srcRect.x = 0; srcRect.y = 0;
	destRect.x = 0; destRect.y = 0; destRect.w = srcRect.w; destRect.h = srcRect.h;

	// Rectangle of txtTexture
	textRect.h = 18; textRect.w = 800; textRect.x = 0; textRect.y = 0;
	destTxtRect.x = textRect.x; destTxtRect.y = textRect.y; destTxtRect.h = textRect.h; destTxtRect.w = textRect.w;
}

void trainingCourse::timerFunction() {
	// to decrease the seconds when millisecond equals 0
	if (milliSec == 0) {
		if (Stages::stage1) {
			//set the milliseconds same as FPS defined in main.cpp
			milliSec = 100;

			//when restarting in this stage set noCollision to true
			if (min == 3 && sec == 59) {
				if (!Obstacle::noCollision)
					Obstacle::noCollision = true;
			}
		}
		else if (Stages::stage2) {
			milliSec = 160;

			//when restarting in this stage set noCollision to true
			if (min == 3 && sec == 29) {
				if (!Obstacle::noCollision)
					Obstacle::noCollision = true;
			}
		}
		else {
			milliSec = 180;

			//when restarting in this stage set noCollision to true
			if (min == 2 && sec == 59) {
				if (!Obstacle::noCollision)
					Obstacle::noCollision = true;
			}
		}

		//decrease the seconds by one
		sec--;

		//update the information on the screen
		textTexture = TextureManager::TextTexture(points, maxPoints, length, min, sec, stage, 800, 20);
	}

	// to decrese the minutes
	if (sec == 0) {
		sec = 59;
		min--;

		//update the information on the screen
		textTexture = TextureManager::TextTexture(points, maxPoints, length, min, sec, stage, 800, 20);
	}
}

void trainingCourse::Update() {
	milliSec--;
	timerFunction();
}

void trainingCourse::reset() {
	points = 0, length = 0;
	if (Stages::stage1) 
		min = 4, sec = 0, milliSec = 100;
	else if (Stages::stage2)
		min = 3, sec = 30, milliSec = 160;
	else
		min = 2, sec = 30, milliSec = 180;

	//update the information on the screen
	textTexture = TextureManager::TextTexture(points, maxPoints, length, min, sec, stage, 800, 20);
}

void trainingCourse::Render() {
	// render the background image
	SDL_RenderCopy(trainingGame::renderer, objTexture, &srcRect, &destRect);

	SDL_SetRenderDrawColor(trainingGame::renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(trainingGame::renderer, &textRect);
	SDL_RenderDrawRect(trainingGame::renderer, &textRect);

	// render the text
	SDL_RenderCopy(trainingGame::renderer, textTexture, &textRect, &destTxtRect);

	// background color 
	SDL_SetRenderDrawColor(trainingGame::renderer, 25, 168, 39, 0);
}