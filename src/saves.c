#include "saves.h"
#include "stdio.h"

void SaveGame(int slot, game_controller_t* game)
{
    char* filename;
    snprintf(filename, 64, "saves/save_%d", slot);
    FILE* fp = fopen(filename,"w");

    ///Controls:
    fprintf(fp, "%d %d %d %d\n", game->controls->U, game->controls->R, game->controls->D, game->controls->L);
    fprintf(fp, "%d %d\n", game->controls->act, game->controls->click);

    ///Player:
    //Name:
    fprintf(fp, "%s\n", game->player->name);
    //Position:
    fprintf(fp, "%d %d %d\n", game->player->locID, game->player->x, game->player->y);
    //Beasts:
    for(int i = 0; i < 4; i++)
    {
        beast_t* b = game->player->beasts[i];
        if(b != NULL)
        {
            //Name:
            fprintf(fp, "%s\n", b->name);
            //Damaged stats:
            fprintf(fp, "%d %d %d %d %d\n", b->type, b->lvl, b->experience, b->hp, b->mp);
            //Base stats:
            fprintf(fp, "%d %d %d %d %d\n", b->baseHP, b->baseMP, b->baseAttack, b->baseDefense, b->baseMagic);
            //Growth stats:
            fprintf(fp, "%d %d %d %d %d\n", b->hpGrow, b->mpGrow, b->attGrow, b->defGrow, b->magicGrow);
        }
        else
        {
            //Empty slot
            fprintf(fp, "0\n");
        }
    }
}
