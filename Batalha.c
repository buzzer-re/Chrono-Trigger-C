/*
 * Batalha.c
 *
 *  Created on: 18 de jul de 2017
 *      Author: Anderson
 */

#include "Batalha.h"



int done = 0;
int contadorAtaque = 0;
int contSetup = 0;

void menuPlayer(SDL_Rect* menu,int width, int height,int flag){
	menu->h = (height/4) ;

	if(menu->w <= width - (width/10))
		menu->w += 25;
  SDL_Log("w -> %d\nw -> %d", menu->w, (width - (width/10)));
	menu->y = (height - menu->h) - menu->h/12 ;
	menu->x = (width - menu->w) / 2;
}

int setText(PlayerConf* player ,Text* text,int flag){
	/// status

	if(!flag){
		sprintf(player->textMenu,"%s\n%s%d\n%s%d",player->name,"HP: ",player->battle->hp,"MP: ",player->battle->mp);
		*text->surface = TTF_RenderText_Blended_Wrapped(text->font, player->textMenu, *text->color, 120);
	}else if(flag){
		sprintf(text->text,"%s\n%s\n%s", "Ataque", "Tecnica","Itens");
		*text->surface = TTF_RenderText_Blended_Wrapped(text->font, text->text, *text->color, 120);
	}

//	SDL_Log("surface %s", TTF_GetError());

	if(!*text->surface)
		return 0;

	*text->tex = SDL_CreateTextureFromSurface(*text->render, *text->surface);
//	SDL_Log(" text %s", TTF_GetError());

	if(!*text->tex)
		return 0;

	SDL_QueryTexture(*text->tex, NULL, NULL, &text->textRect->w, &text->textRect->h);

	SDL_FreeSurface(*text->surface);

//	SDL_Log("%s", TTF_GetError());
	return 1;
}

void setupInfo(Text* text,SDL_Rect* menu){
	text->textRect->w = (menu->w)/6;
	text->textRect->h = (menu->h);
	text->textRect->x = (menu->w - text->textRect->w) + text->textRect->w/2;
	text->textRect->y = (menu->y);

}

int battleSystem(SDL_Rect* menu,PlayerConf* player,MonsterInfo* monster,STAGE* stage, Text* options){
	if(player->battle->ataqueNormal == 1){		//ATAQUE NORMAL
		if(player->sprite->y > monster->monsterRect->y + (monster->monsterRect->h/2)){
			variacaoSprite++;
			player->flag = 1;
			player->up = 1;
			cameraAdjust(stage, player->sprite, monster,1);
			change(player, monster,stage, NULL);

		}
		else{
			player->flag = 6;
			player->up = 0;
			player->battle->readyAtaque = 1;
			change(player, monster,stage, NULL);
			contadorAtaque = 0;

			
		}
	}
	if(player->battle->adjust == 1){
		battleConf(player, stage, monster);
		if(!contadorAtaque){
			int hit = calculateHit(player);
			SDL_Log("Hit -> %d", hit);
			monster->battle->hp -= hit ;
			monster->battle->damage = 1;
			SDL_Log("Vida monstro -> %d ", monster->battle->hp);
			contadorAtaque = 1;
		}
		
		
	}

	if(monster->battle->hp <= 0 && player->battle->adjust != 1){
		player->ready = 0;
		player->battleState = 0;
		// player->up = 1;
		monster->battle->hp = 100;
		monster->battleState = 0;
		monster->battle->isDead = 1;
		player->state = 1;
		changeSprite(player,player->sprite,1);

	}

	return 0;
}

int calculateHit(PlayerConf* player){
	srand(time(NULL));
	int dano;
	int dado = (rand() % 6) + 1;
	if(!player->battle->critical)
		dano = (player->battle->atk * dado);
	else
		dano = (player->battle->atk * (dado*2));

	return dano;
}
void setupOptions(Text* text, SDL_Rect* menu,Element* choose,Element* avatar){
	SDL_Log("%d\n", menu->w);
  text->textRect->w = (menu->w)/6;
	text->textRect->h = (menu->h) ;
	text->textRect->x = (text->textRect->w);
	text->textRect->y = (menu->y);

	choose->rect->w = 40;
	choose->rect->h = 40;
  //choose->rect->w *= 2;
	//choose->rect->h *= 2;

	avatar->rect->w = (menu->w)/6;
	avatar->rect->h = (menu->h);
	//avatar->rect->w * 2;
	//avatar->rect->h * 2;

	if(!contSetup){
		choose->rect->y = text->textRect->y;
		contSetup = 1;
	}
	choose->rect->x = text->textRect->x - (text->textRect->x/2);
	choose->height = text->textRect->h;
	choose->y = text->textRect->y;

	avatar->rect->x = (text->textRect->w) * 4;
	avatar->rect->y = menu->y;
	SDL_Log("avatar %d", choose->rect->x);
}
