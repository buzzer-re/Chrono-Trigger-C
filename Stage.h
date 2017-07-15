/*
 * Stage.h
 *
 *  Created on: 14 de jul de 2017
 *      Author: bigboss
 */

#ifndef STAGE_H_
#define STAGE_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

typedef struct stage_conf{
	SDL_Renderer** render;
	SDL_Surface** surface;
	SDL_Texture** tex;
	SDL_Rect* stage;
	int limitY, limitX;
	int width, heigth;
}STAGE;

void setupStage(STAGE*);

void mouseSet(STAGE*);

#endif /* STAGE_H_ */
