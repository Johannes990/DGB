#ifndef WORLD_H
#define WORLD_H

#include "WorldNode.h"

// constants
#define X_PAD 100
#define Y_PAD 100
#define WORLD_NODESPACING 20
#define WORLD_NODECOUNT_Y 25
#define WORLD_NODECOUNT_X 25
#define WORLD_WIDTH ((WORLD_NODESPACING * WORLD_NODECOUNT_X) + (2 * WORLD_NODESPACING) + (2 * X_PAD))
#define WORLD_HEIGHT ((WORLD_NODESPACING * WORLD_NODECOUNT_Y) + (2 * WORLD_NODESPACING) + (2 * Y_PAD))
#define WORLD_MAX_ENTITY_COUNT WORLD_NODECOUNT_X * WORLD_NODECOUNT_Y

// world objects
extern struct Cell WORLD_INHABITED_CELLS[WORLD_MAX_ENTITY_COUNT];
extern struct WorldNode WORLD_BASE_GRID[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];

// function declarations
void printWorld(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y], int sizeX, int sizeY);
void constructWorldBaseGrid(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]);
void seedCells(int cellCount, int cellRadius, float clearRadius, int seed);
int randIntInRange(int low, int high);

#endif