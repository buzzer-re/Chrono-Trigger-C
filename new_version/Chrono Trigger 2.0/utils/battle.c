#include "battle.h"


int battlePosition(SDL_Rect* sprite, SDL_Rect* enemy)
{
	if(sprite->x - enemy->x < (enemy->w * 3))
	{
		sprite->x += 10;
	}
	return 1;
}