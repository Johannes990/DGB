#ifndef WORLD_H
#define WORLD_H

#include "WorldNode.h"
#include "../entities/Cell.h"

// constants
#define X_PAD 100
#define Y_PAD 100
#define WORLD_NODESPACING 30
#define WORLD_NODECOUNT_Y 25
#define WORLD_NODECOUNT_X 25
#define WORLD_WIDTH ((WORLD_NODESPACING * WORLD_NODECOUNT_X) + (2 * WORLD_NODESPACING) + (2 * X_PAD))
#define WORLD_HEIGHT ((WORLD_NODESPACING * WORLD_NODECOUNT_Y) + (2 * WORLD_NODESPACING) + (2 * Y_PAD))
#define WORLD_MAX_ENTITY_COUNT WORLD_NODECOUNT_X * WORLD_NODECOUNT_Y

// world objects
extern Cell WORLD_INHABITED_CELLS[WORLD_MAX_ENTITY_COUNT];
extern WorldNode WORLD_BASE_GRID[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];

// function declarations
void printWorld(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]);
void constructWorldBaseGrid(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]);
void seedCells(int cellCount, float minCellRadius, float maxCellRadius, float clearRadius);
void createCellConnectionsFixedAmount(int connectionCount, int cellCount);

#endif