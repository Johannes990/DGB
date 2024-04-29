#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "World.h"
#include "../error_handling/Errors.h"


// world arrays
WorldNode WORLD_BASE_GRID[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];
Cell WORLD_INHABITED_CELLS[WORLD_MAX_ENTITY_COUNT];

// public function definitions
void printWorld(WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]) {
    for (int i = 0; i < WORLD_NODECOUNT_X ; i++) {
        for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
            printf("Node[%d][%d]\tx: %d\ty: %d\toccupied: %d\n",i, j, world[i][j].posX, world[i][j].posY, world[i][j].occupied);
        }
    }
}

void constructWorldBaseGrid(WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]) {
    // some bug here, for some reason some cells
    // end up in the top left corner of window
    for (int i = 0; i < WORLD_NODECOUNT_X; i++) {
        for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
            world[i][j].posX = X_PAD + ((i + 1) * WORLD_NODESPACING);
            world[i][j].posY = Y_PAD + ((j + 1) * WORLD_NODESPACING);
            world[i][j].occupied = 0;
        }
    }
}

void seedCells(int cellCount, float minCellRadius, float maxCellRadius, float clearRadius) {
    if (cellCount > WORLD_MAX_ENTITY_COUNT) {
        errno = ERROR_WORLD_CELL_LIMIT_EXCEEDED;
        return;
    }

    // should include some error handling here for when the
    // clearRadius is taken into account as well

    if (maxCellRadius < 1) {
        errno = ERROR_CELL_CELL_RADIUS_UNDER_MIN;
        return;
    }

    if (maxCellRadius >= WORLD_NODESPACING) {
        errno = ERROR_CELL_CELL_RADIUS_OVER_MAX;
        return;
    }

    for (int i = 0; i < cellCount; i++) {
        int cellPos[] = {0, 0};

        getRandomCellPosition(cellPos, 0, WORLD_NODECOUNT_X, 0, WORLD_NODECOUNT_Y);
        WorldNode *node = &WORLD_BASE_GRID[cellPos[0]][cellPos[1]];
        printf("Node[%d][%d], occupancy: %d\n", cellPos[0], cellPos[1], node->occupied);

        while (node->occupied) {
            getRandomCellPosition(cellPos, 0, WORLD_NODECOUNT_X, 0, WORLD_NODECOUNT_Y);
            node = &WORLD_BASE_GRID[cellPos[0]][cellPos[1]];
            printf("Node[%d][%d], occupancy: %d\n", cellPos[0], cellPos[1], node->occupied);
        }

        int r = randIntInRange(1, maxCellRadius);

        WORLD_INHABITED_CELLS[i].posX = node->posX;
        WORLD_INHABITED_CELLS[i].posY = node->posY;
        WORLD_INHABITED_CELLS[i].radius = r;
        node->occupied = 1;
    }   
}

void createCellConnectionsFixedAmount(int connectionCount, int cellCount) {
    for (int i = 0; i < connectionCount; i++) {
        
    }
}

// private function definitions
int randIntInRange(int low, int high) {
    int random = rand();
    return intWrap(random, low, high);
}

int intWrap(int input, int low, int high) {
    return (input % (high - low + 1)) + low;
}

void getRandomCellPosition(int posArray[], int lowX, int highX, int lowY, int highY) {
    int x = randIntInRange(lowX, highX - 1);
    int y = randIntInRange(lowY, highY - 1);
    posArray[0] = x;
    posArray[1] = y;
}

void initializeCell(WorldNode *node, int r, int idx) {
    WORLD_INHABITED_CELLS[idx].posX = node->posX;
    WORLD_INHABITED_CELLS[idx].posY = node->posY;
    WORLD_INHABITED_CELLS[idx].radius = r;
    WORLD_INHABITED_CELLS[idx].connectionCount = 0;
}

void seedRandomInt(int seed) {
    srand(seed);
}

void seedRandomTime() {
    srand((unsigned int)time(NULL));
}

int sizeOfIntArray(int *array) {
    return sizeof(array) / sizeof(array[0]);
}
