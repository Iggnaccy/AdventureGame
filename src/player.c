#include "player.h"
#include <stdlib.h>

player_t* CreatePlayer(char* name)
{
    player_t* p = malloc(sizeof(player_t));
    p->name = name;
    p->locID = 1;
    p->x = p->y = 5.0;
    p->beasts[0] = p->beasts[1] = p->beasts[2] = p->beasts[3] = NULL;
    p->gold = 0;
    /*for(int i = 0; i < 64; i++)
    {
        p->inventory[i] = DefineItem("", BLANK, "");
    }*/
    return p;
}

void AddBeast(player_t* p, beast_t* b)
{
    int i = 0;
    while(i > 3 || p->beasts[i] != NULL)
    {
        i++;
    }
    if(i > 3)
        return;
    p->beasts[i] = b;
}

void DestroyPlayer(player_t* p)
{
    for(int i = 3; i >= 0; i--)
    {
        if(p->beasts[i] != NULL)
        {
            DestroyBeast(p->beasts[i]);
        }
    }
    /*for(int i = 63; i >= 0; i--)
    {
        if(p->inventory[i] != NULL)
        {
            DestroyItemGroup(p->inventory[i]);
        }
    }*/
    free(p->name);
    free(p);
}
