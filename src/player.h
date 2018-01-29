#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "beast.h"
#include "item.h"

typedef struct player
{
    char* name;
    int locID, x, y;
    beast_t* beasts[4];
    item_t* inventory[64];
    int gold;
} player_t;

player_t* CreatePlayer(char* name);

#endif // _PLAYER_H_
