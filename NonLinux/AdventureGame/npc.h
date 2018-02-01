#ifndef _NPC_H_
#define _NPC_H_
#include "beast.h"
#include "item.h"
#include <stdbool.h>

typedef struct npc
{
    int locID, x, y;
    int type; /// 0 - pedestrian, 1 - shopkeeper, 2 - enemy, 3 - healer
    bool aggressive;
    bool defeated;
    int bounty;
    char* dialogs[4]; /// type = 0 -> 1 dialog line, type = 1 -> {welcome,buy,sell,bye}, type = 2 -> {begin fight, win fight, lose fight, defeated already}, type = 3 -> {welcome, heal, bye, ""}
    beast_t* beasts[4];
    item_t* inventory;
} npc_t;

npc_t* DefineNPC(int locID, int x, int y, int type, bool aggressive, bool defeated, int bounty, char** dialog, beast_t** beasts, item_t* inv);
void DestroyNPC(npc_t* n);

#endif // _NPC_H_
