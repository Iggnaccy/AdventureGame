#include "battle.h"

void BeginWildBattle(game_controller_t* g, beast_t* b)
{
    g->battle->wildBeast = b;
    g->battle->isTrainerBattle = false;
}
void BeginEnemyBattle(game_controller_t* g, npc_t* n)
{
    g->battle->enemy = n;
    g->battle->isTrainerBattle = true;
}

void BasicAttack(beast_t* source, beast_t* target)
{
    if(target->isBlocked)
    {
        target->isBlocked = false;
        return;
    }
    double baseDamage;
    switch(source->type)
    {
    case FIGHTER:
        baseDamage = 15.0;
        break;
    case HEALER:
        baseDamage = 5.0;
        break;
    case SORCERER:
        baseDamage = 7.0;
        break;
    case TANK:
        baseDamage = 9.0;
        break;
    default:
        baseDamage = 10.0;
        break;
    }
    double mult = (100.0 + source->attack - target->defense) / 100.0;
    DealDamage((int)(baseDamage * mult), target);
}

void Block(beast_t* source, beast_t* target)
{
    source->isBlocking = true;
    target->isBlocked = true;
}

void OffensiveBuff(beast_t* user, beast_t* target)
{
    int value = user->magic / 3;
    target->attack += value;
}

void MagicAttack(beast_t* source, bool aoe, beast_t* target)
{
    double mult = 1.0;
    if(aoe) mult/= 3.0;
    DealDamage((int)((double)source->magic * mult), target);
}

void Heal(beast_t* user, beast_t* target)
{
    DealDamage(-user->magic, target);
}
