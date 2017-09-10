#include "background.h"



int createStage(Background* background)
{
	*background->surface = IMG_Load("resourcers/magus.png");
	if(!*background->surface)
	{
		return 0;
	}

	*background->text = SDL_CreateTextureFromSurface(*background->render, *background->surface);

	if(!*background->text)
	{
		return 0;
	}

	SDL_QueryTexture(*background->text, NULL, NULL, &background->stage->w,&background->stage->h);

	background->stage->h = 1060;
	background->stage->w = 1120;
	background->stage->x = 0;
	background->stage->y = -360;

	SDL_FreeSurface(*background->surface);

	return 1;
}