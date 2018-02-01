#include "tile.h"

tile_t* SetTile(enum TILE_TYPE type, bool passable, bool dangerous)
{
    tile_t* t = malloc(sizeof(tile_t));
    t->type = type;
    t->passable = passable;
    t->dangerous = dangerous;
    return t;
}
