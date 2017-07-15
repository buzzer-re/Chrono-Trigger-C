/*
 * Stage.c
 *
 *  Created on: 14 de jul de 2017
 *      Author: Anderson
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Stage.h"





void setupStage(STAGE* stage_conf){
	*stage_conf->surface = IMG_Load("Resourcers/magus.png");
	if(!*stage_conf->surface){
		SDL_Log("Error in load map! %s ", SDL_GetError());
	}

	*stage_conf->tex = SDL_CreateTextureFromSurface(*stage_conf->render, *stage_conf->surface);
	if(!*stage_conf->tex){
		SDL_Log("Error in texture creation! %s", SDL_GetError());
	}

	SDL_QueryTexture(*stage_conf->tex, NULL,NULL, &stage_conf->stage->w, &stage_conf->stage->y);

	stage_conf->stage->h = 10000;
	stage_conf->stage->w = 6000;
	stage_conf->stage->x = -1350;
	stage_conf->stage->y = -9360;
	stage_conf->limitY = stage_conf->stage->y;

	SDL_FreeSurface(*stage_conf->surface);
}

void mouseSet(STAGE* stage_conf){
	SDL_Event eveent;


	while(SDL_PollEvent(&eveent)){
		switch(eveent.type){
		case SDL_KEYDOWN:
			switch(eveent.key.keysym.scancode){
			case SDL_SCANCODE_RIGHT:
				stage_conf->stage->x += 40;
				break;
			case SDL_SCANCODE_LEFT:
				stage_conf->stage->x -= 40;
				break;
			case SDL_SCANCODE_UP:
				stage_conf->stage->y -= 40;
				break;
			case SDL_SCANCODE_DOWN:
				stage_conf->stage->y += 40;
				break;
			}
		}
	}

	SDL_Log("X - %d\nY - %d", stage_conf->stage->x, stage_conf->stage->y);
}
