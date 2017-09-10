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


int createElement(SDL_Renderer** render, SDL_Texture** text,Element* element,RootElement* root)
{

}