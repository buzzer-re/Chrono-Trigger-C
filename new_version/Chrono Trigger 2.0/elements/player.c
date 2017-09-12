#include "player.h"
#include <string.h>
#include <stdio.h>

#define CHANGE 6
int sprite_change = 0;

int set_sprite(Player* sprite, int flag)
{
	if(!strcmp(sprite->name,"crono"))
	{
		sprintf(sprite->sprite_img,"%s","resourcers/cronoNormal1.png");
	}

	if(!flag)
		*sprite->surface = IMG_Load(sprite->sprite_img);

	else if(flag && !sprite->action && !sprite->battle.inBattle)
	{
		if(!sprite->battle.inBattle)
		{
			switch(sprite->state)
			{
				case 1:	sprintf(sprite->sprite_img,"%s%s%s","resourcers/",sprite->name,"Normal1.png");break;
				case 2: sprintf(sprite->sprite_img,"%s%s%s","resourcers/",sprite->name,"NormalLeft1.png");break;
				case 3: sprintf(sprite->sprite_img,"%s%s%s","resourcers/",sprite->name,"NormalRight1.png");break;
				case 4: sprintf(sprite->sprite_img,"%s%s%s","resourcers/",sprite->name,"NormalDown1.png");break;
			}
		}
		else
		{
			switch(sprite->state)
			{
				case 1:	sprintf(sprite->sprite_img,"%s%s%s","resourcers/",sprite->name,"BattleFront1.png");break;
				case 2: sprintf(sprite->sprite_img,"%s%s%s","resourcers/",sprite->name,"BattleFront4.png");break;
				case 3: sprintf(sprite->sprite_img,"%s%s%s","resourcers/",sprite->name,"NormalRight1.png");break;
				case 4: sprintf(sprite->sprite_img,"%s%s%s","resourcers/",sprite->name,"NormalDown1.png");break;
			}
		}

		*sprite->surface = IMG_Load(sprite->sprite_img);
	}

	if(!*sprite->surface)
	{
		SDL_Log("Error in load image! %s", SDL_GetError());
		return 0;
	}
	//// Some error ocour here!
	*sprite->text = SDL_CreateTextureFromSurface(*sprite->render, *sprite->surface);

	if(!*sprite->text)
	{
		SDL_Log("Error in load texture! %s ", SDL_GetError());
		return 0;
	}

	SDL_QueryTexture(*sprite->text,NULL,NULL,&sprite->player_rect->w,&sprite->player_rect->h);

	SDL_FreeSurface(*sprite->surface);


	// sprite->player_rect->w *= sprite->info.w;
	// sprite->player_rect->h *= sprite->info.h;
	// sprite->player_rect->x = sprite->info.x;
	// sprite->player_rect->y = sprite->info.y;


	sprite->player_rect->w *= 3;
	sprite->player_rect->h *= 3;

	if(!flag){
		sprite->player_rect->x = 400;
		sprite->player_rect->y = 500;
	}
	return 1;
}


void change_sprite(Player* sprite)
{
	/*
		States
		1 - Front
		2 - Left
		3 - Rigth
		4 - Down
	*/
	sprite->cont++;
	if(sprite->cont % CHANGE == 0)  /// sprite change, same for battle
	{
		sprite_change++;
		if(!sprite->battle.inBattle)
		{
			if(sprite_change > sprite->sprite_img_limit)
				sprite_change = 1;
			switch(sprite->state)
			{

				case 1:sprintf(sprite->sprite_img,"%s%s%s%d%s","resourcers/",sprite->name,"WalkFront",sprite_change,".png");break;
				case 2:sprintf(sprite->sprite_img,"%s%s%s%d%s","resourcers/",sprite->name,"WalkLeft",sprite_change,".png");break;
				case 3:sprintf(sprite->sprite_img,"%s%s%s%d%s","resourcers/",sprite->name,"WalkRight",sprite_change,".png");break;
				case 4:sprintf(sprite->sprite_img,"%s%s%s%d%s","resourcers/",sprite->name,"WalkDown",sprite_change,".png");break;
			}
		}
		else
		{
			if(sprite_change > 4)
				sprite_change = 4;

			switch(sprite->state)
			{
				case 1:sprintf(sprite->sprite_img,"%s%s%s%d%s","resourcers/",sprite->name,"BattleFront",sprite_change,".png");break;
				case 2:sprintf(sprite->sprite_img,"%s%s%s%d%s","resourcers/",sprite->name,"BattleLeft",sprite_change,".png");break;
				case 3:sprintf(sprite->sprite_img,"%s%s%s%d%s","resourcers/",sprite->name,"BattleRight",sprite_change,".png");break;
				case 4:sprintf(sprite->sprite_img,"%s%s%s%d%s","resourcers/",sprite->name,"BattleDown",sprite_change,".png");break;
			}
		}

		*sprite->surface = IMG_Load(sprite->sprite_img);
		set_sprite(sprite,1);
	}
}
