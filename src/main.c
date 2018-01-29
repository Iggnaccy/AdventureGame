#include "game.h"
#include "display.h"
#include "SDL_wrapper.h"
#include "button.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_BPP 32
#define FPS 30

int main(int argc, char* argv[])
{
    Initialize();
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_Event event;
    bool quit = false;
    display_t* d = malloc(sizeof(display_t) + TEXTURE_COUNT * sizeof(SDL_Surface*));
    DisplayDebug(screen, d);
    Timer_t* t = malloc(sizeof(Timer_t));
    CreatePlayer("Name");
    while(!quit)
    {
        StartTimer(t);
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        if(GetTime(t) < 1000 / FPS)
        {
            SDL_Delay((1000 / FPS) - GetTime(t));
        }
    }
    free(t);
    TTF_CloseFont(d->font);
    free(d);
    SDL_FreeSurface(screen);
    Quit();
    return 0;
}
