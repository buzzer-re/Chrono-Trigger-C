#include <SDL2/SDL.h>


#include "../elements/player.h"
#include "../elements/monster.h"
#include "../elements/background.h"

#ifndef _UTIL_H
#define _UTIL_H

typedef struct element
{
	SDL_Renderer** render;
	SDL_Texture** text;
	SDL_Surface** surface;
	SDL_Rect* rect;
	int x;
	int y;
	int width;
	int heigth;
	const char* surface_path;
}Element;


/// Element who contains the important info of game

typedef struct root
{
	int w;
	int h;
}RootElement;

typedef struct scenario {
	/// contain, all info of scene
	Player* player;
	Monster* monster;
	Background* background;
	RootElement* root_element;
}Scenario;


int createWindow(SDL_Window**,SDL_Renderer**, const char*,RootElement*);

int createElement(Element*);
#endif
