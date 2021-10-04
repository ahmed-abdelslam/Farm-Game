#include "TextureManager.h"
#include "trainingGame.h"
#include "trainingCourse.h"
#include "Passenger.h"
#include "Wagon.h"
#include "Cart.h"
#include "Obstacle.h"
#include "Notification.h"
#include "Stages.h"

//declare objects
trainingCourse* course;
Passenger* Farmer;
Passenger* FarmerWithCrop;
Wagon* Head;
Cart* carts[100];
Obstacle* obstacle;
Notification* Lose;
Notification* Win;
Stages* stage;

//to share these variables
int trainingGame::nTail = 0;
int trainingGame::row;
int trainingGame::storageOfMovement[50000][6]; //store maximum 50,000 movements
bool trainingGame::collisionWithCart;
bool trainingGame::collisionWithObstacle;
bool trainingGame::win;

//initialize the renderer to nullptr
SDL_Renderer* trainingGame::renderer = nullptr;

//constructor and destructor
trainingGame::trainingGame() {};
trainingGame::~trainingGame() {};

//inintialize the SDL subsystems, window, render and objects 
void trainingGame::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	//if fullscreen true, run a fullscreen window
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//IF RETURN ZERO THAT MEANS WE HAVE SUCCESFULLY INITALIZED SDL SUBSYSTEMS
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { 
		cout << "Subsystems Initialized !... " << endl;

		//create the window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			cout << "Window created !.." << endl;
		}

		//create renderer to render the window
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			cout << "Renderer created !.." << endl;
		}

		//to let the game running
		isRunning = true;
	}
	else {
		//to exit from the game
		isRunning = false;
	}

	// initialize the objects
	//stage object
	stage = new Stages();

	//call function setStage from class Satges with argument 0 to start the game at the first stage
	stage->setStage(0);

	// trainingCourse object with argument "path of the background image"
	course = new trainingCourse("Asset/Background.png");

	// Head of Wagon object with arguments "path of the head image", x-position and y position
	Head = new Wagon("Asset/Head.png", 180, 320);

	//farmer object with arguments "path of the farmer image", x-position and y position
	// call random position function to initialize the x and y positions of the farmer
	Farmer = new Passenger("Asset/farmer.png", randomXposition(), randomYposition());

	//farmer with crop object with arguments "path of the farmer with crop image", x-position and y position
	// call random position function to initialize the x and y positions of the farmer
	FarmerWithCrop = new Passenger("Asset/farmer_with_crop.png", randomXposition(), randomYposition());

	//create obstacle object with argument "path of the wall image"
	obstacle = new Obstacle("Asset/wall.png");

	//lose object with arguments "path of the 'you_lose' image", x-position and y position
	Lose = new Notification("Asset/you_lose.png", 85, 150);

	//win object with arguments "path of the 'you_win' image", x-position and y position
	Win = new Notification("Asset/you_win.png", 74, 150);

};


//handle key pressing
void trainingGame::handleEvents() {
	
	//declare event with type SDL_Event
	SDL_Event event;
	
	//SDL_PollEvent(&event) returns 1 if there is a pending event or 0 if there are none available.
	while (SDL_PollEvent(&event) != 0)
	{

		//User requests quit
		if (event.type == SDL_QUIT)
		{
			//set isRunning to false to end the game
			isRunning = false;
		}

		//User presses a key
		else if (event.type == SDL_KEYDOWN)
		{

			//Select movement based on key press
			switch (event.key.keysym.sym)
			{

			//press key 'w'
			case SDLK_w:
				cout << "move to the up" << endl;
				
				//set requestForMove to 1 which means move to the up
				//as long as the previous value of requestForMove isn't 2
				//because 2 means the head was moving to the down
				//and we want to prevent the user from moving the head from down to up suddenly
				if (requestForMove != 2 && controlAvailability) 
					requestForMove = 1;
				break;

			//press key 's'
			case SDLK_s:
				cout << "move to the down" << endl;

				//set requestForMove to 2 which means move to the down
				//as long as the previous value of requestForMove isn't 1
				//because 1 means the head was moving to the up
				//and we want to prevent the user from moving the head from up to down suddenly
				if (requestForMove != 1 && controlAvailability)
					requestForMove = 2;
				break;

			//press key 'd'
			case SDLK_d:
				cout << "move to the right" << endl;

				//set requestForMove to 3 which means move to the right
				//as long as the previous value of requestForMove isn't 4
				//because 4 means the head was moving to the left
				//and we want to prevent the user from moving the head from left to right suddenly
				if (requestForMove != 4 && controlAvailability)
					requestForMove = 3;
				break;

			//press key 'a'
			case SDLK_a:
				cout << "move to the left" << endl;

				//set requestForMove to 4 which means move to the left
				//as long as the previous value of requestForMove isn't 3
				//because 3 means the head was moving to the right
				//and we want to prevent the user from moving the head from right to left suddenly
				if (requestForMove != 3 && controlAvailability)
					requestForMove = 4;
				break;

			//press key 'r'
			case SDLK_r:

				//if pressKeyR is true
				//set restartRequest to true to call function restart later 
				//set controlAvailability to true to allow the user again to press any movement key
				if (pressKeyR) {
					restartRequest = true;
					controlAvailability = true;
				}
				break;

			//press key 'c'
			case SDLK_c:

				//if pressKeyC is true
				//set requestForContinue to true to call function moveToNextStage later 
				//set controlAvailability to true to allow the user again to press any movement key
				if (pressKeyC) {
					requestForContinue = true;
					controlAvailability = true;
				}
				break;

			default:
				break;
			}
		}
	}
};

// generate a random x position to the farmer
int trainingGame::randomXposition() {

	// randomly choose the side, right of the obstacles or left of the obstacles
	chooseSideRan = rand() % 2;

	// == 1 means the left side
	if (chooseSideRan == 1) {
		//generate random number between 0 and 309
		//from 0 to 309 is the whole area from left of the window to the beginning of obstacles
		randPosX = rand() % 333;
		cout << "the farmer on the left side" << endl;
	}
	// else means the right side
	else {
		//generate random number between 0 and 309 and adding 410 
		//to make sure that the farmer will be on the right side 
		//and also to prevent the farmer from being above the obstacles
		//from 378 to 768 is the whole area from right of the obstacles to the end of window
		randPosX = (rand() % 378) + 390;
		cout << "the farmer on the right side" << endl;
	}

	return randPosX;
}

// generate a random y position to the farmer
int trainingGame::randomYposition() {
	//generate random number between 0 and 590 and adding 18
	//to make sure that the farmer will be away from the text information located at the top of the window
	//from 18 to 608 is the whole area of the window from top to bottom
	randPosY = (rand() % 590) + 18;
	return randPosY;
}

//updating the game every second with the new changes
void trainingGame::update() {

	//update the trainingCourse to run the timer function
	course->Update();

	//showing the carts if it is true
	if (showTheCarts) {
		//a for loop to let the carts 'based on length of nTail' simulate the movement of the head
		for (int count = 0; count < nTail; count++) {
			//simulate the movement of the head for the cart of [count]
			carts[count]->simulator(count);
		}
	}

	//showing the farmer or the farmer with a crop in the default position
	Farmer->Default();
	FarmerWithCrop->Default();

	//moving the head based on requestForMove number
	if (requestForMove == 0)
		Head->Default();
	else if (requestForMove == 1)
		Head->movingUp();
	else if (requestForMove == 2)
		Head->movingDown();
	else if (requestForMove == 3)
		Head->movingRight();
	else if (requestForMove == 4)
		Head->movingLeft();
	else
		cout << "not valid" << endl;

	//this function is used to store detailed information about the head
	//we will benefit from this function later to make the carts simulate the head movement
	statusOfHead();

	//if a collision occurs with any farmer
	//call this function to generate a new farmer and increase the tail by one or two based on type of the farmer
	if (Passenger::collision_farmer)
		collisionWithFarmer();

	//a for loop to check each time if the head collides with one of the obstacles
	for (int p = 0; p < Obstacle::numberOfObstacle; p++) {
		//if a collision occurs with obstacle number [n]
		//call this function to stop the game and show notification of loss
		if (Obstacle::collision_obs[p]) {
			stopTheGame();
			//set collisionWithObstacle to true
			//the cart class will know that collisionWithObstacle is true and will stop the simulator function
			collisionWithObstacle = true;
			//set collision_obs[p] to false
			Obstacle::collision_obs[p] = false;
			//break the for loop
			break;
		}
		else 
			collisionWithObstacle = false;
	}

	//a for loop to check each time if the head collides with one of the carts
	for (int n = 0; n < nTail; n++) {
		//if a collision occurs with cart number [n]
		//call this function to stop the game and show notification of loss
		if (Wagon::collision_cart[n]) {
			stopTheGame();
			//set collisionWithCart to true
			//the cart class will know that collisionWithCart is true and will stop the simulator function
			collisionWithCart = true;
			Wagon::collision_cart[n] = false;
			break;
		}
		else
			collisionWithCart = false;
	}

	//if there is a request to continue, call this function to move to the next stage
	if (requestForContinue)
		moveToNextStage();

	//if there is a request to restart, call this function to restart 
	if (restartRequest)
		restart();

	//if time is over, stop the game! and show the notification of loss
	if (trainingCourse::min == 0 && trainingCourse::sec == 1) {
		stopTheGame();
		cout << "time is over" << endl;
	}

	//if the user reaches 25 or more points in stage 1, call reachTheScore
	if (trainingCourse::points >= 25 && Stages::stage1) {
		//set win to true and the cart class will know that and will stop the simulator function 
		win = true;
		//call this function to stop the movement of the head and show the notification of winning
		reachTheScore();
		//set the number of the next stage to 1, meaning the second stage
		numberOfStage = 1;
	}

	//if the user reaches 35 or more points in stage 2, call reachTheScore
	else if (trainingCourse::points >= 35 && Stages::stage2) {
		//set win to true and the cart class will know that and will stop the the simulator function 
		win = true;
		//call this function to stop the movement of the head and show the notification of winning
		reachTheScore();
		//set the number of the next stage to 2, meaning the third stage
		numberOfStage = 2;
	}

	//if the user reaches 45 or more points in stage 3, call reachTheScore
	else if (trainingCourse::points >= 45 && Stages::stage3) {
		//set win to true and the cart class will know that and will stop the the simulator function 
		win = true;
		//call this function to stop the movement of the head and show the notification of winning
		reachTheScore();
		//set the number of the next stage to 0, meaning the first stage to play again from beginning
		numberOfStage = 0;
	}

	//SDL function to update the surface of the window
	SDL_UpdateWindowSurface(window);
};

void trainingGame::collisionWithFarmer() {

	//now we will set showTheCarts to true to allow rendering the carts objects if the opposite value is true
	if (!showTheCarts)
		showTheCarts = true;

	//check if the collision was with a farmer or with a farmer with crop
	//if the collision was with just a farmer we will increase the carts by one
	// 1 means a normal farmer
	if (chooseRandomly == 1) {
		//randomly change the location of the normal farmer
		Farmer->changeLocation(randomXposition(), randomYposition());
		//calculate the appropriate position for the new cart to be behind the head if it is the first cart
		//or to be behind the last cart if it is not the first cart
		calculateThePositionOfTheNewCart(nTail);

		//create object cart with index nTail, 
		//with arguments "path of the Cart image", x-position and y position
		//0, 0 is just to initialize the posiotns
		carts[nTail] = new Cart("Asset/Cart.png", 0, 0);

		//increase the tail by one
		nTail++;

		//increase the length that is displayed on the screen by one
		trainingCourse::length += 1;

		//increase the points that is displayed on the screen by one
		trainingCourse::points += 1;

		//update the information on the screen with the new changes
		//a full explanation of this line in trainingCourse.cpp
		trainingCourse::textTexture = TextureManager::TextTexture(trainingCourse::points, trainingCourse::maxPoints, trainingCourse::length, trainingCourse::min, trainingCourse::sec, trainingCourse::stage, 800, 20);
	}

	//if the collision was with a farmer with crop we will increase the carts by two
	//0 means a farmer with a crop
	else if (chooseRandomly == 0) {
		//randomly change the location of farmer with crop
		FarmerWithCrop->changeLocation(randomXposition(), randomYposition());
		//calculate the appropriate position for the new cart to be behind the head if it is the first cart
		//or to be behind the last cart if it is not the first cart
		calculateThePositionOfTheNewCart(nTail);

		//create object cart with index nTail, 
		//with arguments "path of the Cart image", x-position and y position
		//0, 0 is just to initialize the posiotns
		carts[nTail] = new Cart("Asset/Cart.png", 0, 0);

		//increase the tail by one
		nTail++;

		//calculate the appropriate position for the new cart to be behind the head  
		calculateThePositionOfTheNewCart(nTail);

		//create object cart with index nTail, 
		//with arguments "path of the Cart image", x-position and y position
		//0, 0 is just to initialize the posiotns
		carts[nTail] = new Cart("Asset/Cart.png", 0, 0);

		//increase the tail by one
		nTail++;
		
		//increase the length that is displayed on the screen by two
		trainingCourse::length += 2;

		//increase the points that is displayed on the screen by two
		trainingCourse::points += 2;

		//update the information on the screen with the new changes
		//a full explanation of this line in trainingCourse.cpp
		trainingCourse::textTexture = TextureManager::TextTexture(trainingCourse::points, trainingCourse::maxPoints, trainingCourse::length, trainingCourse::min, trainingCourse::sec, trainingCourse::stage, 800, 20);
	}

	//generate random choosing between a normal farmer or a farmer with a crop
	//for the next time
	chooseRandomly = rand() % 2;
}

//if a collision occurs with a cart or an obstacle, stop the head and close the controller keys
void trainingGame::stopTheGame() {
	requestForMove = 0;
	controlAvailability = false;
	//set showLoseNotification to true to render the notification of loss
	showLoseNotification = true;
	//now, allow the user to press key R so he/she can restart the game
	pressKeyR = true;
}

//if the user reached the maximum points, stop the head and close the controller keys
void trainingGame::reachTheScore() {
	requestForMove = 0;
	controlAvailability = false;
	//set showWinNotification to true to render the notification of winning
	showWinNotification = true;
	//now, allow the user to press key C so he/she can move to the next stage
	pressKeyC = true;
}


void trainingGame::statusOfHead() {
	//receive from class wagon the values of the head 
	//receive the xposition, yposition, degree, center point x, center point y, flip
	stateOfHead = Head->trackPostiotion();

	//fill the information of the head into a 2D array
	for (int col = 0; col < 6; col++) {
		trainingGame::storageOfMovement[row][col] = *(stateOfHead + col);
	}
	//increase the row
	row++;

	//if row equals 49999 set the row to 0
	if (row == 49999)
		row = 0;
}

//calculate the appropriate position for the new cart
void trainingGame::calculateThePositionOfTheNewCart(int TailNO) {
	//We will subtract 35 from the value of the current row which contains the current positions of the head,
	//35 is an appropriate number to be the cart behind the head or the other carts
	//for example for the cart number 0, if the row of the head when the collision occurs at 200,
	//so 200 + (-35 * ( 0 + 1 ) = 165, 
	//the cart number 0 starts from row 165
	//by a function called simulator in class cart, the calculated row will increase 
	//and the cart will simulate the previous movement of the head 
	calcPosOfCartNO[TailNO] = row + (-35 * (TailNO + 1));

	//assign the calculated row for the new cart to startPosOfCartNO[TailNO] 
	Cart::startPosOfCartNO[TailNO] = calcPosOfCartNO[TailNO];
}

void trainingGame::restart() {
	//reset the length of tail
	nTail = 0;

	//allow the user to press any controller key
	controlAvailability = true;

	//hide the carts
	showTheCarts = false;
	
	//hide the notification of loss
	showLoseNotification = false;
	
	//set restartRequest to false
	restartRequest = false;
	
	//reset the displayed information
	course->reset();
	
	//reset the head to the original position
	Head->reset();
	
	//prevent the user from press key r, so he can't restart the game while he is playing
	pressKeyR = false;
	
	//reset the row of storageMovement, to store the information from the beginning
	row = 0;

}

void trainingGame::moveToNextStage() {
	//reset the length of tail
	nTail = 0;
	
	//allow the user to press any controller key
	controlAvailability = true;
	
	//hide the carts
	showTheCarts = false;
	
	//hide the notification of winning
	showWinNotification = false;
	
	//set requestForContinue to flase
	requestForContinue = false;
	
	//reset the displayed information
	course->reset();
	
	//reset the head to the original position
	Head->reset();
	
	//call setStage with argument numberOfStage to setup the next stage
	stage->setStage(numberOfStage);
	
	//prevent the user from press key c, so he can't move to the next stage at beginning of the stage
	pressKeyC = false;
	
	//set win to false and the cart class will know that and will allow the simulator function to work
	win = false;
}

void trainingGame::render() {
	//SDL function to clear the old render
	SDL_RenderClear(renderer);

	// this is where we would add stuff to render

	//rendering the course
	course->Render();

	//rendering the obstacle
	obstacle->Render();

	//rendering the carts if showTheCarts true
	if (showTheCarts) {
		//rendering the carts based on the value of nTail which is the length of tail
		for (int count = 0; count < nTail; count++)
			carts[count]->Render();
	}

	//rendering the farmer if the value of chooseRandomly 1
	if (chooseRandomly == 1)
		Farmer->Render();

	//rendering the farmer with crop if the value of chooseRandomly 0
	else
		FarmerWithCrop->Render();

	//rendering the head of the wagon
	Head->Render();

	//rendering the notification of losing if showLoseNotification true
	if (showLoseNotification)
		Lose->Render();

	//rendering the notification of winning if showWinNotification true
	if (showWinNotification)
		Win->Render();

	//update the screen with any rendering performed
	SDL_RenderPresent(renderer);
}

void trainingGame::clean() {
	//calls the destructor of each object
	delete course;
	delete Farmer;
	delete FarmerWithCrop;
	delete Head;
	for (int n = 0; n < ( nTail - 1 ); n++)
		delete carts[n];
	delete obstacle;
	delete Lose;
	delete Win;
	delete stage;

	//destroy the window
	SDL_DestroyWindow(window);

	//destroy the renderer
	SDL_DestroyRenderer(renderer);

	//exit from SDL
	SDL_Quit();

	cout << "Game Cleaned !.." << endl;
};