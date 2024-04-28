#include <stdio.h>
#include "WorldNode.h"
#include "World.h"

// world array
struct WorldNode WORLD_ARRAY[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];

// function definitions
void printWorld(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y], int sizeX, int sizeY) {
    for (int i = 0; i < sizeX ; i++) {
        for (int j = 0; j < sizeY; j++) {
            printf("Node[%d][%d]\tx: %d\ty: %d\n",i, j, world[i][j].posX, world[i][j].posY);
        }
    }
}

void setNodePositions(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]) {
    for (int i = 0; i < WORLD_NODECOUNT_X; i++) {
        for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
            world[i][j].posX = X_PAD + ((i + 1) * WORLD_NODESPACING);
            world[i][j].posY = Y_PAD + ((j + 1) * WORLD_NODESPACING);
        }
    }
}
