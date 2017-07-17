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
/// My API's
#include "utils.h"
#include "Player.h"
#include "Stage.h"
#include "Monster.h"
#include "Move.h" // Movimentação ta bem complicadinha

#define WIDTH_SCREEN 800
#define HEIGH_SCREEN 640
#define FPS 6


int main(int argc, char **argv) {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
		SDL_Log("Error in init! %s", SDL_GetError());
		return -1;
	}
	int contMusica = 1;

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
		SDL_Log("Error in audio init! %s",Mix_GetError() );
		return -1;
	}

	Mix_Music* bgm = Mix_LoadMUS("Sounds/magus.mp3");

	//	Mix_Chunk* sound = Mix_Load;

	SDL_Window* window;
	SDL_Renderer* render;

	initScreen(&window,&render, WIDTH_SCREEN,HEIGH_SCREEN);
	PlayerConf* crono_conf;
	crono_conf = (PlayerConf*) malloc(sizeof(PlayerConf) * 50);
	STAGE stage_conf;
	SDL_Rect crono;
	SDL_Surface* surface;
	SDL_Surface* tex;
	crono_conf->render = &render;
	crono_conf->surface = &surface;
	crono_conf->tex = &tex;
	crono_conf->name = "crono";

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
	setupMonster(monster);

	if(!setupSprite(crono_conf, &crono))
	{
		SDL_Log("Error s %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);
		return -1;
	}


	SDL_RenderClear(render);

	int run = 1;
	Mix_PlayMusic(bgm, -1);


	while(run){
		if(contMusica){

			contMusica = 0;
		}

		SDL_RenderClear(render);
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderCopy(render, texturaStage, NULL, &stageRect);
		SDL_RenderCopy(render, tex, NULL, &crono);
		SDL_RenderCopy(render,monsterTex,NULL,&monsterRect);
		SDL_RenderDrawRect(render, &crono);
		SDL_RenderDrawRect(render, &monsterRect);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		move(&crono,&run,crono_conf, &stage_conf);
		moveMonster(monster);
		SDL_RenderPresent(render);
		SDL_Delay(FPS);

	}

	Mix_Quit();

	Mix_FreeMusic(bgm);

	bgm = NULL;


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();

	return 1;
}
