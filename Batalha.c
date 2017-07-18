/*
 * Batalha.c
 *
 *  Created on: 18 de jul de 2017
 *      Author: bigboss
 */

#include "Batalha.h"



int done = 0;
void menuPlayer(PlayerConf* player,MonsterInfo* monster,SDL_Rect* menu,int width, int height,Text* text){
//	char *nome = malloc(255);
	menu->x = (width - menu->w) / 2;
	menu->y = (height - menu->h) - menu->h/12 ;
	/// TODO ORGANIZAR ISSO!

//	SDL_Log("%s", nome);
	if(menu->h < height/4)
		menu->h += 25;
	else
		done += 1;;
	if(menu->w < width - (width/10))
		menu->w += 25;
	else
		done+=1;

	if(done > 1){
		/// Define text
//		sprintf(nome,"%s\n%s%d\n%s%d", player->name, "HP: ", player->battle->hp,"MP: ", player->battle->mp);
		SDL_Color color = {255,255,255};
		*text->font = TTF_OpenFont("Resourcers/Chrono.ttf", 35);
		if(!*text->font){
			SDL_Log("Error in load fonts! %s ", SDL_GetError());

		}
		*text->surface = TTF_RenderText_Blended_Wrapped(*text->font, "Crono", color, 100);//(*text->font, nome, color);
		if(!*text->surface){
			SDL_Log("Error in load texture! %s ", SDL_GetError());
		}

		*text->tex = SDL_CreateTextureFromSurface(*text->render, *text->surface);

		SDL_FreeSurface(*text->surface);
		SDL_QueryTexture(*text->tex, NULL, NULL, &text->textRect->w, &text->textRect->h);

		text->textRect->x = 400 ;
		text->textRect->y = 500;
		SDL_Log("%s", SDL_GetError());
	}

//	free()
}
