#include "beast.h"
#include <math.h>
///int expTable[] = {0,25,35,...}
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
    b->isDead = false;
    return b;
}
static void DieBeast(beast_t* b)
{
    b->isDead = true;
}

void DealDamage(int damage, beast_t* defender)
{
    defender->hp = fmax(0, defender->hp - damage);
    if(defender->hp <= 0)
    {
        DieBeast(defender);
    }
}

/**
int CalculateExp(beast_t* winner, beast_t* loser)
{

}
*/
