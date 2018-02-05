#include "controls.h"
#include "SDL/SDL.h"

controls_t* DefaultControls()
{
    controls_t* c = malloc(sizeof(controls_t));
    c->U = SDLK_UP;
    c->D = SDLK_DOWN;
    c->L = SDLK_LEFT;
    c->R = SDLK_RIGHT;
    c->act = SDLK_z;
    c->back = SDLK_x;
    return c;
}

void DestroyControls(controls_t* c)
{
    free(c);
}
