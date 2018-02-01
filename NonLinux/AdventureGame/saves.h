#ifndef _SAVES_H_
#define _SAVES_H_
#include "game.h"

void SaveGame(int slot, game_controller_t* game);
game_controller_t* LoadGame(int slot);

#endif // _SAVES_H_
