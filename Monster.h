/*
 * Monster.h
 *
 *  Created on: 17 de jul de 2017
 *      Author: Anderson
 */

#ifndef MONSTER_H_
#define MONSTER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>
#include "Stage.h"

typedef struct monsterBattle{
	int hp, mp;
	int atk, def;
	int critical;
}MonsterBattle;

typedef struct monster_info{
	SDL_Surface** surface;
	SDL_Texture** tex;
	SDL_Renderer** render;
	SDL_Rect* monsterRect;
	char *pathSprite;
	int start;
	int numSprite;
	int state;
	int battleState;
	int x,y;
	MonsterBattle* battle;
	STAGE* stage_conf;
}MonsterInfo;

int variacaoSpriteM;

void setupMonster(MonsterInfo*);

void moveMonster(MonsterInfo*);

#endif /* MONSTER_H_ */
