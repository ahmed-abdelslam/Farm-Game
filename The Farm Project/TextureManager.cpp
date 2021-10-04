#include "TextureManager.h"
#include <sstream>

//loading images and create surfaces
SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface *tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(trainingGame::renderer,tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return tex;
}

//convert integers to strings
std::string TextureManager::IntToString(int n)
{
	std::stringstream sstream;
	sstream << n;
	return sstream.str();
}

//creating text texture 
SDL_Texture* TextureManager::TextTexture(int points, int maxPoints, int length, int min, int sec, int stage, int width, int height) {
	//initialize ttf (font library)
	TTF_Init();
	SDL_Color textColor;
	TTF_Font* font = TTF_OpenFont("Fonts/Anke.ttf", 22);
	textColor.r = 0; textColor.g = 0; textColor.b = 0;

	//information will be shown on the screen
	std::string information = "POINTS : " + IntToString(points) + " OF " + IntToString(maxPoints)
							+ " LENGTH OF TAIL : " + IntToString(length) +
							" REMAINING TIME : " + IntToString(min) + " : " + IntToString(sec) + " STAGE : " 
							+ IntToString(stage);

	//create surface
	SDL_Surface *message = TTF_RenderText_Blended_Wrapped(font, information.c_str(), textColor, width);
	if (message == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//set the width of the message surface
	message->w = 800;

	//create text texture
	SDL_Texture* txt = SDL_CreateTextureFromSurface(trainingGame::renderer, message);
	SDL_SetTextureBlendMode(txt, SDL_BLENDMODE_BLEND);
	if (txt == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	SDL_FreeSurface(message);

	return txt;
}