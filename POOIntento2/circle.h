
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
