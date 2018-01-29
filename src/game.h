#ifndef _GAME_H_
#define _GAME_H_

#include "map.h"
#include "player.h"
#include "npc.h"
#include "battle.h"
#include "controls.h"

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

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
    controls_t* controls;
    player_t* player;
    map_t* map;
    enum GAME_STATE state;
    enum ACHIEVEMENTS achievements;
    npc_t* NPCs;
} game_controller_t;

#include "display.h"

game_controller_t* NewGame();

#endif // _GAME_H_
