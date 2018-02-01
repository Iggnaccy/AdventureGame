#ifndef _ITEM_H_
#define _ITEM_H_
#include <stdbool.h>
#include "beast.h"

enum ITEM_TYPE
{
    BLANK, HEALTH_POTION, MANA_POTION, MAX_HEALTH, MAX_MANA, MAX_POTION, ATT_BUFF, DEF_BUFF, MAG_BUFF
};

typedef struct item
{
    int type;
    char* name;
    char* description;
    struct item *next;
} item_t;

item_t* DefineItem(char* name, enum ITEM_TYPE type, char* desc);
bool CanUseItem(beast_t* b, item_t* i);
void UseItem(beast_t* b, item_t* i);
void DestroyItemGroup(item_t* i);

#endif // _ITEM_H_
