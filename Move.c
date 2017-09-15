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
#define TROCA 15
#define STAGE_VEL 1
#define MARGEM_ERRO 10

/// Global
int accel = 1;
int num = 1;
int contDown = 0, contUp = 0;
int action = 0;
int ataque_normal;
int tecnica;
int item;

int move(SDL_Rect* sprite,int* isGame,PlayerConf* conf,STAGE* stage_conf,MonsterInfo* monster,Element* cursor)
{
	/*
	 * 	flag 1 -> crono
	 * 	flag 2 -> marle
	 * 	flag 3 -> lucca
	 * */
	/// Menu Options
	ataque_normal = cursor->y;
	tecnica = cursor->y + cursor->height/3;
	item = cursor->y/5 + cursor->height * 3;
	//End menu options

	SDL_Event event;

	if(variacaoSprite > 2000)
		variacaoSprite = 0;

	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type){
		case SDL_QUIT: *isGame = 0; break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode){
			case SDL_SCANCODE_UP:
				if(!conf->battleState){
					conf->up = 1;

				}
				up = 1;
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

				}
				down = 1;
				break;
			case SDL_SCANCODE_Q:
				*isGame = 0;
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
			case SDL_SCANCODE_Z:
				run = 1;
				accel = 2;
				conf->run = 1;
				break;
			case SDL_SCANCODE_X:
				if(conf->battleState)
					action = 1;
				break;
			}break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode){
				case SDL_SCANCODE_UP:
					if(!conf->battleState){

						conf->up = 0;
						conf->numSprite =0;
						conf->state = 1;
						changeSprite(conf, sprite, 1);
					}
					up = 0;
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

					}
					down = 0;
					break;
				case SDL_SCANCODE_K:
					accel = 1;
					break;
				case SDL_SCANCODE_Z:
					run = 0;
					accel = 1;
					conf->run = 0;break;
				case SDL_SCANCODE_X:
					if(conf->battleState)
						action = 0;break;
				}break;
		}
	}
	/// velocity
		if(!conf->battleState) accel = 1;
	///
	///Menu Cursor

	if(up && conf->battleState){
		contUp++;
		if(contUp > 0 && contUp <= 3){
			switch(contUp){
			case 1: cursor->rect->y = cursor->y;break;
			case 2: cursor->rect->y = cursor->y/5 + cursor->height * 3;break;
			case 3: cursor->rect->y = cursor->y + cursor->height/3;break;
			}
			SDL_Delay(100);
		}else
			contUp = 0;

		SDL_Log("UP -> %d", contUp);
	}

	if(down && conf->battleState){
		contDown++;
		if(contDown > 0 && contDown <= 3){
			switch(contDown){
			case 1: cursor->rect->y = cursor->y + cursor->height/3;break;
			case 2: cursor->rect->y = cursor->y/5 + cursor->height * 3;break;
			case 3: cursor->rect->y = cursor->y;break;
			}
			SDL_Delay(100);
		}else
			contDown = 0;
//		SDL_Log("Down -> %d", contDown);
	}

	/// end menu cursor

	//Actions in battle
	if(action){
		if(cursor->rect->y == ataque_normal) // Se o cursor estiver na posição do ataque normal
			conf->battle->ataqueNormal = 1;
		if(cursor->rect->y == tecnica){
			//TODO
		}

		if(cursor->rect->y == item){
			//TODO
		}
	}

	//end actions in battle
	if(up && !conf->battleState){
		variacaoSprite++;
		change(conf, monster,stage_conf,NULL);
		cameraAdjust(stage_conf, sprite, monster,1);
//		SDL_Log("%d", sprite->y);
	}

	if((down && !conf->battleState)){
		variacaoSprite++;
		change(conf, monster,stage_conf,NULL);
		cameraAdjust(stage_conf, sprite, monster,2);
//		SDL_Log("%d", sprite->y);
	}

	if(left && !conf->battleState){
		variacaoSprite++;
		change(conf, monster,stage_conf,NULL);
		cameraAdjust(stage_conf, sprite, monster, 3);
//		SDL_Log("%d", stage_conf->stage->x);

	}

	if(right && !conf->battleState){
		variacaoSprite++;
		change(conf, monster,stage_conf,NULL);
		cameraAdjust(stage_conf, sprite, monster, 4);
	}

	if(conf->battleState){
		if(conf->ready){
			variacaoSprite++;
			change(conf, monster,stage_conf,NULL);
			return 1;
		}else
			battleConf(conf,stage_conf, monster);
	}

//	SDL_Log("Battle -> %d", conf->battleState);
	return 0;
}

int getTroca(PlayerConf* player){
	if(player->battle->ataqueNormal == 1 && !player->up){
		return 25;
	}


	if(player->run)
		return 6;

	if(player->ready)
		return 9;

	if(up || down || player->flag || player->flag == 2){
		if(player->battleState)
			return 6;
		if((up || down) && (left || right)){
			return 12;
		}
		else
			return 6;
	}

	return 6;
}

void change(PlayerConf* player, MonsterInfo* monster,STAGE* stage,int flag){
	int limit;
	int initialFantasy = 1;

	if(player->up ||player->flag)
		limit = 6;
	if(player->down || player->flag == 2)
		limit = 6;
	if(player->rigth || player->flag == 3)
		limit = 6;
	if(player->left || player->flag == 4)
		limit = 6;
	if(player->ready && !player->up){
		limit = 5;
		initialFantasy = 5;
	}

	if(player->run)
		limit = 7;

	if(player->flag == 6){
		limit = 2;
		initialFantasy = 1;
		variacaoSprite++;
	}
	if(variacaoSprite % getTroca(player) == 0){
		player->numSprite++;
		if(player->numSprite > limit){
			player->numSprite = initialFantasy;
		}
		if(player->flag == 6)
			player->battle->contadorAtaque++;

		if(player->battle->contadorAtaque > 2){
			player->battle->ataqueNormal = 0;
			player->battle->adjust = 1;
			player->battle->contadorAtaque = 0;
			player->battle->readyAtaque = 0;
			accel = 2;
		}

		changeSprite(player,player->sprite,0);

	}
}

int collisionCheck(PlayerConf* player,STAGE* stage, MonsterInfo* monster){

	SDL_Rect aux;

	if(SDL_IntersectRect(player->sprite, monster->monsterRect, &aux) == SDL_TRUE && !monster->battle->isDead){
		if(!player->battleState){
			player->numSprite = 0;

		}
		player->battleState = 1;
		monster->battleState = 1;
		return 1;
	}

	return 0;
}
int contDemage = 0;
int battleConf(PlayerConf* player,STAGE* stage, MonsterInfo* monster){
	if(player->sprite->x != monster->monsterRect->x){
		variacaoSprite++;
		if(player->sprite->x < monster->monsterRect->x){
			player->rigth = 1;
			change(player, monster,stage,4);
			cameraAdjust(stage,  player->sprite, monster, 4);
		}
		else{
			player->flag = 3;
			player->left = 1;
			change(player, monster,stage,3);
			cameraAdjust(stage,  player->sprite, monster, 3);
		}
	}

	else if(player->sprite->y > monster->monsterRect->y + (monster->monsterRect->h * 2) ){
		player->numSprite = 1;

		if(player->battle->adjust != 1)
			player->ready = 1;
		player->flag = 10;
		player->up = 0;
		player->left = 0;
		player->rigth= 0;
		player->down = 0;
		player->battle->adjust = 0;
	}
	else{
		variacaoSprite++;
		player->flag = 2;
		cameraAdjust(stage, player->sprite, monster,2);
		change(player, monster,stage, NULL);
		contDemage += 2;
		if(contDemage % 50 == 0){
			monster->battle->damage = 0;
			contDemage = 0;
		}
	}


	return 0;
}

int cameraAdjust(STAGE* stage_conf, SDL_Rect* sprite,MonsterInfo* monster, int flag){
	/*
	 * 		CAMERA CONTROL, A LOT OF CODE, BUT ITS SIMPLE! PLEASE DONT TOUCH!
	 * 				A little changes, signal and other stuff... used flags to
	 * 				know if camera is up, down, rigth or left!
	 *
	 *
	 *
	 *
	 * */

	if(flag == 1){ // UP
		if(sprite->y < stage_conf->heigth/2){
			if(stage_conf->stage->y < 1){
				stage_conf->stage->y += (SPEED + STAGE_VEL) * accel;
				monster->monsterRect->y += (SPEED + STAGE_VEL) * accel;
			}
			else{
				if(sprite->y > 0)
					sprite->y -= (SPEED + STAGE_VEL) * accel;
			}
		}else
			sprite->y -= (SPEED + STAGE_VEL) * accel;
	}


	if(flag == 2){  // DOWN
		if(sprite->y > stage_conf->heigth/2){
			if(stage_conf->stage->y > stage_conf->limitY){
				stage_conf->stage->y -= (SPEED + STAGE_VEL) * accel;
				monster->monsterRect->y -= (SPEED + STAGE_VEL) * accel;
			}
			else
				if(sprite->y < stage_conf->heigth - sprite->h)
					sprite->y += (SPEED + STAGE_VEL)* accel;
		}else{
			sprite->y += (SPEED + STAGE_VEL) * accel;
		}
	}

	if(flag == 3){ // left
		if(sprite->x < stage_conf->width/2){
			if(stage_conf->stage->x < 0){
				stage_conf->stage->x += (SPEED + STAGE_VEL)* accel;
				monster->monsterRect->x += (SPEED + STAGE_VEL) * accel;
			}
			else
				if(sprite->x > 0)
					sprite->x -= (SPEED + STAGE_VEL)* accel;
		}else{
			sprite->x -= (SPEED + STAGE_VEL)* accel;
		}
	}

	if(flag == 4){  /// RIGTH
		if(sprite->x > stage_conf->width/2){
			if(stage_conf->limitX + MARGEM_ERRO <= ((stage_conf->stage->w + stage_conf->stage->x))){
				stage_conf->stage->x -= (SPEED + STAGE_VEL)* accel;
				monster->monsterRect->x -= (SPEED + STAGE_VEL) * accel;
			}

			else{
				if(sprite->x < stage_conf->width - sprite->w)
					sprite->x += (SPEED + STAGE_VEL)* accel;
			}
		}else{
			sprite->x += (SPEED + STAGE_VEL)* accel;
			variacaoRigth += (SPEED + STAGE_VEL)* accel;
		}
	}
	return 0;
}
