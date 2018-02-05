#include "beast.h"
#include <math.h>
#include <stdlib.h>

#define MAX_LVL 26
static int expTable[MAX_LVL] = {15, 25, 35, 50, 70, 150, 250, 400, 650, 950, 1300, 1775, 2200, 2700, 3400, 4300, 5100, 6000, 6950, 7800, 8800, 9900, 11000, 12000, 13000, 14000};
beast_t* DefineBeast(char* name, enum BEAST_TYPE type, int hp, int hpGrow, int mp, int mpGrow, int att, int attGrow, int def, int defGrow, int magic, int magicGrow)
{
    beast_t* b = malloc(sizeof(beast_t));
    b->name = name;
    b->type = type;
    b->hp = b->maxHP = hp;
    b->hpGrow = hpGrow;
    b->mp = b->maxMP = mp;
    b->mpGrow = mpGrow;
    b->attack = att;
    b->attGrow = attGrow;
    b->defense = def;
    b->defGrow = defGrow;
    b->magic = magic;
    b->magicGrow = magicGrow;
    b->isBlocking = false;
    b->isBlocked = false;
    b->isDead = false;
    return b;
}
static void DieBeast(beast_t* b)
{
    b->isDead = true;
}

void DealDamage(int damage, beast_t* defender)
{
    defender->hp = defender->hp - damage;
    if(defender->hp <= 0)
    {
        defender->hp = 0;
        DieBeast(defender);
    }
}

int CalculateExp(beast_t* winner, beast_t* loser)
{
    double mult;
    switch(loser->type)
    {
    case FIGHTER:
        mult = 0.5;
        break;
    case HEALER:
        mult = 0.55;
        break;
    case SORCERER:
        mult = 0.52;
        break;
    case TANK:
        mult = 0.5525;
        break;
    }
    double multPenalty = 1.0 + (((double)(loser->lvl) - (double)(winner->lvl))/50.0);
    mult *= multPenalty;
    int exp;
    if(loser->lvl < 5)
    {
        exp = (int)(15.0 * mult);
    }
    else
    {
        exp = (int)((double)expTable[loser->lvl - 5] * mult);
    }
    winner->experience += (int)exp;
    if(winner->experience >= expTable[winner->lvl])
    {
        winner->experience -= expTable[winner->lvl];
        LevelUp(winner);
    }
}

void LevelUp(beast_t* b)
{
    b->lvl++;
    b->attack += b->attGrow;
    b->defense += b->defGrow;
    b->magic += b->magicGrow;
    b->hp + b->hpGrow;
    b->maxHP += b->hpGrow;
    b->mp += b->mpGrow;
    b->maxMP += b->mpGrow;
}

void DestroyBeast(beast_t* b)
{
    free(b->name);
    free(b);
}
