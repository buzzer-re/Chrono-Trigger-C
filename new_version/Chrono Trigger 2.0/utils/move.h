#include <SDL2/SDL.h>
#include "util.h"
#ifndef _MOVE_H
#define _MOVE_H

typedef struct action {
	int up;
	int down;
	int left;
	int right;
	int quit;
}Action;

int move_sprite(SDL_Rect*,Action*,SDL_Rect* background, RootElement* window);

int move_camera(SDL_Rect* sprite, SDL_Rect* background, Action*, RootElement* window);

int action(Action*); //get keyboard data

int cleanAction(Action*);
#endif