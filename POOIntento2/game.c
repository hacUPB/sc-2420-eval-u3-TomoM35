
#include "game.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void game_initialize(Game* game) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }

    game->window = SDL_CreateWindow("Juego de Esquivar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    game->active_circles = 1;
    game->last_add_time = SDL_GetTicks();
    game->game_over = false;

    player_initialize(&game->player);
    circle_initialize(&game->circles[0]);
}

void game_update(Game* game) {
    Uint32 current_time = SDL_GetTicks();
    if ((current_time - game->last_add_time) > 5000 && game->active_circles < 25) {
        circle_initialize(&game->circles[game->active_circles]);
        game->active_circles++;
        game->last_add_time = current_time;
    }

    for (int i = 0; i < game->active_circles; i++) {
        game->circles[i].entity.y += game->circles[i].entity.vel_y;
        if (game->circles[i].entity.y > 600) {
            circle_initialize(&game->circles[i]);
        }

        if (circle_detect_collision(&game->circles[i], &game->player.entity)) {
            game->game_over = true;
        }
    }

    entity_update(&game->player.entity);
}

void game_render(Game* game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    entity_render(&game->player.entity, game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    for (int i = 0; i < game->active_circles; i++) {
        circle_render(&game->circles[i], game->renderer);
    }

    SDL_RenderPresent(game->renderer);
}

void game_run(Game* game) {
    bool running = true;
    SDL_Event event;

    while (running && !game->game_over) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else {
                player_handle_input(&game->player, &event);
            }
        }

        game_update(game);
        game_render(game);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}
