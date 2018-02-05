#ifndef _BATTLE_H_
#define _BATTLE_H_
#include "beast.h"
#include "player.h"
#include "npc.h"

typedef struct battlecontroller
{
    player_t* p;
    bool isTrainerBattle;
    npc_t* enemy;
    beast_t* wildBeast;
} battle_controller_t;

#include "game.h"
typedef struct gameController game_controller_t;

void BeginWildBattle(game_controller_t* g, beast_t* b);
void BeginEnemyBattle(game_controller_t* g, npc_t* n);

void BasicAttack(beast_t* source, beast_t* target);
void Block(beast_t* source, beast_t* target);
void OffensiveBuff(beast_t* user, beast_t* target);
void DefensiveBuff(beast_t* user, beast_t* target);
void Heal(beast_t* user, beast_t* target);
void MagicAttack(beast_t* source, bool aoe, beast_t* target);

void EndBattle(game_controller_t* g);

#endif // _BATTLE_H_
