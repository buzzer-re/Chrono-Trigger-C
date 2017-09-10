#include <SDL2/SDL.h>
#ifndef _MONSTER_H
#define _MONSTER_H

typedef struct monster{
	SDL_Renderer** render;
	SDL_Texture** text;
	SDL_Surface** surface;
	SDL_Rect* monster_rect;
	int sprite_img_limit;
	int id;
}Monster;

int set_monster(Monster*);

int move_monster(Monster*);

#endif