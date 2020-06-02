#include "game.h"
#include "quadtree.h"
#include <stdio.h>

int main(void) 
{  
    Game* game;
    do {
        game = init_Game();
        printf("%d\n", maxDepth(game->players[0]->map->qt));
        printf("%d\n", maxDepth(game->players[1]->map->qt));
        do
            playTurn_Game(game);
        while(!over_Game(game));
    } while(!exit_Game(game));
    return 0;
}
