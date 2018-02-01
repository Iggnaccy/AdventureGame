#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#define TEXTURE_COUNT 28

typedef struct display
{
    int locID;
    int visibleX, visibleY;
    TTF_Font* font;
    SDL_Surface* textures[];
} display_t;

#include "game.h"
typedef struct gameController game_controller_t;
SDL_Surface* LoadTexture(char* path);
TTF_Font* LoadFont(char* path, int size);
display_t* LoadTexturesAndFont(display_t* d);
void DisplayDebug(SDL_Surface* screen, display_t* d);
void DisplayWorld(SDL_Surface* screen, game_controller_t* game);
void DisplaySidePanels(SDL_Surface* screen, game_controller_t* game);
void DisplayMainMenu(SDL_Surface* screen, game_controller_t* game);
void DisplayNewGame(SDL_Surface* screen, game_controller_t* game);
void DisplayBattle(SDL_Surface* screen, game_controller_t* game);
void DestroyDisplay(display_t* d);

#endif // _DISPLAY_H_
