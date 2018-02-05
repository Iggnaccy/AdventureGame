#include "game.h"
#include "display.h"
#include "SDL_wrapper.h"
#include "button.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Initialize();
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    bool quit = false;
    Timer_t* t = malloc(sizeof(Timer_t));
    CreatePlayer("Name");
    game_controller_t* game = NewGame();
    while(!quit)
    {
        //Start timing the frame
        StartTimer(t);
        //Start frame
        quit = DoFrame(screen, game);
        //End of frame
        SDL_Flip(screen);
        //Wait for next frame
        if(GetTime(t) < 1000 / FPS)
        {
            SDL_Delay((1000 / FPS) - GetTime(t));
        }
    }
    FreeGame(game);
    free(t);
    SDL_FreeSurface(screen);
    Quit();
    return 0;
}
