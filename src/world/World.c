#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "WorldNode.h"
#include "World.h"
#include "../errorhandling/Errors.h"


// world array
struct WorldNode WORLD_BASE_GRID[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];
struct Cell WORLD_INHABITED_CELLS[WORLD_MAX_ENTITY_COUNT];

// function definitions
void printWorld(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y], int sizeX, int sizeY) {
    for (int i = 0; i < sizeX ; i++) {
        for (int j = 0; j < sizeY; j++) {
            printf("Node[%d][%d]\tx: %d\ty: %d\n",i, j, world[i][j].posX, world[i][j].posY);
        }
    }
}

void constructWorldBaseGrid(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]) {
    for (int i = 0; i < WORLD_NODECOUNT_X; i++) {
        for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
            world[i][j].posX = X_PAD + ((i + 1) * WORLD_NODESPACING);
            world[i][j].posY = Y_PAD + ((j + 1) * WORLD_NODESPACING);
            world[i][j].occupied = 0;
        }
    }
}

void seedCells(int cellCount, int cellRadius, float clearRadius, int seed) {
    if (cellCount > WORLD_MAX_ENTITY_COUNT) {
        errno = ERROR_ENTITY_LIMIT_EXCEEDED;
        return;
    }

    // should include some error handling here for when the
    // clearRadius is taken into account as well

    if (cellRadius < 1) {
        errno = ERROR_MIN_CELL_RADIUS;
        return;
    }

    if (cellRadius >= WORLD_NODESPACING) {
        errno = ERROR_MAX_CELL_RADIUS;
        return;
    }

    for (int i = 0; i < cellCount; i++) {
        int nodePosX = randIntInRange(0, WORLD_NODECOUNT_X);
        int nodePosY = randIntInRange(0, WORLD_NODECOUNT_Y);
        int r = randIntInRange(1, cellRadius);
        WorldNode node = WORLD_BASE_GRID[nodePosX][nodePosY];

        while (node.occupied == 1) {
            int nodePosX = randIntInRange(0, WORLD_NODECOUNT_X);
            int nodePosY = randIntInRange(0, WORLD_NODECOUNT_Y);
            node = WORLD_BASE_GRID[nodePosX][nodePosY];
        }

        WORLD_INHABITED_CELLS[i].posX = node.posX;
        WORLD_INHABITED_CELLS[i].posY = node.posY;
        WORLD_INHABITED_CELLS[i].radius = r;
        node.occupied = 1;
    }   
}

int randIntInRange(int low, int high) {
    return (rand() % (high - low + 1)) + low;
}
