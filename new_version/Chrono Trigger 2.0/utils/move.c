#include "move.h"

#define SPEED 4
#define CHANGE 15


int accel = 1;

int move_sprite(SDL_Rect* sprite,SDL_Rect* element, Action* actions, SDL_Rect* background, RootElement* window, const char* type)
{
	int can_up = actions->up && sprite->y > 0 && (sprite->y > window->h / 2 || background->y >= 0); 
	
	int can_right = actions->right && (sprite->x < window->w - sprite->w) ;
	
	int can_left = actions->left && (sprite->x > 0);

	int can_down = actions->down && (sprite->y < window->h - sprite->h) && 
				((sprite->y < window->h/2) || (background->y <= window->h - background->h) );


	if(can_right && strcmp("element",type))
		sprite->x += SPEED * accel;	

	if(can_left && strcmp("element",type)) 
		sprite->x -= SPEED * accel;

	if(can_down && strcmp("element",type))  
		sprite->y += SPEED * accel;

	if(can_up && strcmp("element",type))
		sprite->y -= SPEED * accel;

	move_camera(sprite,element,background,actions,window,type);
}
/*
	move_sprite, receive a SDL_Rect with sprite, and one SDL_Rect with the other element in the screen
	such, moster or other thing, he make his is statemant, and send that to move_camera
	on move camera, he will incresse the velocity on element, but as the element was not use before
	he will always be in the opposite of the sprite!

*/

int move_camera(SDL_Rect* sprite,SDL_Rect* element, SDL_Rect* background, Action* action, RootElement* window, const char* type)
{

	int is_sprite = 1;
	if(action->right && window->w < (background->x + background->w) && sprite->x > window->w/2)
	{
		if(!strcmp("sprite",type))
		{
			background->x -= 2 * accel; 
		}
		sprite->x -= 2 * accel;
		element->x -= 2 * accel;
	}
	if(action->left && background->x < 0 && sprite->x < window->w/2)
	{
		if(!strcmp("sprite",type))
		{
			background->x += 2 * accel;
		}
		sprite->x += 2 * accel;
		element->x += 2 * accel;
	}

	if(action->up && background->y < 0 && sprite->y < window->h/2)
	{
		if(!strcmp("sprite",type))
		{
			background->y += SPEED * accel;
		}
		element->y += SPEED * accel;
	}
	if(action->down && (background->y > window->h - background->h) && sprite->y > window->h/2 )
	{
		if(!strcmp("sprite",type))
		{
			background->y -= SPEED * accel;	
		}
		element->y -= SPEED * accel;
		
	}
}


int action(Action* action)
{	
	SDL_Event event; /// catch events
	while(SDL_PollEvent(&event) != 0)
	{	
		switch(event.type)
		{
			case SDL_KEYDOWN:
			switch(event.key.keysym.scancode)
			{
				case SDL_SCANCODE_UP:
					action->up = 1;
					break;
				case SDL_SCANCODE_DOWN:
					action->down = 1;
					break;
				case SDL_SCANCODE_LEFT:
					action->left = 1;
					break;
				case SDL_SCANCODE_RIGHT:
					action->right = 1;
					break;
				case SDL_SCANCODE_Q:
					action->quit = 1;
					break;
				case SDL_SCANCODE_K:
					accel = 5;
					break;
			}break;

			case SDL_KEYUP:
			switch(event.key.keysym.scancode)
			{
				case SDL_SCANCODE_UP:
					action->up = 0;
					break;
				case SDL_SCANCODE_DOWN:
					action->down = 0;
					break;
				case SDL_SCANCODE_LEFT:
					action->left = 0;
					break;
				case SDL_SCANCODE_RIGHT:
					action->right = 0;
					break;
				case SDL_SCANCODE_K:
					accel = 1;
					break;
			}
		}
	}


	return 1;
}





int cleanAction(Action* action)
{
	action->right = 0;
	action->left = 0;
	action->up = 0;
	action->down = 0;
}