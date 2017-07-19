/*
 * Batalha.c
 *
 *  Created on: 18 de jul de 2017
 *      Author: bigboss
 */

#include "Batalha.h"



int done = 0;
void menuPlayer(SDL_Rect* menu,int width, int height,int flag){
	menu->h = (height/4) ;

	if(menu->w <= width - (width/10))
		menu->w += 25;

	menu->y = (height - menu->h) - menu->h/12 ;
	menu->x = (width - menu->w) / 2;
}

int setText(PlayerConf* player ,Text* text){
	/// status

	if(player != NULL){
		sprintf(player->textMenu,"%s\n%s%d\n%s%d",player->name,"HP: ",player->battle->hp,"MP: ",player->battle->mp);
		*text->surface = TTF_RenderText_Blended_Wrapped(text->font, player->textMenu, *text->color, 120);
	}else{
		sprintf(text->text,"%s\n%s\n%s", "Ataque", "Técnica","Itens");
		*text->surface = TTF_RenderText_Blended_Wrapped(text->font, text->text, *text->color, 120);
	}


	SDL_Log("surface %s", TTF_GetError());
	if(!*text->surface)
		return 0;

	*text->tex = SDL_CreateTextureFromSurface(*text->render, *text->surface);
	SDL_Log(" text %s", TTF_GetError());

	if(!*text->tex)
		return 0;

	SDL_QueryTexture(*text->tex, NULL, NULL, &text->textRect->w, &text->textRect->h);

	SDL_FreeSurface(*text->surface);



	SDL_Log("%s", TTF_GetError());
	return 1;
}

void setupInfo(Text* text,SDL_Rect* menu){

	text->textRect->w = (menu->w)/6;
	text->textRect->h = (menu->h);
	text->textRect->x = (menu->w - text->textRect->w) + text->textRect->w/2;
	text->textRect->y = (menu->y);

}

int battleSystem(SDL_Rect* menu, PlayerConf* player, Text* options){
	//	*options->surface = TTF_RenderText_Blended_Wrapped(options->font, player->textMenu, *options->color, 120);
	//		SDL_Log("surface %s", TTF_GetError());
	//		if(!*options->surface)
	//			return 0;
	//
	//		*options->tex = SDL_CreateTextureFromSurface(*options->render, *options->surface);
	//		SDL_Log(" text %s", TTF_GetError());
	//		if(!*options->tex)
	//			return 0;
	//
	//		SDL_QueryTexture(*options->tex, NULL, NULL, &options->textRect->w, &options->textRect->h);
	//
	//		SDL_FreeSurface(*options->surface);
	return 0;
}
