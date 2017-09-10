#include "collision.h"


int collision_check(SDL_Rect* player, SDL_Rect* element)
{
	SDL_Rect aux;
	if(SDL_IntersectRect(player,element, &aux) == SDL_TRUE)
	{
		return 1;
	}
	
	return 0;
}