/*
 * Player.h
 *
 *  Created on: 13 de jul de 2017
 *      Author: bigboss
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Stage.h"
typedef struct player_info {
	SDL_Surface** surface;
	SDL_Texture** tex;
	SDL_Renderer** render;
	char *pathSprite;
	int start;
	int numSprite;
	int up, down, left, rigth;
	char *name;
	int state;
}PlayerConf;

int up, down, left, right;
int variacaoSprite;
int variacaoRigth;

int setupSprite(PlayerConf*,SDL_Rect*);

void move(SDL_Rect*,int*,PlayerConf*,STAGE*);

void changeSprite(PlayerConf*,SDL_Rect*,int);


void drawCollision(PlayerConf*);
#endif /* PLAYER_H_ */
