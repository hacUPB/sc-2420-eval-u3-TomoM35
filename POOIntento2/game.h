
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "circle.h"

typedef struct {
    Player player;
    Circle circles[25];
    int active_circles;
    Uint32 last_add_time;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool game_over;
} Game;

void game_initialize(Game* game);
void game_update(Game* game);
void game_render(Game* game);
void game_run(Game* game);

#endif
