#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <string.h>

#include "elements/monster.h"
#include "elements/background.h"
#include "elements/player.h"
#include "utils/move.h"
#include "utils/collision.h"
#include "utils/util.h"
#include "utils/battle.h"


const int WIDTH_SCREEN = 1000;
const int HEIGTH_SCREEN = 700;

SDL_Window* window;				//window
SDL_Renderer* render;			//render
SDL_Texture* text;				//texture
Player player[3];
Monster monster[3];
SDL_Texture* player_tex; 		//text
SDL_Texture* stage_tex;
SDL_Texture* monster_text;
SDL_Surface* background_surface;
SDL_Surface* player_surface;
SDL_Surface* monster_surface;
RootElement root_element;		//root_element, contains info
Background background;
Scenario scene;
SDL_Rect stage;
SDL_Rect player_rect[3];
SDL_Rect monster_rect[3];
int inBattle = 0;
int contMusic = 0; /// music counter, control player state

///Effects

Mix_Music* bgm; /// background music
Mix_Music* battle; /// battle song

void destroy();
void findPos();
int Game();
void loopGame();
void setStates(Action*, Player*); /// set sprite states

int setScene(); /// set All variables of screen to use in battlestate

int main(int argc, char** argv)
{
	Game(); // starting game..

	return 1;
}


int Game()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
    {
    	SDL_Log("Error in init game! %s", SDL_GetError());
    	return 0;
    }

    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0 )
    {
        SDL_Log("Error initing audio! %s", Mix_GetError());
    }

    bgm = Mix_LoadMUS("effects/audio/zeal.mp3");
    battle = Mix_LoadMUS("effects/audio/battle11.mp3");
    root_element.w = WIDTH_SCREEN;
    root_element.h = HEIGTH_SCREEN;

    if(!createWindow(&window, &render, "Chrono Trigger engine test",&root_element))
    {
    	SDL_Log("Error in create window! %s ", SDL_GetError());
    	return 0;
    }

    //// Starting elements of game
    background.render = &render;
    background.surface = &background_surface;
    background.stage = &stage;
    background.text = &stage_tex;
    if(!createStage(&background))
    {
    	SDL_Log("Error creating background %s", SDL_GetError());
    	destroy();
        return 0;
    }
    loopGame();
    player[0].name = "crono";
    player[0].render = &render;
    player[0].text = &player_tex;
    player[0].player_rect = &player_rect[0];
    player[0].surface = &player_surface;
    player[0].sprite_img = malloc(sizeof(char) * 100);
    player[0].sprite_img_limit = 6;


    monster[0].render = &render;
    monster[0].text = &monster_text;
    monster[0].monster_rect = &monster_rect[0];
    monster[0].sprite_img_limit = 6;
    monster[0].surface = &monster_surface;

    for (int i = 0; i < 1; i++)
    {


        if(!set_sprite(&player[i], 0))
        {
          SDL_Log("Error in creating sprite! %d -> %s", i, SDL_GetError());
        }

        if(!set_monster(&monster[i]))
        {
            SDL_Log("Error in creating monster! %d -> %s", i, SDL_GetError());
        }


    }

    Action actions;
    cleanAction(&actions);
    Mix_PlayMusic(bgm, -1);
    if(!setScene())
    {
        SDL_Log("Error in setting scene! %s", SDL_GetError());
        destroy();
        return 0;
    }
        /// game actions
    while(1)
    {   
        for (int i = 0; i < 1; ++i)
        {
            action(&actions);     

            if(!collision_check(&player_rect[i],&monster_rect[i]) && !inBattle)
            {
                move_sprite(&player_rect[i],&monster_rect[i],&actions,&stage,&root_element,"sprite",0);
                move_monster(&monster);

            }
            else
            {
                if(!contMusic)
                {
                    Mix_PauseMusic();
                    Mix_PlayMusic(battle,-1);
                    contMusic = 1;
                }
                inBattle = 1;
                player[i].battle.inBattle = 1;
                player[i].battle.preparing = 1;
                if(move_battle(&scene, &actions) < 0)
                {
                    player[i].battle.inBattle = 1;
                    player[i].battle.preparing = 0;

                }

                if(player[i].battle.inBattle){
                    findPos();
                    battle_system(&player,&monster);
                }
            }

        }

        setStates(&actions,&player[0]);

        if(actions.quit)
            break;
        loopGame();
    }


    destroy();

    return 1;
}



void setStates(Action* action, Player* player)
{

    /// each sprite has a state, who indentify the sprite animation
    player->action = 1;  ///if has action, change sprite, if not, make sprite stop
    if(!player->battle.inBattle)
    {
        if(action->up)
            player->state = 1;

        else if(action->left)
            player->state = 2;

        else if(action->right)
            player->state = 3;

        else if(action->down)
            player->state = 4;
        else
            player->action = 0;
    }

    change_sprite(&player[0]);

}


int setScene()
{
    scene.background = &background;
    scene.player = &player[0];
    scene.monster = &monster[0];
    scene.root_element = &root_element;
    return 1;
}


void findPos()
{
    if(player->player_rect->y > monster->monster_rect->y) /// lower
        player->state = 1;
    else if(player->player_rect->y < monster->monster_rect->y) // upper
        player->state = 4;
}

void loopGame()
{
	SDL_RenderClear(render);
    SDL_RenderCopy(render, stage_tex, NULL, &stage);
    SDL_RenderCopy(render, monster_text, NULL, &monster_rect);
    SDL_RenderCopy(render, player_tex, NULL, &player_rect);
    SDL_RenderPresent(render);
    SDL_Delay(6);
}

void destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
    Mix_FreeMusic(bgm);
	SDL_Log("Bye!");
    SDL_Quit();
}
