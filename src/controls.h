#ifndef _CONTROLS_H_
#define _CONTROLS_H_
#include <stdint.h>

typedef struct controls
{
    uint8_t U, R, D, L;
    uint8_t act;
    uint8_t back;
} controls_t;

controls_t* DefaultControls();
void DestroyControls(controls_t* c);

#endif // _CONTROLS_H_
