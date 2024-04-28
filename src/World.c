#include <stdio.h>
#include "WorldNode.c"

// world constants
#define WORLD_NODESPACING 10
#define WORLD_NODECOUNT_Y 25
#define WORLD_NODECOUNT_X 25
#define WORLD_WIDTH = (WORLD_NODESPACING * WORLD_NODECOUNT_Y) + (2 * WORLD_NODESPACING)
#define WORLD_HEIGHT = (WORLD_NODESPACING * WORLD_NODECOUNT_X) + (2 * WORLD_NODESPACING)

// function declarations
void printWorld(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y], int sizeX, int sizeY);
void setNodePositions(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]);

int main() {
    struct WorldNode WORLD_ARRAY[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];
    //printWorld(WORLD_ARRAY, WORLD_NODECOUNT_X, WORLD_NODECOUNT_Y);
    setNodePositions(WORLD_ARRAY);
    printWorld(WORLD_ARRAY, WORLD_NODECOUNT_X, WORLD_NODECOUNT_Y);
    return 0;
}

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
            world[i][j].posX = (i + 1) * WORLD_NODESPACING;
            world[i][j].posY = (j + 1) * WORLD_NODESPACING;
        }
    }
}
