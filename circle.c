
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
