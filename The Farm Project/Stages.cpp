#include "Stages.h"
#include "Obstacle.h"
#include "trainingCourse.h"

//to share these varaibles
bool Stages::stage1;
bool Stages::stage2;
bool Stages::stage3;

Stages::Stages() {}

Stages::~Stages() {}

//setting the stages based on the number of the stage
void Stages::setStage(int number) {
	if (number == 0) {
		stage1 = true;
		stage2 = false;
		stage3 = false;
		
		trainingCourse::maxPoints = 25;
		trainingCourse::min = 4;
		trainingCourse::sec = 0;
		trainingCourse::stage = 1;
		
		//reset the row of storageMovement, to store the information from the beginning
		trainingGame::row = 0;

	}
	else if (number == 1) {
		stage2 = true;
		stage1 = false;
		stage3 = false;
		
		trainingCourse::maxPoints = 35;
		trainingCourse::min = 3;
		trainingCourse::sec = 30;
		trainingCourse::stage = 2;
		
		//increase the number of obstacles to show one more obstacle on the screen
		Obstacle::numberOfObstacle++;
		
		//reset the row of storageMovement, to store the information from the beginning
		trainingGame::row = 0;
	}
	else {
		stage3 = true;
		stage1 = false;
		stage2 = false;
		
		trainingCourse::maxPoints = 45;
		trainingCourse::min = 3;
		trainingCourse::sec = 0;
		trainingCourse::stage = 3;

		//increase the number of obstacles to show one more obstacle on the screen
		Obstacle::numberOfObstacle++;

		//reset the row of storageMovement, to store the information from the beginning
		trainingGame::row = 0;
	}
}