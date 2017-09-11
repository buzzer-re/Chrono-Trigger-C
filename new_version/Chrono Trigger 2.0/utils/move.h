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

int move_sprite(SDL_Rect* element,SDL_Rect* other, Action* actions, SDL_Rect* background, RootElement* window, const char* type,int flag);

int move_camera(SDL_Rect* sprite,SDL_Rect* element, SDL_Rect* background, Action*, RootElement* window,const char*);

int move_battle(Scenario* scene, Action* actions);

int action(Action*); //get keyboard data

int cleanAction(Action*);
#endif