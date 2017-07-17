/*
 * Player.c
 *
 *  Created on: 13 de jul de 2017
 *      Author: Anderson
 */


#include "Player.h"
#include "Stage.h"
#include "Monster.h"
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define SPEED 2
#define TROCA 6
#define STAGE_VEL 1
#define MARGEM_ERRO 10
//
//int accel = 1;

int setupSprite(PlayerConf* conf,SDL_Rect* spriteRect)
{

	char* path;
	variacaoSprite = 0;
	variacaoRigth = 0;
	if(!strcmp(conf->name,"crono") && conf->start != 1){
		path = "Resourcers/cronoNormal1.png";
		conf->pathSprite = malloc(sizeof(char) * 40);

		conf->up = conf->down = conf->left = conf->rigth = 0;
		spriteRect->x = 400;
		spriteRect->y = 500;

		up = down = left = right = 0;
	}

	*conf->surface = IMG_Load(path);
	conf->start = 1;
	conf->state = 1;
	if(!*conf->surface)
		return 0;
	*conf->tex = SDL_CreateTextureFromSurface(*conf->render, *conf->surface);
	if(!*conf->tex)
		return 0;
	SDL_QueryTexture(*conf->tex, NULL, NULL, &spriteRect->w, &spriteRect->h);
	spriteRect->w *= 3;
	spriteRect->h *= 3;
	SDL_FreeSurface(*conf->surface);
	conf->battleState = 0;

	conf->battle = (PlayerBattle*) malloc(sizeof(PlayerBattle) * 50);
	conf->battle->hp = 100;
	conf->battle->mp = 120;
	conf->battle->atk = 15;
	conf->battle->def = 20;

	return 1;
}


//void move(SDL_Rect* sprite,int* run,PlayerConf* conf,STAGE* stage_conf)
//{
//	/*
//	 * 	flag 1 -> crono
//	 * 	flag 2 -> marle
//	 * 	flag 3 -> lucca
//	 * */
//	SDL_Event event;
//	if(variacaoSprite > 2000)
//		variacaoSprite = 0;
//
//	while(SDL_PollEvent(&event) != 0)
//	{
//		switch(event.type){
//		case SDL_KEYDOWN:
//			switch(event.key.keysym.scancode){
//			case SDL_SCANCODE_UP:
//				if(!conf->battleState){
//					conf->up = 1;
//					up = 1;
//				}
//				break;
//			case SDL_SCANCODE_LEFT:
//				if(!conf->battleState){
//					conf->left = 1;
//					left = 1;
//				}
//				break;
//			case SDL_SCANCODE_RIGHT:
//				if(!conf->battleState){
//					conf->rigth = 1;
//					right = 1;
//				}
//				break;
//			case SDL_SCANCODE_DOWN:
//				if(!conf->battleState){
//					conf->down = 1;
//					down = 1;
//				}
//				break;
//			case SDL_SCANCODE_Q:
//				*run = 0;
//				break;
//			case SDL_SCANCODE_K:
//				if(!conf->battleState){
//					accel = 30;
//				}
//				break;
//			case SDL_SCANCODE_B:
//				if(conf->battleState)
//					conf->battleState = 0;
//				else
//					conf->battleState = 1;
//				break;
//			}break;
//			case SDL_KEYUP:
//				switch(event.key.keysym.scancode){
//				case SDL_SCANCODE_UP:
//					if(!conf->battleState){
//						up = 0;
//						conf->up = 0;
//						conf->numSprite =0;
//						conf->state = 1;
//						changeSprite(conf, sprite, 1);
//					}
//
//					break;
//				case SDL_SCANCODE_LEFT:
//					if(!conf->battleState){
//						conf->left = 0;
//						left = 0;
//						conf->numSprite =0;
//						conf->state = 2;
//						changeSprite(conf, sprite, 1);
//					}
//					break;
//				case SDL_SCANCODE_RIGHT:
//					if(!conf->battleState){
//						conf->rigth = 0;
//						conf->numSprite = 0;
//						conf->state = 3;
//						changeSprite(conf, sprite, 1);
//						right = 0;
//					}
//					break;
//				case SDL_SCANCODE_DOWN:
//					if(!conf->battleState){
//						conf->down = 0;
//						conf->numSprite = 0;
//						conf->state = 4;
//						changeSprite(conf, sprite, 1);
//						down = 0;
//					}
//					break;
//				case SDL_SCANCODE_K:
//					accel = 1;
//					break;
//				}break;
//		}
//	}
//
//	if(up && !conf->battleState){
//		variacaoSprite++;
//		if(variacaoSprite % TROCA == 0){
//			conf->numSprite++;
//			if(conf->numSprite > 6)
//				conf->numSprite = 1;
//			changeSprite(conf,sprite,0);
//		}
//		if(sprite->y < stage_conf->heigth/2){
//			if(stage_conf->stage->y < 1)
//				stage_conf->stage->y += STAGE_VEL + SPEED * accel;
//
//
//			else{
//				if(sprite->y > 0)
//					sprite->y -= SPEED + STAGE_VEL * accel;
//			}
//		}else
//			sprite->y -= SPEED + STAGE_VEL * accel;
//
//		SDL_Log("%d", sprite->y);
//	}
//
//	if(down && !conf->battleState){
//		variacaoSprite++;
//		if(variacaoSprite % TROCA == 0){
//			conf->numSprite++;
//			if(conf->numSprite > 8)
//				conf->numSprite = 1;
//			changeSprite(conf, sprite,0);
//			SDL_Log("Sprite num -> %d", conf->numSprite);
//		}
//		if(sprite->y > stage_conf->heigth/2){
//			if(stage_conf->stage->y > stage_conf->limitY)
//				stage_conf->stage->y -= STAGE_VEL + SPEED * accel;
//			else
//				if(sprite->y < stage_conf->heigth - sprite->h)
//					sprite->y += SPEED + STAGE_VEL* accel;
//		}else{
//			sprite->y += SPEED + STAGE_VEL* accel;
//		}
//		SDL_Log("%d", sprite->y);
//	}
//
//	if(left && !conf->battleState){				///TODO dar uma olhada dps
//		variacaoSprite++;
//		if(variacaoSprite % TROCA == 0){
//			conf->numSprite++;
//			if(conf->numSprite > 6)
//				conf->numSprite = 1;
//			changeSprite(conf, sprite, 0);
//		}
//		if(sprite->x < stage_conf->width/2){
//			if(stage_conf->stage->x < 0)
//				stage_conf->stage->x += STAGE_VEL + SPEED* accel;
//			else
//				if(sprite->x > 0)
//					sprite->x -= SPEED + STAGE_VEL* accel;
//		}else{
//			sprite->x -= SPEED + STAGE_VEL* accel;
//		}
//		SDL_Log("%d", stage_conf->stage->x);
//
//	}
//
//	if(right && !conf->battleState){
//		variacaoSprite++;
//		if(variacaoSprite % TROCA == 0){
//			conf->numSprite++;
//			if(conf->numSprite > 6)
//				conf->numSprite = 1;
//			changeSprite(conf, sprite, 0);
//		}
//		if(sprite->x > stage_conf->width/2){
//			if(stage_conf->limitX + MARGEM_ERRO <= ((stage_conf->stage->w + stage_conf->stage->x)))
//				stage_conf->stage->x -= STAGE_VEL + SPEED* accel;
//			else{
//				if(sprite->x < stage_conf->width - sprite->w)
//					sprite->x += SPEED + STAGE_VEL* accel;
//			}
//		}else{
//			sprite->x += SPEED + STAGE_VEL* accel;
//			variacaoRigth += SPEED + STAGE_VEL* accel;
//
//		}
//
//	}
//
//	if(conf->battleState){
//		variacaoSprite++;
//		if(variacaoSprite % (TROCA + 2) == 0){
//			conf->numSprite++;
//			if(conf->numSprite > 4){
//				conf->numSprite = 4;
//				battleState(conf);
//			}
//
//			changeSprite(conf, sprite, 0);
//		}
//		battleState(conf);
//	}
//	SDL_Delay(6);
//}

void changeSprite(PlayerConf* conf,SDL_Rect* sprite_rect,int reset)
{	/*

		1 - front
		2 - left        <---- PADRÃO
		3 - right
		4 - back
 */

	if(reset){
		if(!strcmp(conf->name,"crono")){
			switch(conf->state){
			case 1: *conf->surface = IMG_Load("Resourcers/cronoNormal1.png");break;
			case 2: *conf->surface = IMG_Load("Resourcers/cronoNormalLeft1.png");break;
			case 3: *conf->surface = IMG_Load("Resourcers/cronoNormalRight1.png");break;
			case 4: *conf->surface = IMG_Load("Resourcers/cronoNormalDown1.png");break;
			}
		}
	}else{


		if(conf->up)
			sprintf(conf->pathSprite, "%s%d%s", "Resourcers/cronoWalkFront",conf->numSprite, ".png");

		if(conf->left)
			sprintf(conf->pathSprite, "%s%d%s", "Resourcers/cronoWalkLeft",conf->numSprite, ".png");

		if(conf->rigth)
			sprintf(conf->pathSprite, "%s%d%s", "Resourcers/cronoWalkRight",conf->numSprite, ".png");

		if(conf->down)
			sprintf(conf->pathSprite, "%s%d%s", "Resourcers/cronoWalkDown", conf->numSprite, ".png");

		//battle mode

		if(conf->battleState && conf->state)
			sprintf(conf->pathSprite, "%s%d%s","Resourcers/battle",conf->numSprite,".png");

		else if(conf->battleState && conf->state == 2)
			sprintf(conf->pathSprite,"%s%d%s","Resourcers/battleLeft",conf->numSprite,".png");

		*conf->surface = IMG_Load(conf->pathSprite);
	}

	if(!*conf->surface)
		SDL_Log("erro aqui ó %s", SDL_GetError());

	*conf->tex = SDL_CreateTextureFromSurface(*conf->render, *conf->surface );
	if(!*conf->tex)
	{
		SDL_Log("%s", SDL_GetError());
	}
	SDL_QueryTexture(*conf->tex, NULL, NULL, &sprite_rect->w, &sprite_rect->h);
	sprite_rect->w *= 3;
	sprite_rect->h *= 3;
	SDL_FreeSurface(*conf->surface);
	//	SDL_Log("Possivel erro -> %s", SDL_GetError());
}

void battleState(PlayerConf* player){
	//	if(variacaoSprite);
	SDL_Log("essa briga, tomate!");
}
