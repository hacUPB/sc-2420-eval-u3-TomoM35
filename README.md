[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/-g_ni1Wx)
# Documentación del Proyecto
## Unidad 3

Estudiante:  Tomas Mejia
Id:  000466315
---
# Trabajo
## Diagrama de Clases UML
![image](https://github.com/user-attachments/assets/052cf8c3-24d2-45b7-a121-00e89e4fedbc)


## Refactorización del Código:

### player.c
```c

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
```
### player.h
```c

#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

typedef struct {
    Entity entity; // Player hereda de Entity
} Player;

void player_initialize(Player* player);
void player_handle_input(Player* player, SDL_Event* event);

#endif

```
### circle.c
```c

#include "circle.h"
#include <stdlib.h>
#include <math.h>

void circle_initialize(Circle* circle) {
    circle->radius = 20 + rand() % 30;
    entity_initialize(&circle->entity, rand() % (800 - 2 * circle->radius), 0, 2 * circle->radius, 2 * circle->radius, 0, 4 + rand() % 3);
    circle->active = true;
}

bool circle_detect_collision(Circle* circle, Entity* player) {
    int dist_x = player->x + player->width / 2 - circle->entity.x;
    int dist_y = player->y + player->height / 2 - circle->entity.y;
    int distance = dist_x * dist_x + dist_y * dist_y;
    int radius_squared = circle->radius * circle->radius;

    return distance < radius_squared;
}

void circle_render(Circle* circle, SDL_Renderer* renderer) {
    for (int w = 0; w < circle->radius * 2; w++) {
        for (int h = 0; h < circle->radius * 2; h++) {
            int dx = circle->radius - w;
            int dy = circle->radius - h;
            if ((dx * dx + dy * dy) <= (circle->radius * circle->radius)) {
                SDL_RenderDrawPoint(renderer, circle->entity.x + dx, circle->entity.y + dy);
            }
        }
    }
}

```
### circle.h
```c

#ifndef CIRCLE_H
#define CIRCLE_H

#include "entity.h"

typedef struct {
    Entity entity; // Circle hereda de Entity
    int radius;
    bool active;
} Circle;

void circle_initialize(Circle* circle);
bool circle_detect_collision(Circle* circle, Entity* player);
void circle_render(Circle* circle, SDL_Renderer* renderer);

#endif

```
### entity.c
```c

#include "entity.h"

void entity_initialize(Entity* entity, int x, int y, int width, int height, int vel_x, int vel_y) {
    entity->x = x;
    entity->y = y;
    entity->width = width;
    entity->height = height;
    entity->vel_x = vel_x;
    entity->vel_y = vel_y;
}

void entity_update(Entity* entity) {
    entity->x += entity->vel_x;
    entity->y += entity->vel_y;
}

void entity_render(Entity* entity, SDL_Renderer* renderer) {
    SDL_Rect rect = { entity->x, entity->y, entity->width, entity->height };
    SDL_RenderFillRect(renderer, &rect);
}
```
### entity.h
```c

#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <stdbool.h>

typedef struct {
    int x, y;
    int vel_x, vel_y;
    int width, height;
} Entity;

// Métodos para la entidad base
void entity_initialize(Entity* entity, int x, int y, int width, int height, int vel_x, int vel_y);
void entity_update(Entity* entity);
void entity_render(Entity* entity, SDL_Renderer* renderer);

#endif
```
### game.c
```c

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

```
### game.h
```c

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

```
### main.c
```c

#include "game.h"
#include <stdio.h>


int main(int argc, char* argv[]) {
    Game game;
    game_initialize(&game);
    game_run(&game);

    if (game.game_over) {
        printf("Has perdido!\n");
    }

    return 0;
}
```
## Componentes
- La relación entre Player, Circle y Entity se puede ver una herencia, hacinedo  que Player y Circle tengan los atributos y funciones de Entity
- Métodos como entity_initialize, entity_update y entity_render se reutilizan en player.c y circle.c, aprovechando el código ya definido para múltiples tipos de entidades.
- Los atributos de la clase base Entity están encapsulados dentro de la estructura. No son accedidos directamente desde fuera, sino mediante métodos específicos como entity_initialize, entity_update, y entity_render.
- El bucle principal del juego está en game_run (en game.c), y está organizado para llamar a las funciones update y render de las entidades de forma clara y modular.
- La clase Game tiene referencias tanto a Player como a un arreglo de Circle. Esto representa agregación porque Game no puede existir sin instancias de estas entidades, pero las entidades pueden existir independientemente.
- 
## Juego en ventaan 
![image](https://github.com/user-attachments/assets/b4035f62-a328-44f1-aaed-a3c5beb4151a)
