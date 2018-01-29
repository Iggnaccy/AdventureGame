#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "game.h"
#define TEXTURE_COUNT 26

typedef struct display
{
    int locID;
    int visibleX, visibleY;
    TTF_Font* font;
    SDL_Surface* textures[];
} display_t;

SDL_Surface* LoadTexture(char* path);
TTF_Font* LoadFont(char* path, int size);
void LoadTexturesAndFont(display_t* d);
void DisplayDebug(SDL_Surface* screen, display_t* d);
void DisplayWorld(game_controller_t* game);
void DisplaySidePanels(game_controller_t* game);
void DisplayMainMenu();
void DisplayNewGame();
void DisplayBattle(game_controller_t* game);

#endif // _DISPLAY_H_
