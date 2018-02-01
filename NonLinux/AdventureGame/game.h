#ifndef _GAME_H_
#define _GAME_H_

#include "map.h"
#include "player.h"
#include "npc.h"
#include "battle.h"
#include "controls.h"

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#define NPC_COUNT 1
#include "display.h"
typedef struct display display_t;

enum GAME_STATE
{
    MAINMENU, NEWGAME, WORLD, BATTLE, DEBUG
};

enum ACHIEVEMENTS
{
    FIRST_BEAST = 1, FIRST_WIN = 2, ENTER_FOREST = 4, ENTER_TUNNEL = 8, ENTER_VOLCANO = 16, RECRUIT_BEAST = 32, LEVEL_BEAST_MAX = 64
};

typedef struct gameController
{
    display_t* display;
    controls_t* controls;
    player_t* player;
    map_t* map;
    int state;
    int achievements;
    npc_t* NPCs[NPC_COUNT];
} game_controller_t;


game_controller_t* NewGame();
void FreeGame(game_controller_t* g);

#endif // _GAME_H_
