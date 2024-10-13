
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
