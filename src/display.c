#include "display.h"
#include <string.h>

static struct path
{
    char* path;
    struct path* next;
};

typedef struct path path_t;

static path_t* FileNames()
{
    char* r[] = {"img/basalt.jpg","img/basalt_wall.jpg","img/brick.jpg","img/door.jpg","img/grass.jpg","img/lava.jpg","img/player_up.png","img/player_right.png","img/player_down.png","img/player_left.png","img/road_cross.jpg","img/road_horizontal.jpg","img/road_vertical.jpg","img/road_right_up.jpg","img/road_right_down.jpg","img/road_left_down.jpg", "img/road_left_up.jpg", "img/rock.jpg", "img/rock_wall.jpg", "img/roof.jpg","img/tree_crown.jpg", "img/tree_trunk.jpg", "img/tree_root.jpg", "img/water.jpg", "img/window.jpg", "img/wooden_floor.jpg"};
    path_t* first = malloc(sizeof(path_t));
    first->path = r[0];
    path_t* prev = first;
    for(int i = 1; i < TEXTURE_COUNT; i++)
    {
        path_t* temp = malloc(sizeof(path_t));
        temp->path = r[i];
        prev->next = temp;
        prev = temp;
    }
    return first;
}

TTF_Font* LoadFont(char* path, int size)
{
    TTF_Font* font = TTF_OpenFont(path, size);
    return font;
}

SDL_Surface* LoadTexture(char* path)
{
    SDL_Surface* texture = IMG_Load(path);
    SDL_Surface* r = SDL_DisplayFormatAlpha(texture);
    SDL_FreeSurface(texture);
    return r;
}

void LoadTexturesAndFont(display_t* d)
{
    path_t* paths = FileNames();
    d->font = LoadFont("font/lunchds.ttf", 24);
    char* e = TTF_GetError();
    if(strlen(e) > 0)
    {
        printf("LoadFont: %s\n", e);
    }
    for(int i = 0; i < TEXTURE_COUNT; i++)
    {
        d->textures[i] = LoadTexture(paths->path);
        char* g = IMG_GetError();
        if(strlen(g) > 0)
        {
            printf("LoadTextures: %s\n", g);
        }
        path_t* prev = paths;
        paths = paths->next;
        free(prev);
    }
}

static SDL_Rect apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
    return offset;
}

void DisplayDebug(SDL_Surface* screen, display_t* d)
{
    LoadTexturesAndFont(d);
    SDL_Color color = {255, 255, 255};
    SDL_Surface* message = TTF_RenderText_Solid(d->font, "The quick brown fox jumps over the lazy dog", color);
    apply_surface(5, 5, message, screen, NULL);
    SDL_FreeSurface(message);
    for(int i = 0; i < TEXTURE_COUNT; i++)
    {
        int x = 20 + 40*i;
        apply_surface(x, 50, d->textures[i], screen, NULL);
    }
    SDL_Flip(screen);
}

void DisplayMainMenu()
{

}