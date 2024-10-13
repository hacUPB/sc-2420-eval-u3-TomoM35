
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
