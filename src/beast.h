#ifndef _BEAST_H_
#define _BEAST_H_
#include <stdbool.h>

enum BEAST_TYPE
{
    FIGHTER, HEALER, SORCERER, TANK ///for magic purposes: Fighter = {Attack buff}, Healer = {Heal, Party buff}, Sorcerer = {Single target burst, AOE}, Tank = {Self buff, Block}
};

typedef struct beast
{
    char* name;
    int type;
    int lvl;
    int experience;
    int hp, maxHP;
    int mp, maxMP;
    int attack, defense, magic;
    int baseHP, baseMP, baseAttack, baseDefense, baseMagic;
    int hpGrow, mpGrow, attGrow, defGrow, magicGrow;
    bool isBlocking;
    bool isBlocked;
    bool isDead;
} beast_t;

beast_t* DefineBeast(char* name, enum BEAST_TYPE type, int hp, int hpGrow, int mp, int mpGrow, int att, int attGrow, int def, int defGrow, int magic, int magicGrow);
void DealDamage(int damage, beast_t* defender);
int CalculateExp(beast_t* winner, beast_t* loser);
void ChangeName(beast_t* b, char* name);
void LevelUp(beast_t* b);
void DestroyBeast(beast_t* b);

#endif // _BEAST_H_
