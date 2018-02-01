#include "game.h"
#include "display.h"
#include "SDL_wrapper.h"
#include "button.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_BPP 32
#define FPS 60

void ResetScreen(SDL_Surface* screen)
{
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
}

int main(int argc, char* argv[])
{
    Initialize();
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    bool quit = false;
    display_t* d = malloc(sizeof(display_t) + TEXTURE_COUNT * sizeof(SDL_Surface*));
    LoadTexturesAndFont(d);
    Timer_t* t = malloc(sizeof(Timer_t));
    CreatePlayer("Name");
    game_controller_t* game = NewGame();
    SDL_Event event;
    while(!quit)
    {
        //Start frame
        StartTimer(t);
        //Frame changes
        ResetScreen(screen);
        switch(game->state)
        {
        case MAINMENU:
            DisplayMainMenu(screen, game);
            break;
        case NEWGAME:
            //DisplayNewGame(screen, game);
            break;
        case WORLD:
            DisplayWorld(screen, game);
            break;
        case BATTLE:
            //DisplayBattle(screen, game);
            break;
        case DEBUG:
            DisplayDebug(screen, d);
            break;
        default:
            break;
        }
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        //End of frame
        SDL_Flip(screen);
        if(GetTime(t) < 1000 / FPS)
        {
            SDL_Delay((1000 / FPS) - GetTime(t));
        }
    }
    free(t);
    SDL_Color c = {255,255,255};
    SDL_Surface* test = TTF_RenderText_Solid(d->font, "1", c);
    SDL_Rect offset;
    offset.x = 1280- (TTF_FontHeight(d->font));
    offset.y = 5;
    SDL_BlitSurface(test, NULL, screen, &offset);
    SDL_FreeSurface(test);
    SDL_Flip(screen);
    TTF_CloseFont(d->font);
    free(d);
    SDL_FreeSurface(screen);
    Quit();
    return 0;
}
