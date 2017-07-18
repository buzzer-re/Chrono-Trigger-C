/*
 * Batalha.h
 *
 *  Created on: 17 de jul de 2017
 *      Author: Anderson
 */
#include "Player.h"
#include "Monster.h"

#include <SDL2/SDL_ttf.h>
#ifndef BATALHA_H_
#define BATALHA_H_

typedef struct text_info{
	SDL_Renderer** render;
	SDL_Surface** surface;
	SDL_Texture** tex;
	TTF_Font** font;
	SDL_Color* color;
	SDL_Rect* textRect;

	char* text;
}Text;

void menuPlayer(PlayerConf*,MonsterInfo*,SDL_Rect*,int,int,Text*);

#endif
