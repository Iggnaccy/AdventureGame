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
    char* r[] = {"img/black.png","img/basalt.jpg","img/basalt_wall.jpg","img/brick.jpg","img/door.jpg","img/grass.jpg","img/lava.jpg","img/player_up.png","img/player_right.png","img/player_down.png","img/player_left.png","img/road_cross.jpg","img/road_horizontal.jpg","img/road_vertical.jpg","img/road_right_up.jpg","img/road_right_down.jpg","img/road_left_down.jpg", "img/road_left_up.jpg", "img/rock.jpg", "img/rock_wall.jpg", "img/roof.jpg","img/tree_crown.jpg", "img/tree_trunk.jpg", "img/tree_root.jpg", "img/water.jpg", "img/window.jpg", "img/wooden_floor.jpg", "img/dialoguebox_temp.png"};
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
    char* g;
    fprintf(stderr,"TTF_OpenFont: %s\n", TTF_GetError());
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
        d = malloc(sizeof(display_t) + TEXTURE_COUNT * sizeof(SDL_Surface*));
    }
    d->font = LoadFont("font/lunchds.ttf", 16);
    path_t* paths = FileNames();
    for(int i = 0; i < TEXTURE_COUNT; i++)
    {
        d->textures[i] = LoadTexture(paths->path);
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
}

static void StartGame(game_controller_t* g)
{
    g->state = WORLD;
    printf("Changing scene to NEWGAME\n");
}

static void Debug(game_controller_t* g)
{
    g->state = DEBUG;
    printf("Changing scene to DEBUG\n");
}

static void DisplayButton(SDL_Surface* screen, button_t* b, game_controller_t* g)
{
    SDL_Rect r;
    r.x = b->x;
    r.y = b->y;
    r.w = b->w;
    r.h = b->h;
    SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, b->color.r, b->color.g, b->color.b));
    SDL_Color c = {255,183,0};
    SDL_Surface* text = TTF_RenderText_Solid(g->display->font, b->name, c);
    int x = b->x + (b->w/2) - text->clip_rect.w/2;
    int y = b->y + (b->h/2) - text->clip_rect.h/2;
    apply_surface(x, y, text, screen, NULL); // Przesun mnie
    SDL_FreeSurface(text);
}

static bool CheckButtonPress(int x, int y, button_t* b)
{
    return (x >= b->x && x <= b->x + b->w && y >= b->y && y <= b->y + b->h);
}

void DisplayMainMenu(SDL_Surface* screen, game_controller_t* game)
{
    SDL_Color c = {128,128,128};
    button_t* start = DefineButton(50, 50, 200, 100, c, StartGame, "Start Game");
    button_t* debug = DefineButton(50, 155, 200, 100, c, Debug, "Debug");
    DisplayButton(screen, start, game);
    DisplayButton(screen, debug, game);
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
    free(start);
    free(debug);
}

void DisplayWorld(SDL_Surface* screen, game_controller_t* game)
{
    location_t* l = game->map->locations[game->player->locID];
    int xOffset = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
    SDL_Color c = {255,255,255};
    SDL_Surface* debug = TTF_RenderText_Solid(game->display->font, "1", c);
    SDL_Rect r;
    r.x = r.y = 0;
    r.w = xOffset;
    r.h = SCREEN_HEIGHT;
    SDL_FillRect(screen, &r, SDL_MapRGB(screen->format,128,128,128));
    r.x = SCREEN_HEIGHT + xOffset;
    SDL_FillRect(screen, &r, SDL_MapRGB(screen->format,128,128,128));

    for(int i = 0; i < l->y; i++)
    {
        for(int j = 0; j < l->x; j++)
        {
            apply_surface(xOffset+j*40,i*40,game->display->textures[l->tiles[i][j]],screen,NULL);
            if(game->tiles[l->tiles[i][j]]->passable == false)
            {
                //apply_surface(xOffset + j*40 + 15, i*40 + 15, debug, screen, NULL);
            }
        }
    }
}

void DisplayPlayer(SDL_Surface* screen, game_controller_t* game, int id)
{
    int xOffset = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
    int x = xOffset + (int)(game->player->x*40.0) - 20;
    int y = (int)(game->player->y*40.0) - 20;
    apply_surface(x, y, game->display->textures[id], screen, NULL);
}

void DisplayTextBox(SDL_Surface* screen, game_controller_t* game, char* text)
{
    int x = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
    int y = (SCREEN_HEIGHT - 200);
    apply_surface(x, y, game->display->textures[DIALOGUE_BOX], screen, NULL);
    SDL_Color c = {0,0,0};
    SDL_Surface* message = TTF_RenderText_Solid(game->display->font, text, c);
    apply_surface(x + 10, y + 10, message, screen, NULL);
    SDL_FreeSurface(message);
}

static void DisplayBeast(SDL_Surface* screen, beast_t* b, int x, int y, game_controller_t* g)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = r.h = 160;
    SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_Color c = {0,0,0};
    int infoX = 5 + x, infoY = 5 + y;
    char* text = malloc(sizeof(char) * 128);
    snprintf(text, 128, "%s", b->name);
    SDL_Surface* message = TTF_RenderText_Solid(g->display->font, text, c);
    apply_surface(infoX, infoY, message, screen, NULL);
    SDL_FreeSurface(message);
    infoY += 40;
    snprintf(text, 128, "HP: %d/%d (+%d)", b->hp, b->maxHP, b->hpGrow);
    message = TTF_RenderText_Solid(g->display->font, text, c);
    apply_surface(infoX, infoY, message, screen, NULL);
    SDL_FreeSurface(message);
    infoY += 20;
    snprintf(text, 128, "MP: %d/%d (+%d)", b->mp, b->maxMP, b->mpGrow);
    message = TTF_RenderText_Solid(g->display->font, text, c);
    apply_surface(infoX, infoY, message, screen, NULL);
    SDL_FreeSurface(message);
    infoY += 20;
    snprintf(text, 128, "Attack: %d (+%d)", b->attack, b->attGrow);
    message = TTF_RenderText_Solid(g->display->font, text, c);
    apply_surface(infoX, infoY, message, screen, NULL);
    SDL_FreeSurface(message);
    infoY += 20;
    snprintf(text, 128, "Defense: %d (+%d)", b->defense, b->defGrow);
    message = TTF_RenderText_Solid(g->display->font, text, c);
    apply_surface(infoX, infoY, message, screen, NULL);
    SDL_FreeSurface(message);
    free(text);
}

void DisplayBattle(SDL_Surface* screen, game_controller_t* game)
{
    int xOffset = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
    int enemyY = 50;
    //Enemy beasts
    if(game->battle->isTrainerBattle)
    {
        for(int i = 0; i < 4; i++)
        {
            if(game->battle->enemy->beasts[i] != NULL)
            {
                int x = xOffset + SCREEN_HEIGHT - 170 * i;
                DisplayBeast(screen, game->battle->enemy->beasts[i], x, enemyY, game);
            }
        }
    }
    else
    {
        int x = xOffset + SCREEN_HEIGHT - 170;
        DisplayBeast(screen, game->battle->wildBeast, x, enemyY, game);
    }
    //Player beasts
    int playerX = 10 + xOffset;
    int playerY = 260;
    for(int i = 0; i < 4; i++)
    {
        if(game->player->beasts[i] == NULL)
            break;
        DisplayBeast(screen, game->player->beasts[i], playerX, playerY, game);
        playerX += 170;
    }



    //Side columns
    SDL_Rect r;
    r.x = r.y = 0;
    r.w = xOffset;
    r.h = SCREEN_HEIGHT;
    SDL_FillRect(screen, &r, SDL_MapRGB(screen->format,128,128,128));
    r.x = SCREEN_HEIGHT + xOffset;
    SDL_FillRect(screen, &r, SDL_MapRGB(screen->format,128,128,128));
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
