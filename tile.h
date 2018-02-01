#ifndef _TILE_H_
#define _TILE_H_
#include <stdbool.h>

enum TILE_TYPE
{
    BLACK, BASALT,BASALT_W, BRICK, DOOR, GRASS, LAVA, PLAYER_UP,
    PLAYER_RIGHT, PLAYER_DOWN, PLAYER_LEFT, ROAD_CROSS, ROAD_H, ROAD_V,
    ROAD_R_U, ROAD_R_D, ROAD_L_D, ROAD_L_U, ROCK, ROCK_W, ROOF, TREE_CROWN,
    TREE_TRUNK, TREE_ROOT, WATER, WINDOW, WOODEN_FLOOR, DIALOGUE_BOX
};

typedef struct tile
{
    int type;
    bool passable;
    bool dangerous;
} tile_t;

tile_t* SetTile(enum TILE_TYPE type, bool passable, bool dangerous);
#endif // _TILE_H_
