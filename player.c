
#include "player.h"

void player_initialize(Player* player) {
    entity_initialize(&player->entity, 400, 550, 40, 40, 0, 0); // Inicializar player como entidad
}

void player_handle_input(Player* player, SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_a) {
            player->entity.vel_x = -5;
        }
        else if (event->key.keysym.sym == SDLK_d) {
            player->entity.vel_x = 5;
        }
    }
    if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_d) {
            player->entity.vel_x = 0;
        }
    }
}
