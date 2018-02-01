#include "button.h"

button_t* DefineButton(int x, int y, int w, int h, SDL_Color c, void (*press)(game_controller_t*), char* name)
{
    button_t* r = malloc(sizeof(button_t));
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    r->color = c;
    r->press = press;
    r->name = name;
    return r;
}
