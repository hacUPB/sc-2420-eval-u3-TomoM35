
#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

typedef struct {
    Entity entity; // Player hereda de Entity
} Player;

void player_initialize(Player* player);
void player_handle_input(Player* player, SDL_Event* event);

#endif
