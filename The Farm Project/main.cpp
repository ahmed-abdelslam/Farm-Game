#include <SDL.h>
#include "trainingGame.h"
#include "Stages.h"

//create object from trainingGame class
trainingGame *TrainingGame = nullptr;

int main(int argc, char *argv[]) {

	int FPS;
	int frameDelay;
	Uint32 frameStart;
	int frameTime;
	
	TrainingGame = new trainingGame();
	
	// initialize the window 
	//title, positions x and y, width, height, fullscreen window
	TrainingGame->init("Farm | CPP Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	while (TrainingGame->running()) {
		//this function gets the number of milliseconds since the SDL library initialization
		frameStart = SDL_GetTicks();

		//handling events like pressing keys
		TrainingGame->handleEvents();

		//updating the window with new changes
		TrainingGame->update();

		//rendering the window
		TrainingGame->render();

		//calculate frame time
		frameTime = SDL_GetTicks() - frameStart;

		//if the user in the first stage set "framePerSecond" = 100
		if (Stages::stage1) {
			FPS = 100;
			frameDelay = 1000 / FPS;
		}

		//if the user in the second stage set "framePerSecond" = 160, increasing the speed of the game!
		else if (Stages::stage2) {
			FPS = 160;
			frameDelay = 1000 / FPS;
		}

		//if the user in the third stage set "framePerSecond" = 180, increasing the speed of the game!
		else {
			FPS = 180;
			frameDelay = 1000 / FPS;
		}

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	TrainingGame->clean();

	return 0;
}
