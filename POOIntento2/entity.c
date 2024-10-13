
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
