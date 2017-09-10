#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef _BACKGROUND_H
#define _BACKGROUND_H



typedef struct background
{
	SDL_Renderer** render;
	SDL_Texture** text;
	SDL_Surface** surface;
	SDL_Rect* stage;
	int x;
	int y;
	int width;
	int heigth;
}Background;


int createStage(Background*);


#endif
