#include "monster.h"

#define SPEED 5

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
	monster->monster_rect->x = 100 * monster->id;
	monster->monster_rect->y = 400;
	SDL_Log("monster -> %d created! ", monster->id);
	SDL_FreeSurface(*monster->surface);

}


int monster_move = 0;

int move_monster(Monster* monster)
{
	monster_move++;
	if(monster_move >= 200)
		monster_move = 1;

	if(monster_move <= 100)
	{
		monster->monster_rect->x += SPEED;
	}
	else
	{
		monster->monster_rect->x -= SPEED;
	}
}