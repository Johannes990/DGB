#ifndef WORLD_H
#define WORLD_H

#include "WorldNode.h"
#include "../world_objects/Cell.h"
#include "../world_connections/CellConnections.h"
#include "../globals/Errors.h"
#include "../globals/Constants.h"
#include "../globals/UtilFunctions.h"
#include <errno.h>


// world objects
extern Cell WORLD_INHABITED_CELLS[WORLD_MAX_ENTITY_COUNT];
extern WorldNode WORLD_BASE_GRID[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]; 

// function declarations
void printWorld(WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]);
void printCells(Cell worldCells[]);
void initializeWorldBaseGrid(WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]);
void initializeCells(int cellCount, float minCellRadius, float maxCellRadius, float clearRadius);

#endif
