#include "player.h"
#include <stdlib.h>

player_t* CreatePlayer(char* name)
{
    player_t* p = malloc(sizeof(player_t));
    p->name = name;
    p->beasts[0] = p->beasts[1] = p->beasts[2] = p->beasts[3] = NULL;
    p->gold = 0;
    for(int i = 0; i < 64; i++)
    {
        p->inventory[i] = DefineItem("", BLANK, "");
    }
    return p;
}
