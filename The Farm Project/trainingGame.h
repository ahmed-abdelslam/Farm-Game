#ifndef trainingGame_hpp
#define trainingGame_hpp
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
using namespace std;

class trainingGame {
public:

	trainingGame();
	~trainingGame();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	void restart();
	void collisionWithFarmer();
	void stopTheGame();
	void moveToNextStage();
	void reachTheScore();
	void statusOfHead();
	void calculateThePositionOfTheNewCart(int TailNO);

	bool running() { return isRunning; };

	bool collision_With_Farmer = false, showTheCarts = false, collision_With_Carts[30], collision_With_Obstacle[6];
	bool controlAvailability = true;
	bool restartRequest = false;
	bool pressKeyR = false;
	bool pressKeyC = false;
	bool static collisionWithCart;
	bool static collisionWithObstacle;
	bool showLoseNotification = false;
	bool showWinNotification = false;
	bool requestForContinue = false;
	bool static win;

	int calcPosOfCartNO[100];
	int randPosX, randPosY, requestForMove = 0;
	int static nTail;
	int numberOfStage;
	int chooseSideRan;
	int *stateOfHead;
	int chooseRandomly = 1;
	int static storageOfMovement[50000][6];
	int static row;
	int randomXposition();
	int randomYposition();

	SDL_Rect obstacleInfo;
	
	static SDL_Renderer* renderer;

private:
	int count = 0;

	bool isRunning;

	SDL_Window *window;

};
#endif /* trainingGame */