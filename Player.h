/*
 * Player.h
 *
 *  Created on: 13 de jul de 2017
 *      Author: Anderson
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Stage.h"
#include "Monster.h"

typedef struct player_battle{
	int hp, mp;
	int atk, def;
	int exp;
	int critical;
	int ataque, ataqueNormal, readyAtaque, contadorAtaque;
	int adjust;
}PlayerBattle;

typedef struct player_info {
	SDL_Surface** surface;
	SDL_Texture** tex;
	SDL_Renderer** render;
	SDL_Rect* sprite;
	char *pathSprite;
	int start;
	int numSprite;
	int up, down, left, rigth,flag,run;
	int x, y;
	char *name;
	char *FirstSprite;
	char *textMenu;
	int state;
	int battleState, ready;

	PlayerBattle* battle;
}PlayerConf;

int up, down, left, right;
int variacaoSprite;
int variacaoRigth;

int setupSprite(PlayerConf*,SDL_Rect*);

void changeSprite(PlayerConf*,SDL_Rect*,int);

void battleState(PlayerConf*,MonsterInfo*);

void drawCollision(PlayerConf*);
#endif /* PLAYER_H_ */
