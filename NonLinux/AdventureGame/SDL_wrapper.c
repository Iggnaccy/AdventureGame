#include "SDL_wrapper.h"
#include <stdbool.h>

void Initialize()
{
    bool error = false;
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("SDL_Init: %s\n", SDL_GetError());
        error = true;
    }
    if(TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        error = true;
    }
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1)
    {
        printf("IMG_Init: %s\n", IMG_GetError());
        error = true;
    }
    if(error)
    {
        Quit();
        exit(-1);
    }
    SDL_WM_SetCaption("Adventure Game", NULL);
}

void Quit()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void StartTimer(Timer_t* t)
{
    t->paused = false;
    t->pauseTicks = 0;
    t->started = true;
    t->startTicks = SDL_GetTicks();
}

void PauseTimer(Timer_t* t)
{
    if(!t->paused)
    {
        t->paused = true;
        t->pauseTicks = SDL_GetTicks() - t->startTicks;
    }
}

void UnpauseTimer(Timer_t* t)
{
    if(t->paused)
    {
        t->paused = false;
        t->startTicks = SDL_GetTicks() - t->pauseTicks;
        t->pauseTicks = 0;
    }
}

Uint32 GetTime(Timer_t* t)
{
    if(t->started)
    {
        if(t->paused)
        {
            return t->pauseTicks;
        }
        else
        {
            return SDL_GetTicks() - t->startTicks;
        }
    }
    return 0;
}
