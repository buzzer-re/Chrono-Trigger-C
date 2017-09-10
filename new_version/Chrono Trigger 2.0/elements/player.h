#include <SDL2/SDL.h>
#include <stdlib.h>

#ifndef _PLAYER_H
#define _PLAYER_H

typedef struct battle {
	int hp;
	int mp;
	int atk;
	int def;
	int inBattle;
	int sprite_img_limit;
}Battle;


typedef struct player{
	SDL_Renderer** render;
	SDL_Texture** text;
	SDL_Surface** surface;
	SDL_Rect* player_rect;
	char* name;
	char* sprite_img;
	int cont;
	int state;
	int action;
	int sprite_img_limit;
	int up, down , left, rigth;
	Battle battle;
}Player;


int set_sprite(Player*, int);

void change_sprite(Player*);


#endif
