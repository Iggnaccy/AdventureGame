#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "SDL/SDL.h"
#include "game.h"

typedef struct button
{
    int x, y;
    int w, h;
    SDL_Color color;
    void (* press)(game_controller_t*);
    char* name;
} button_t;

button_t* DefineButton(int x, int y, int w, int h, SDL_Color c, void (*press)(game_controller_t*), char* name);

#endif // _BUTTON_H_
