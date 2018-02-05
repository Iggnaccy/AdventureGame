#include "game.h"
#include <stdio.h>
#include <math.h>

static int textboxReturnScene;
static char* textboxText;
static int lastX, lastY;

game_controller_t* NewGame()
{
    game_controller_t* g = malloc(sizeof(game_controller_t));
    g->achievements = 0;
    g->controls = DefaultControls();
    g->state = MAINMENU;
    g->player = CreatePlayer("");
    g->map = DefineMap(g->map);
    g->display = malloc(sizeof(display_t) + TEXTURE_COUNT * sizeof(SDL_Surface*));
    LoadTexturesAndFont(g->display);
    char** dialog = {"Dialog line 1","Dialog line 2","Dialog line 3","Dialog line 4"};
    g->NPCs[0] = DefineNPC(0,0,0,0,0,0,0,dialog,NULL);
    g->tiles = malloc(sizeof(tile_t*) * TEXTURE_COUNT);
    SetAllTiles(g->tiles);
    g->battle = malloc(sizeof(battle_controller_t));
    g->battle->p = g->player;
    g->battle->enemy = NULL;
    g->battle->wildBeast = NULL;
    g->battle->isTrainerBattle = false;
    beast_t* b = DefineBeast("Fighter beast 1", FIGHTER, 50, 4, 25, 2, 15, 3, 18, 2, 4, 1);
    AddBeast(g->player, b);
    textboxReturnScene = WORLD;
    textboxText = NULL;
    return g;
}

static void Collision(game_controller_t* g)
{
    player_t* p = g->player;
    location_t* l = g->map->locations[p->locID];
    tile_t** t = g->tiles;
    int iX, iY;
    iX = (int)(p->x);
    iY = (int)(p->y);
    int tileType = l->tiles[iX][iY];
    if(!t[tileType]->passable)
    {
        double xDist = ((double)iX + 0.5) - p->x;
        double yDist = ((double)iY + 0.5) - p->y;
        if(fabs(xDist) > fabs(yDist))
        {
            if(xDist > 0)
            {
                p->x = (int)p->x - 0.01;
            }
            else p->x = (int)p->x + 1.01;
        }
        else
        {
            if(yDist > 0)
            {
                p->y = (int)p->y - 0.01;
            }
            else p->y = (int)p->y + 1.01;
        }
    }
}

static void ResetScreen(SDL_Surface* screen)
{
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
}

bool DoFrame(SDL_Surface* screen, game_controller_t* g)
{
    SDL_Event event;
    switch(g->state)
    {
    case MAINMENU:
        ResetScreen(screen);
        DisplayMainMenu(screen, g);
        break;
    case NEWGAME:
        ResetScreen(screen);
        //DisplayNewGame(screen, game);
        break;
    case WORLD:
        {
            ResetScreen(screen);
            DisplayWorld(screen, g);
            Uint8* keystates = SDL_GetKeyState(NULL);
            int playerTexID = PLAYER_DOWN;
            if(keystates[SDLK_UP])
            {
                g->player->y -= PLAYER_SPEED;
                if(g->player->y < 0)
                    g->player->y = 0.025;
                playerTexID = PLAYER_UP;
            }
            else if(keystates[SDLK_DOWN])
            {
                g->player->y += PLAYER_SPEED;
                if(g->player->y > (g->map->locations[g->player->locID]->y))
                {
                    g->player->y = (double)g->map->locations[g->player->locID]->y - 0.025;
                }
                playerTexID = PLAYER_DOWN;
            }
            if(keystates[SDLK_LEFT])
            {
                g->player->x -= PLAYER_SPEED;
                if(g->player->x < 0)
                    g->player->x = 0.025;
                playerTexID = PLAYER_LEFT;
            }
            else if(keystates[SDLK_RIGHT])
            {
                g->player->x += PLAYER_SPEED;
                if(g->player->x > (g->map->locations[g->player->locID]->x))
                {
                    g->player->x = (double)g->map->locations[g->player->locID]->x - 0.025;
                }
                playerTexID = PLAYER_RIGHT;
            }
            if(keystates[SDLK_t])
            {
                g->state = TEXTBOX;
                textboxReturnScene = WORLD;
            }
            DisplayPlayer(screen, g, playerTexID);
            Collision(g);
            for(int i = 0; i < 8; i++)
            {
                passage_t* p = g->map->locations[g->player->locID]->passages[i];
                if(p->startX == (int)(g->player->x) && p->startY == (int)(g->player->y))
                {
                    g->player->locID = p->loc;
                    g->player->x = p->endX;
                    g->player->y = p->endY;
                }
            }
            if((int)g->player->x != lastX || (int)g->player->y != lastY)
            {
                if(g->tiles[g->map->locations[g->player->locID]->tiles[(int)g->player->x][(int)g->player->y]]->dangerous)
                {
                    int chance = rand() % 100;
                    if(chance < 4)
                    {
                        int type = rand() % 4;
                        char* name = "Wild beast";
                        beast_t* wild = DefineBeast(name, type, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10);
                        BeginWildBattle(g, wild);
                        g->state = BATTLE;
                    }
                }
            }
            lastX = (int)g->player->x;
            lastY = (int)g->player->y;
        }
        break;
    case BATTLE:
        ResetScreen(screen);
        DisplayBattle(screen, g);
        break;
    case DEBUG:
        ResetScreen(screen);
        DisplayDebug(screen, g->display);
        break;
    case TEXTBOX:
        DisplayTextBox(screen, g, "TEST");
        Uint8* keystates = SDL_GetKeyState(NULL);
        if(keystates[g->controls->act] || keystates[g->controls->back])
        {
            g->state = WORLD;
        }
        break;
    default:
        break;
    }


    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            return true;
        }
    }
    return false;
}

void FreeGame(game_controller_t* g)
{
    DestroyControls(g->controls);
    DestroyDisplay(g->display);
    for(int i = NPC_COUNT - 1; i >= 0; i--)
    {
        DestroyNPC(g->NPCs[i]);
    }
    DestroyPlayer(g->player);
}
