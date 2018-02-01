#ifndef _MAP_H_
#define _MAP_H_
#include "tile.h"

typedef struct passage
{
    int startX, startY;
    int loc;
    int endX, endY;
} passage_t;

typedef struct location
{
    int** tiles;
    passage_t* passages[8];
} location_t;

typedef struct map
{
    location_t* locations;
} map_t;

passage_t* DefinePassage(int sX, int sY, int loc, int eX, int eY);
location_t* DefineLocation(int** tiles, int passCount, passage_t* pass[]);
map_t* DefineMap();

#endif // _MAP_H_
