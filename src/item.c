#include "item.h"

item_t* DefineItem(char* name, enum ITEM_TYPE type, char* desc)
{
    item_t* i = malloc(sizeof(item_t));
    i->name = name;
    i->description = desc;
    i->type = type;
    return i;
}
