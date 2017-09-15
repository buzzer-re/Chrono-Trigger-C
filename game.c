/*
 * game.c

 *
 *  Chrono trigger simple system in C/SDL
 */

#include <stdio.h>
#include <time.h>

/// SDL APIS
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

/// My API's
#include "utils.h"
#include "Player.h"
#include "Stage.h"
#include "Monster.h"
#include "Move.h"
#include "Batalha.h"

#define WIDTH_SCREEN 1000
#define HEIGH_SCREEN 700
#define FPS 6


int main(int argc, char **argv) {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
		SDL_Log("Error in init! %s", SDL_GetError());
		return -1;
	}

	if(TTF_Init() < 0){
		SDL_Log("Error in init fonts! %s", TTF_GetError());
		return -1;
	}

	int battle = 0;
	int contMusica = 1;
	int contSetup = 0;

	if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		SDL_Log("%s", SDL_GetError());

	Mix_Music* bgm = Mix_LoadMUS("Sounds/black.mp3");
	Mix_Music* battleSong = Mix_LoadMUS("Sounds/crossBoss.mp3");

	SDL_Window* window;
	SDL_Renderer* render;

	initScreen(&window,&render, WIDTH_SCREEN,HEIGH_SCREEN);
	PlayerConf* crono_conf;
	crono_conf = (PlayerConf*) malloc(sizeof(PlayerConf) * 50);
	STAGE stage_conf;
	SDL_Rect crono;
	SDL_Surface* surface;
	SDL_Texture* tex;
	crono_conf->render = &render;
	crono_conf->surface = &surface;
	crono_conf->tex = &tex;
	crono_conf->name = "Crono";
	crono_conf->sprite = &crono;
	//stage
	SDL_Rect stageRect;
	SDL_Surface* surfaceStage;
	SDL_Texture* texturaStage;

	stage_conf.render = &render;
	stage_conf.stage = &stageRect;
	stage_conf.tex = &texturaStage;
	stage_conf.surface = &surfaceStage;
	stage_conf.limitX = WIDTH_SCREEN;
	stage_conf.width = WIDTH_SCREEN;
	stage_conf.heigth = HEIGH_SCREEN;
	setupStage(&stage_conf);


	// Monster

	MonsterInfo* monster = (MonsterInfo*) malloc(sizeof(MonsterInfo) * 50);
	SDL_Rect monsterRect;
	SDL_Surface* monsterSurface;
	SDL_Texture* monsterTex;

	monster->render = &render;
	monster->surface = &monsterSurface;
	monster->tex = &monsterTex;
	monster->monsterRect = &monsterRect;
	monster->stage_conf = &stage_conf;
	monster->pathSprite = malloc(sizeof(char) * 40);
	monster->x = 448; 
	monster->y = -100;
	setupMonster(monster);

	SDL_Rect menu;
	SDL_Rect optionsRect;
	Text* text = (Text*) malloc(sizeof(Text) * 50);
	Text* options = (Text*) malloc(sizeof(Text) * 50);
	text->font = TTF_OpenFont("Resourcers/Chrono.ttf", 35);
	SDL_Color color = {255,255,255};
	SDL_Surface* textSurface;
	SDL_Texture* textTex;
	SDL_Rect textRect;
	text->render = &render;
	text->surface = &textSurface;
	text->tex = &textTex;
	text->color = &color;
	text->textRect = &textRect;

	options->font = text->font;
	options->render = &render;
	options->surface = &textSurface;
	options->tex = &textTex;
	options->color = &color;
	options->textRect = &optionsRect;
	options->text = malloc(sizeof(char) * 50);

	/// Menu
	SDL_Rect optionBox;
	SDL_Texture* cursorTex;
	Element* cursor = (Element*) malloc(sizeof(Element) * 50);
	cursor->render = &render;
	cursor->surface = &surface;
	cursor->rect =  &optionBox;
	cursor->path = "Resourcers/cursor.png";
	cursor->text = &cursorTex;
	setElement(cursor);

	SDL_Rect imageBox;
	SDL_Texture* imageText;
	Element* avatar = (Element*) malloc(sizeof(Element) * 50);
	avatar->render = &render;
	avatar->surface = &surface;
	avatar->rect = &imageBox;
	avatar->path = "Resourcers/CronoStatus.png";
	avatar->text = &imageText;
	setElement(avatar);

	if(!setupSprite(crono_conf, &crono))
	{
		SDL_Log("Error s %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);
		return -1;
	}

	int run = 1;
	Mix_PlayMusic(bgm, -1);


	while(run){
		SDL_RenderClear(render);
		SDL_SetRenderDrawColor(render,255, 255, 255, 255);
		SDL_RenderCopy(render, texturaStage, NULL, &stageRect);
		if(!monster->battle->isDead){
			SDL_RenderCopy(render,monsterTex,NULL,&monsterRect);
			moveMonster(monster);

		}
		SDL_RenderCopy(render, tex, NULL, &crono);

		collisionCheck(crono_conf, &stage_conf, monster);
		if(move(&crono,&run,crono_conf,&stage_conf,monster,cursor)){
			if(!battle){
				Mix_PlayMusic(battleSong, -1);
				battle = 1;
			}
			
			SDL_SetRenderDrawColor(render, 1, 1, 71, 255);
			menuPlayer(&menu, WIDTH_SCREEN, HEIGH_SCREEN,1);
			SDL_RenderFillRect(render,&menu);
			setText(crono_conf,text,0);
			setupInfo(text,&menu);
			SDL_SetRenderDrawColor(render,255, 255, 255, 255);
			SDL_RenderCopy(render, textTex, NULL, &textRect);
			battleSystem(&menu, crono_conf, monster, &stage_conf, options);
			changeMonster(monster);
			setText(crono_conf,options,1);
			setupOptions(text, &menu,cursor,avatar);
			if(crono_conf->battle->ataqueNormal != 1){
				SDL_RenderCopy(render, textTex, NULL, &textRect);			
				SDL_RenderCopy(render, cursorTex, NULL, &optionBox);			
			}
			SDL_RenderCopy(render, imageText, NULL, &imageBox);
		}else{
			if(battle) Mix_PlayMusic(bgm,-1);
			battle = 0;
		}

		SDL_SetRenderDrawColor(render,0, 0, 0, 255);
		SDL_RenderPresent(render);
		SDL_Delay(FPS);

	}

	Mix_FreeMusic(bgm);
	Mix_FreeMusic(battleSong);
	Mix_Quit();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	
	//	free(crono_conf->battle);
	//	free(crono_conf->pathSprite);
	//	free(crono_conf->name);
	//	free(crono_conf);
	return 1;
}
