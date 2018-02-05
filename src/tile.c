#include "tile.h"
#define TEXTURE_COUNT 28
#include <stdio.h>

tile_t* SetTile(bool passable, bool dangerous)
{
    tile_t* t = malloc(sizeof(tile_t));
    t->passable = passable;
    t->dangerous = dangerous;
    return t;
}

tile_t** SetAllTiles(tile_t** r)
{
    if(r == NULL)
    {
        r = malloc(sizeof(tile_t*) * TEXTURE_COUNT);
    }
    r[BLACK] = SetTile(true, false);
    r[BASALT] = SetTile(true, false);
    r[BASALT_W] = SetTile(false, false);
    r[BRICK] = SetTile(false, false);
    r[DOOR] = SetTile(true, false);
    r[GRASS] = SetTile(true, true);
    r[LAVA] = SetTile(false, false);
    r[PLAYER_DOWN] = r[PLAYER_LEFT] = r[PLAYER_RIGHT] = r[PLAYER_UP] = NULL;
    r[ROAD_CROSS] = r[ROAD_H] = r[ROAD_L_D] = r[ROAD_L_U] = r[ROAD_R_D] = r[ROAD_R_U] = r[ROAD_V] = SetTile(true, false);
    r[ROCK] = SetTile(true, true);
    r[ROCK_W] = SetTile(false, false);
    r[ROOF] = SetTile(false, false);
    r[TREE_CROWN] = r[TREE_ROOT] = r[TREE_TRUNK] = SetTile(false, false);
    r[WATER] = SetTile(false, false);
    r[WINDOW] = SetTile(false, false);
    r[WOODEN_FLOOR] = SetTile(true, false);
    r[DIALOGUE_BOX] = NULL;
    return r;
}
