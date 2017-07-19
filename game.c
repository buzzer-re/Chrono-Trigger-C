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

#define WIDTH_SCREEN 800
#define HEIGH_SCREEN 640
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


	if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		SDL_Log("%s", SDL_GetError());

	Mix_Music* bgm = Mix_LoadMUS("Sounds/black.mp3");
	Mix_Music* battleSong = Mix_LoadMUS("Sounds/battle1.mp3");

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
	monster->x = 400;
	monster->y = -100;
	setupMonster(monster);

	SDL_Rect menu;
	Text* text = (Text*) malloc(sizeof(Text) * 50);
	Text* options = (Text*) malloc(sizeof(Text) * 50);
	text->font = TTF_OpenFont("Resourcers/Chrono.ttf", 35);
	SDL_Color color = {255,255,255};
	SDL_Surface* textSurface;
	SDL_Texture* textTex;
	SDL_Texture* battleOptionsTex;
	SDL_Rect textRect;
	SDL_Rect battleInfo;
	text->render = &render;
	text->surface = &textSurface;
	text->tex = &textTex;
	text->color = &color;
	text->textRect = &textRect;



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
		SDL_RenderCopy(render,monsterTex,NULL,&monsterRect);
		SDL_RenderCopy(render, tex, NULL, &crono);

		//		SDL_RenderDrawRect(render, &textRect);
		moveMonster(monster);
		collisionCheck(crono_conf, &stage_conf, monster);

		if(move(&crono,&run,crono_conf,&stage_conf,monster)){
			if(!battle){
				Mix_PlayMusic(battleSong, -1);
				battle = 1;
			}
			SDL_SetRenderDrawColor(render, 1, 1, 71, 255);
			menuPlayer(&menu, WIDTH_SCREEN, HEIGH_SCREEN,1);
			SDL_RenderFillRect(render,&menu);
			setText(crono_conf,text);
			setupInfo(text,&menu);

			SDL_SetRenderDrawColor(render,255, 255, 255, 255);
			SDL_RenderCopy(render, textTex, NULL, &textRect);
		}
		SDL_SetRenderDrawColor(render,255, 255, 255, 255);

		SDL_RenderPresent(render);
		SDL_Delay(FPS);

	}

	Mix_Quit();
	Mix_FreeMusic(bgm);
	Mix_FreeMusic(battleSong);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();
	TTF_Quit();
	free(crono_conf->battle);
	free(crono_conf);
	free(monster->battle);
	free(monster);
	free(text);
	//	free(&menu);
	return 1;
}
