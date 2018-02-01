#include "item.h"
#include <stdio.h>

item_t* DefineItem(char* name, enum ITEM_TYPE type, char* desc)
{
    item_t* i = malloc(sizeof(item_t));
    i->name = name;
    i->description = desc;
    i->type = type;
    return i;
}

void DestroyItemGroup(item_t* i)
{
    item_t** prev = &i;
    item_t* next = i->next;
    while(next != NULL)
    {
        free((*prev)->description);
        free((*prev)->name);
        free(*prev);
        *prev = next;
        next = (*prev)->next;
    }
}
