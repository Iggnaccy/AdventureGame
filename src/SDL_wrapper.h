#ifndef _SDL_WRAPPER_H_
#define _SDL_WRAPPER_H_
#include "display.h"
#include <stdbool.h>
#include <stdint.h>
//timer structure and timer-related functions are based on LazyFoo's timer class
typedef struct timer
{
    Uint32 startTicks;
    Uint32 pauseTicks;
    bool started;
    bool paused;
} Timer_t;

void Initialize();
void Quit();

void StartTimer(Timer_t* t);
void PauseTimer(Timer_t* t);
void UnpauseTimer(Timer_t* t);
Uint32 GetTime(Timer_t* t);

#endif // _SDL_WRAPPER_H_
