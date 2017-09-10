#include "monster.h"


int set_monster(Monster* monster)
{

	*monster->surface = IMG_Load("resourcers/Monster1.png");

	if(!*monster->surface)
	{
		return 0;
	}

	*monster->text = SDL_CreateTextureFromSurface(*monster->render, *monster->surface);

	if(!*monster->text)
	{
		return 0;
	}

	SDL_QueryTexture(*monster->text,NULL,NULL,&monster->monster_rect->w,&monster->monster_rect->h);

	monster->monster_rect->w *= 3;
	monster->monster_rect->h *= 3;
	monster->monster_rect->x = 300;
	monster->monster_rect->y = 400;

	SDL_FreeSurface(*monster->surface);

}