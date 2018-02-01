#include "display.h"
#include "button.h"
#include <string.h>

static struct path
{
    char* path;
    struct path* next;
};

typedef struct path path_t;

static path_t* FileNames()
{
    char* r[] = {"img\\basalt.jpg","img\\basalt_wall.jpg","img\\brick.jpg","img\\door.jpg","img\\grass.jpg","img\\lava.jpg","img\\player_up.png","img\\player_right.png","img\\player_down.png","img\\player_left.png","img\\road_cross.jpg","img\\road_horizontal.jpg","img\\road_vertical.jpg","img\\road_right_up.jpg","img\\road_right_down.jpg","img\\road_left_down.jpg", "img\\road_left_up.jpg", "img\\rock.jpg", "img\\rock_wall.jpg", "img\\roof.jpg","img\\tree_crown.jpg", "img\\tree_trunk.jpg", "img\\tree_root.jpg", "img\\water.jpg", "img\\window.jpg", "img\\wooden_floor.jpg", "img\\dialoguebox.png"};
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

display_t* LoadTexturesAndFont(display_t* d)
{
    if(d == NULL)
    {
        d = malloc(sizeof(display_t));
    }
    path_t* paths = FileNames();
    d->font = LoadFont("font\\lunchds.ttf", 24);
    char* e = TTF_GetError();
    if(strlen(e) > 0)
    {
        printf("LoadFont: %s\r\n", e);
    }
    for(int i = 0; i < TEXTURE_COUNT; i++)
    {
        d->textures[i] = LoadTexture(paths->path);
        char* g = IMG_GetError();
        if(strlen(g) > 0)
        {
            printf("LoadTextures: %s\r\n", g);
        }
        path_t* prev = paths;
        paths = paths->next;
        free(prev);
    }
    return d;
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
    SDL_Color color = {255, 255, 255};
    SDL_Surface* message = TTF_RenderText_Solid(d->font, "The quick brown fox jumps over the lazy dog", color);
    apply_surface(10, 10, message, screen, NULL);
    SDL_FreeSurface(message);
    for(int i = 0; i < TEXTURE_COUNT-1; i++)
    {
        int x = 20 + 40*i;
        apply_surface(x, 50, d->textures[i], screen, NULL);
    }
    apply_surface(1280/2 - 140, 640, d->textures[TEXTURE_COUNT-1], screen, NULL);
    SDL_Flip(screen);
}

static void StartGame(game_controller_t* g)
{
    g->state = NEWGAME;
    printf("Changing scene to NEWGAME\r\n");
}

static void Debug(game_controller_t* g)
{
    g->state = DEBUG;
    printf("Changing scene to DEBUG\r\n");
}

static void DisplayButton(SDL_Surface* screen, button_t* b)
{
    SDL_Rect r;
    r.x = b->x;
    r.y = b->y;
    r.w = b->w;
    r.h = b->h;
    SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, b->color.r, b->color.g, b->color.b));
}

static bool CheckButtonPress(int x, int y, button_t* b)
{
    return (x >= b->x && x <= b->x + b->w && y >= b->y && y <= b->y + b->h);
}

void DisplayMainMenu(SDL_Surface* screen, game_controller_t* game)
{
    SDL_Color c = {128,128,128};
    button_t* start = DefineButton(50, 50, 200, 100, c, StartGame);
    button_t* debug = DefineButton(50, 155, 200, 100, c, Debug);
    DisplayButton(screen, start);
    DisplayButton(screen, debug);
    SDL_Event event;
    int x, y;
    if(SDL_GetMouseState(&x, &y) & SDL_BUTTON_LMASK)
    {
        if(CheckButtonPress(x, y, start))
        {
            start->press(game);
        }
        else if(CheckButtonPress(x, y, debug))
        {
            debug->press(game);
        }
    }
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            Quit();
            exit(0);
        }
    }
}

void DestroyDisplay(display_t* d)
{
    for(int i = TEXTURE_COUNT-1; i >=0; i--)
    {
        SDL_FreeSurface(d->textures[i]);
    }
    TTF_CloseFont(d->font);
    free(d);
}
