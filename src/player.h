#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "beast.h"
#include "item.h"

typedef struct player
{
    char* name;
    int locID;
    double x, y;
    beast_t* beasts[4];
    //item_t* inventory[64];
    int gold;
} player_t;

player_t* CreatePlayer(char* name);
void AddBeast(player_t* p, beast_t* b);
void DestroyPlayer(player_t* p);

#endif // _PLAYER_H_
