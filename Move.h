/*
 * Move.h
 *
 *  Created on: 17 de jul de 2017
 *      Author: Anderson
 */

#ifndef MOVE_H_
#define MOVE_H_

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "utils.h"

int up, down, left, right,run;
int variacaoSprite;
int variacaoRigth;


int move(SDL_Rect* ,int* ,PlayerConf* ,STAGE* ,MonsterInfo*,Element*);

int collisionCheck(PlayerConf*,STAGE*,MonsterInfo*);

void change(PlayerConf*, MonsterInfo*,STAGE*,int);

int battleConf(PlayerConf*,STAGE*,MonsterInfo*);
#endif /* MOVE_H_ */
