/*
 * utils.h
 *
 *  Created on: 13 de jul de 2017
 *      Author: Anderson
 */
#ifndef UTILS_H_
#define UTILS_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
// My apis

#include "Player.h"
#include "Stage.h"
#include "Monster.h"

typedef struct element {
	SDL_Rect* rect;
	SDL_Renderer** render;
	SDL_Surface** surface;
	SDL_Texture** text;
	int height, y; /// can be of stage or some container
	const char* path;

}Element;

int up, down, left, right;
int variacaoSprite;
int variacaoRigth;


void initScreen(SDL_Window**, SDL_Renderer**,int,int);

void setElement(Element*);
#endif /* UTILS_H_ */
