#include "util.h"


int createWindow(SDL_Window** window, SDL_Renderer** render, const char* title,RootElement* root)
{
	*window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		root->w,
		root->h,
		0
	);

	if(!*window)
	{
		/// error in window creation
		return 0;
	}

	unsigned int render_flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	*render = SDL_CreateRenderer(*window,-1, render_flags);

	if(!*render)
	{
		/// error in creation of renderer
		return 0;
	}
	return 1;
}


int createElement(Element* element)
{
	*element->surface = IMG_Load(*element->surface_path);

	if(!*element->surface)
	{
		SDL_Log("Cant get surface! %s", SDL_GetError());
		return 0;
	}

	*element->text = SDL_CreateTextureFromSurface(*element->render, *element->surface);

	if(!*element->text)
	{
		SDL_Log("Error in create element texture! %s", SDL_GetError());
		return 0;
	}

	SDL_QueryTexture(element->text,NULL,NULL, &element->rect->w, &element->rect->h);

	SDL_FreeSurface(*element->surface);

	return 1;
}