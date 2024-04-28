#include <stdio.h>
#include "WorldNode.c"

#define WORLD_NODESPACING 10
#define WORLD_NODECOUNT_Y 25
#define WORLD_NODECOUNT_X 25

#define WORLD_WIDTH = (WORLD_NODESPACING * WORLD_NODECOUNT_Y) + (2 * WORLD_NODESPACING)
#define WORLD_HEIGHT = (WORLD_NODESPACING * WORLD_NODECOUNT_X) + (2 * WORLD_NODESPACING)



int main() {
    struct WorldNode WORLD_ARRAY[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];

    for (int i = 0; i < WORLD_NODECOUNT_X; i++) {
        for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
            printf("%d, %d\n", WORLD_ARRAY[i][j].pos_x, WORLD_ARRAY[i][j].pos_y);
        }
    }
    return 0;
}


