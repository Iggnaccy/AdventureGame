#include "game.h"

game_controller_t* NewGame()
{
    game_controller_t* g = malloc(sizeof(game_controller_t));
    g->achievements = 0;
    g->controls = DefaultControls();
    g->state = MAINMENU;
    g->player = NULL;
    g->map = DefineMap();
    char** dialog = {"Dialog line 1","Dialog line 2","Dialog line 3","Dialog line 4"};
    g->NPCs[0] = DefineNPC(0,0,0,0,0,0,0,dialog,NULL,NULL);
}

void FreeGame(game_controller_t* g)
{

}
