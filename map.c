#include "map.h"
#include <stdio.h>

static location_t* LoadLocationFromFile(char* path)
{
    FILE* fp = fopen(path, "r");
    FILE* fo = fopen("locations\\log.txt", "w");

    int x, y;
    fscanf(fp, "%d%d", &x, &y);
    fprintf(fo, "Loaded x:%d y:%d", x, y);
    int** tiles = malloc(y*sizeof(int*));
    location_t* l = malloc(2* sizeof(int) + y*sizeof(int*) + sizeof(passage_t*) * 8);
    l->x = x;
    l->y = y;
    for(int i = 0; i < y; i++)
    {
        tiles[i] = calloc(x, sizeof(int));
        fprintf(fo, "\r\nLoading on y=%d: ", i);
        for(int j = 0; j < x; j++)
        {
            fscanf(fp, "%d", &tiles[i][j]);
            fprintf(fo, "%d ", tiles[i][j]);
        }
    }
    l->tiles = tiles;
    passage_t** p = malloc(8 * sizeof(passage_t*));
    for(int i = 0; i < 8; i++)
    {
        p[i] = malloc(sizeof(passage_t));
        fprintf(fo, "\r\nLoading passage %d: ", i);
        fscanf(fp, "%d%d%d%d%d",&(p[i]->startX),&(p[i]->startY),&(p[i]->loc),&(p[i]->endX),&(p[i]->endY));
        fprintf(fo, "%d %d %d %d %d", p[i]->startX, p[i]->startY, p[i]->loc, p[i]->endX, p[i]->endY);
        //p[i]->ID = i;
    }

    l->passages = p;
    fprintf(fo, "\r\nLocation successfully loaded");
    fclose(fp);
    fclose(fo);
    return l;
}

map_t* DefineMap(map_t* m)
{
    m = malloc(sizeof(map_t));
    m->locations = malloc(sizeof(location_t*)*2);
    m->locations[0] = LoadLocationFromFile("locations\\loc1.loc");
    m->locations[1] = LoadLocationFromFile("locations\\loc2.loc");
    return m;
}

