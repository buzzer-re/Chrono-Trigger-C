#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

void initScreen(SDL_Window** window, SDL_Renderer** render,int width, int heigth){
	*window = SDL_CreateWindow("Chrono Trigger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,heigth,0);
	if(!*window)
	{
		SDL_Log("Error while create window! %s", SDL_GetError());
		exit(1);
	}
	*render = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!*render)
	{
		SDL_Log("Error while create render! %s", SDL_GetError());
		SDL_DestroyWindow(*window);
		exit(1);
	}
}
