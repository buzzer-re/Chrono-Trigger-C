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
	char* path = "Resourcers/Monster.png";

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
	monster->monsterRect->x = 400;
	monster->monsterRect->y = 200;
	monster->battle = (MonsterBattle*) malloc(sizeof(MonsterBattle) * 50);
	monster->battleState = 0;
	SDL_Log("foi %s", SDL_GetError());

}



void moveMonster(MonsterInfo* monster){
	variacaoSpriteM++;
	if(!monster->battleState){
		if(variacaoSpriteM > 150)
			variacaoSpriteM = 0;

		if(variacaoSpriteM < 50)
			monster->monsterRect->x += 3;

		if(variacaoSpriteM > 100)
			monster->monsterRect->x -= 3;
	}
}
