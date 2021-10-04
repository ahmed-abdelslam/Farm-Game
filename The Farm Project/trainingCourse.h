#include "trainingGame.h"

class trainingCourse {
public:

	trainingCourse(const char* texture);
	~trainingCourse();
	void setRect();
	void Update();
	void Render();
	void timerFunction();
	void reset();

	static SDL_Texture* textTexture;

	int static points, maxPoints, length, sec, min, milliSec, stage;

private:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Rect textRect, destTxtRect;

};
