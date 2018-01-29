#ifndef _BATTLE_H_
#define _BATTLE_H_
#include "beast.h"
#include "player.h"
#include "npc.h"

void BeginWildBattle(player_t* p, beast_t* b);
void BeginEnemyBattle(player_t* p, npc_t* n);

#endif // _BATTLE_H_
