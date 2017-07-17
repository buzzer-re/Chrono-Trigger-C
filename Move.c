/*
 * Move.c
 *
 *  Created on: 17 de jul de 2017
 *      Author: Anderson
 */
#include "Move.h"
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


/// TODO ORGANIZAR MOVIMENTAÇÃO PARA TODOS ELEMENTOS! (Monstros e etc..)

int accel = 1;

void move(SDL_Rect* sprite,int* run,PlayerConf* conf,STAGE* stage_conf)
{
	/*
	 * 	flag 1 -> crono
	 * 	flag 2 -> marle
	 * 	flag 3 -> lucca
	 * */
	SDL_Event event;
	if(variacaoSprite > 2000)
		variacaoSprite = 0;

	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode){
			case SDL_SCANCODE_UP:
				if(!conf->battleState){
					conf->up = 1;
					up = 1;
				}
				break;
			case SDL_SCANCODE_LEFT:
				if(!conf->battleState){
					conf->left = 1;
					left = 1;
				}
				break;
			case SDL_SCANCODE_RIGHT:
				if(!conf->battleState){
					conf->rigth = 1;
					right = 1;
				}
				break;
			case SDL_SCANCODE_DOWN:
				if(!conf->battleState){
					conf->down = 1;
					down = 1;
				}
				break;
			case SDL_SCANCODE_Q:
				*run = 0;
				break;
			case SDL_SCANCODE_K:
				if(!conf->battleState){
					accel = 30;
				}
				break;
			case SDL_SCANCODE_B:
				if(conf->battleState)
					conf->battleState = 0;
				else
					conf->battleState = 1;
				break;
			}break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode){
				case SDL_SCANCODE_UP:
					if(!conf->battleState){
						up = 0;
						conf->up = 0;
						conf->numSprite =0;
						conf->state = 1;
						changeSprite(conf, sprite, 1);
					}

					break;
				case SDL_SCANCODE_LEFT:
					if(!conf->battleState){
						conf->left = 0;
						left = 0;
						conf->numSprite =0;
						conf->state = 2;
						changeSprite(conf, sprite, 1);
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if(!conf->battleState){
						conf->rigth = 0;
						conf->numSprite = 0;
						conf->state = 3;
						changeSprite(conf, sprite, 1);
						right = 0;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if(!conf->battleState){
						conf->down = 0;
						conf->numSprite = 0;
						conf->state = 4;
						changeSprite(conf, sprite, 1);
						down = 0;
					}
					break;
				case SDL_SCANCODE_K:
					accel = 1;
					break;
				}break;
		}
	}

	if(up && !conf->battleState){
		variacaoSprite++;
		if(variacaoSprite % TROCA == 0){
			conf->numSprite++;
			if(conf->numSprite > 6)
				conf->numSprite = 1;
			changeSprite(conf,sprite,0);
		}
		if(sprite->y < stage_conf->heigth/2){
			if(stage_conf->stage->y < 1)
				stage_conf->stage->y += STAGE_VEL + SPEED * accel;


			else{
				if(sprite->y > 0)
					sprite->y -= SPEED + STAGE_VEL * accel;
			}
		}else
			sprite->y -= SPEED + STAGE_VEL * accel;

		SDL_Log("%d", sprite->y);
	}

	if(down && !conf->battleState){
		variacaoSprite++;
		if(variacaoSprite % TROCA == 0){
			conf->numSprite++;
			if(conf->numSprite > 8)
				conf->numSprite = 1;
			changeSprite(conf, sprite,0);
			SDL_Log("Sprite num -> %d", conf->numSprite);
		}
		if(sprite->y > stage_conf->heigth/2){
			if(stage_conf->stage->y > stage_conf->limitY)
				stage_conf->stage->y -= STAGE_VEL + SPEED * accel;
			else
				if(sprite->y < stage_conf->heigth - sprite->h)
					sprite->y += SPEED + STAGE_VEL* accel;
		}else{
			sprite->y += SPEED + STAGE_VEL* accel;
		}
		SDL_Log("%d", sprite->y);
	}

	if(left && !conf->battleState){				///TODO dar uma olhada dps
		variacaoSprite++;
		if(variacaoSprite % TROCA == 0){
			conf->numSprite++;
			if(conf->numSprite > 6)
				conf->numSprite = 1;
			changeSprite(conf, sprite, 0);
		}
		if(sprite->x < stage_conf->width/2){
			if(stage_conf->stage->x < 0)
				stage_conf->stage->x += STAGE_VEL + SPEED* accel;
			else
				if(sprite->x > 0)
					sprite->x -= SPEED + STAGE_VEL* accel;
		}else{
			sprite->x -= SPEED + STAGE_VEL* accel;
		}
		SDL_Log("%d", stage_conf->stage->x);

	}

	if(right && !conf->battleState){
		variacaoSprite++;
		if(variacaoSprite % TROCA == 0){
			conf->numSprite++;
			if(conf->numSprite > 6)
				conf->numSprite = 1;
			changeSprite(conf, sprite, 0);
		}
		if(sprite->x > stage_conf->width/2){
			if(stage_conf->limitX + MARGEM_ERRO <= ((stage_conf->stage->w + stage_conf->stage->x)))
				stage_conf->stage->x -= STAGE_VEL + SPEED* accel;
			else{
				if(sprite->x < stage_conf->width - sprite->w)
					sprite->x += SPEED + STAGE_VEL* accel;
			}
		}else{
			sprite->x += SPEED + STAGE_VEL* accel;
			variacaoRigth += SPEED + STAGE_VEL* accel;

		}

	}

	if(conf->battleState){
		variacaoSprite++;
		if(variacaoSprite % (TROCA + 2) == 0){
			conf->numSprite++;
			if(conf->numSprite > 4){
				conf->numSprite = 4;
				battleState(conf);
			}

			changeSprite(conf, sprite, 0);
		}
		battleState(conf);
	}
	SDL_Delay(6);
}
