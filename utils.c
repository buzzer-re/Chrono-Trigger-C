#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

void initScreen(SDL_Window** window, SDL_Renderer** render,int width, int heigth){
	*window = SDL_CreateWindow("Chrono Trigger engine test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,heigth,0);
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

/// function to set any type of image, passing struct Element.
void setElement(Element* element){
	*element->surface = IMG_Load(element->path);
	if(!*element->surface)
	{
		SDL_Log("Error in open surface %s", SDL_GetError());
	}

	*element->text = SDL_CreateTextureFromSurface(*element->render, *element->surface);
	if(!*element->text)
	{
		SDL_Log("Error in create texture! %s ", SDL_GetError());
	}
	SDL_QueryTexture(*element->text, NULL, NULL, &element->rect->w, &element->rect->y);
	SDL_FreeSurface(*element->surface);

	SDL_Log("Element created!");
}
