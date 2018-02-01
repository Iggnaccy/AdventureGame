#include "npc.h"
#include <stdio.h>

npc_t* DefineNPC(int locID, int x, int y, int type, bool aggressive, bool defeated, int bounty, char** dialog, beast_t** beasts, item_t* inv)
{
    npc_t* r = malloc(sizeof(npc_t));
    r->locID = locID;
    r->x = x;
    r->y = y;
    r->type = type;
    r->aggressive = aggressive;
    r->bounty = bounty;
    for(int i = 0; i < 4; i++)
    {
        r->dialogs[i] = dialog[i];
    }
    r->defeated = defeated;
    if(beasts != NULL)
    for(int i = 0; i < 4; i++)
    {
        r->beasts[i] = beasts[i];
    }
    r->inventory = inv;
    return r;
}

void DestroyNPC(npc_t* n)
{
    for(int i = 3; i >= 0; i--)
    {
        free(n->dialogs[i]);
        if(n->beasts[i] != NULL)
        {
            //DestroyBeast(n->beasts[i]);
        }
    }
    DestroyItemGroup(n->inventory);
    free(n);
}
