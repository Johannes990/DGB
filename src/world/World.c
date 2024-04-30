#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "World.h"


// local declarations
static int randIntInRange(int low, int high);
static int intWrap(int input, int low, int high);
static void getRandomCellPosition(int posArray[], int lowX, int highX, int lowY, int highY);
static void initializeCell(WorldNode *node, float r, int idx);


// world variables
WorldNode WORLD_BASE_GRID[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];
Cell WORLD_INHABITED_CELLS[WORLD_MAX_ENTITY_COUNT];
CellConnections* WORLD_CELL_CONNECTIONS;
int worldCellConnectionCount;


// public function definitions
void printWorld(WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]) {
    for (int i = 0; i < WORLD_NODECOUNT_X ; i++) {
        for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
            printf("Node[%d][%d]\tx: %d\ty: %d\toccupied: %d\n",i, j, world[i][j].posX, world[i][j].posY, world[i][j].occupied);
        }
    }
}

void initializeWorldBaseGrid(WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]) {
    for (int i = 0; i < WORLD_NODECOUNT_X; i++) {
        for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
            world[i][j].posX = X_PAD + ((i + 1) * WORLD_NODESPACING);
            world[i][j].posY = Y_PAD + ((j + 1) * WORLD_NODESPACING);
            world[i][j].occupied = 0;
        }
    }
}

void initializeCells(int cellCount, float minCellRadius, float maxCellRadius, float clearRadius) {
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

        WORLD_INHABITED_CELLS[i].baseCellAttrs.posX = node->posX;
        WORLD_INHABITED_CELLS[i].baseCellAttrs.posY = node->posY;
        WORLD_INHABITED_CELLS[i].baseCellAttrs.radius = r;
        node->occupied = 1;
    }   
}

void initializeCellConnectionArray(int connectionSize, int connectionCount) {
    worldCellConnectionCount = connectionCount;
    WORLD_CELL_CONNECTIONS = createCellConnectionArray(connectionSize, connectionCount);
}

void addConnectedCellGroup(const int cellIdxArray[], int cellCount) {
    if (WORLD_INHABITED_CELLS == NULL) {
        errno = ERROR_WORLD_INHABITED_CELLS_UNALLOCATED;
        return;
    }

    if (cellIdxArray == NULL) {
        errno = ERROR_GLOBAL_NULLPOINTER_ARGUMENT;
        return;
    }

    if (WORLD_CELL_CONNECTIONS == NULL) {
        errno = ERROR_CELLCONNECTIONS_STRUCT_MEMORY_UNALLOCATED;
        return;
    }

    if (cellCount != CELL_CONNECTION_SIZE) {
        errno = ERROR_WORLD_PROPOSED_CELL_CONNECTION_SIZE_MISMATCH;
        return;
    }

    Cell connectedCells[CELL_CONNECTION_SIZE] = {0};

    // this function needs error handling as well
    // current version for testing purposes
    for (int i = 0; i < CELL_CONNECTION_SIZE; i++) {
        Cell cell = WORLD_INHABITED_CELLS[cellIdxArray[i]];
        printf("found cell with coordinates (%d, %d) for adding into group\n",
                cell.baseCellAttrs.posX,
                cell.baseCellAttrs.posY);
        connectedCells[i] = cell;
    }

    addConnection(WORLD_CELL_CONNECTIONS, connectedCells);
}

void seedRandomInt(int seed) {
    srand(seed);
}

void seedRandomTime() {
    srand((unsigned int)time(NULL));
}

// private function definitions
static int randIntInRange(int low, int high) {
    int random = rand();
    return intWrap(random, low, high);
}

static int intWrap(int input, int low, int high) {
    return (input % (high - low + 1)) + low;
}

static void getRandomCellPosition(int posArray[], int lowX, int highX, int lowY, int highY) {
    int x = randIntInRange(lowX, highX - 1);
    int y = randIntInRange(lowY, highY - 1);
    posArray[0] = x;
    posArray[1] = y;
}

static void initializeCell(WorldNode *node, float r, int idx) {
    WORLD_INHABITED_CELLS[idx].baseCellAttrs.posX = node->posX;
    WORLD_INHABITED_CELLS[idx].baseCellAttrs.posY = node->posY;
    WORLD_INHABITED_CELLS[idx].baseCellAttrs.radius = r;
    WORLD_INHABITED_CELLS[idx].connectionCount = 0;
}
