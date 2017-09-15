/*
 * Monster.c
 *
 *  Created on: 17 de jul de 2017
 *      Author: Anderson
 */
#include "Monster.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>



void setupMonster(MonsterInfo* monster){
	variacaoSpriteM = 0;
	char* path = "Resourcers/Monster1.png";

	*monster->surface = IMG_Load(path);

	if(!*monster->surface){
		SDL_Log("Error in load monster image -> %s", SDL_GetError());
	}

	*monster->tex = SDL_CreateTextureFromSurface(*monster->render, *monster->surface);

	if(!*monster->tex){
		SDL_Log("Error in load texture for monster! -> %s", SDL_GetError());
	}

	SDL_QueryTexture(*monster->tex, NULL, NULL, &monster->monsterRect->w, &monster->monsterRect->h);

	SDL_FreeSurface(*monster->surface);

	//Set Monster data
	monster->monsterRect->w *= 3;
	monster->monsterRect->h *= 3;
	monster->monsterRect->x = monster->x;
	monster->monsterRect->y = monster->y;
	monster->battle = (MonsterBattle*) malloc(sizeof(MonsterBattle) * 50);
	monster->battleState = 0;
	monster->battle->hp = 100;
	monster->battle->isDead = 0;
	SDL_Log("foi %s", SDL_GetError());
	variacaoSpriteM = 0;

}

void moveMonster(MonsterInfo* monster){
	variacaoSpriteM++;
	if(!monster->battleState){
		if(variacaoSpriteM > 150)
			variacaoSpriteM = 0;

		if(variacaoSpriteM < 50){
			monster->monsterRect->x += 3;
			changeMonster(monster);
		}

		if(variacaoSpriteM > 100){
			monster->monsterRect->x -= 3;
			changeMonster(monster);
		}
	}
}


///// implements
void changeMonster(MonsterInfo* monster)
{
	variacaoChange++;
	if(variacaoChange > 1000)
		variacaoChange = 1;
	if(variacaoChange % 10 == 0)
	{
		spriteNum++;
		if(spriteNum > 3)
			spriteNum = 1;

		SDL_Log("%d", spriteNum);

		if(monster->battle->damage != 1)
			sprintf(monster->pathSprite,"%s%d%s","Resourcers/Monster",spriteNum,".png");
		else if(monster->battle->damage == 1)
			sprintf(monster->pathSprite,"%s","Resourcers/MonsterDamage.png");
		
		*monster->surface = IMG_Load(monster->pathSprite);

		if(!*monster->surface){
			SDL_Log("Error in load monster %s", SDL_GetError());
		}

		*monster->tex = SDL_CreateTextureFromSurface(*monster->render,*monster->surface);
		if(!*monster->tex){
			SDL_Log("Error create texture %s", SDL_GetError());
			return ;
		}
		SDL_QueryTexture(*monster->tex, NULL, NULL, &monster->monsterRect->w, &monster->monsterRect->h);
		SDL_FreeSurface(*monster->surface);
		monster->monsterRect->w *= 3;
		monster->monsterRect->h *= 3;
	}
}
