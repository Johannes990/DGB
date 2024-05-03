#include <stdio.h>
#include "World.h"


// local declarations
static void getRandomCellPosition(int posArray[], int lowX, int highX, int lowY, int highY);
static void initializeCellAtIdx(WorldNode *node, float r, int idx);

// world variables
WorldNode WORLD_BASE_GRID[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];
Cell WORLD_INHABITED_CELLS[WORLD_MAX_ENTITY_COUNT];
int globalCells = 0;

// public function definitions
void printWorld(WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]) {
    for (int i = 0; i < WORLD_NODECOUNT_X ; i++) {
        for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
            printf("Node[%d][%d]\tx: %d\ty: %d\toccupied: %d\n",
                    i,
                    j,
                    world[i][j].posX,
                    world[i][j].posY,
                    world[i][j].occupied);
        }
    }
}

void printCells(Cell worldCells[WORLD_MAX_ENTITY_COUNT]) {
    for (int i = 0; i < globalCells; i++) {
        Cell cell = WORLD_INHABITED_CELLS[i];
        printf("Cell[%d]\t:x %d\ty: %d\tradius: %f\tconnections: %d\n",
                i,
                cell.baseCellAttrs.posX,
                cell.baseCellAttrs.posY,
                cell.baseCellAttrs.radius,
                cell.connectionCount);
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

        initializeCellAtIdx(node, 5.0f, i);
        node->occupied = 1;
    }

    globalCells = cellCount;
}

void recalculateCellRadii() {
    if (globalCells == 0) {
        errno = ERROR_WORLD_NO_INHABITED_CELLS;
        return;
    }

    for (int i = 0; i < globalCells; i++) {
        Cell *cell = &WORLD_INHABITED_CELLS[i];
        if (cell->connectionCount == 0) {
            continue;
        }

        float radius = calculateCellRadius(cell);
        cell->baseCellAttrs.radius = radius;
    }
}

// private function definitions
static void getRandomCellPosition(int posArray[], int lowX, int highX, int lowY, int highY) {
    int x = randIntInRange(lowX, highX - 1);
    int y = randIntInRange(lowY, highY - 1);
    posArray[0] = x;
    posArray[1] = y;
}

static void initializeCellAtIdx(WorldNode *node, float r, int idx) {
    WORLD_INHABITED_CELLS[idx].baseCellAttrs.posX = node->posX;
    WORLD_INHABITED_CELLS[idx].baseCellAttrs.posY = node->posY;
    WORLD_INHABITED_CELLS[idx].baseCellAttrs.radius = r;
    WORLD_INHABITED_CELLS[idx].connectionCount = 0;
}
