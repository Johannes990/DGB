#ifndef WORLD_H
#define WORLD_H

#include "WorldNode.h"

// constants
#define WORLD_NODESPACING 10
#define WORLD_NODECOUNT_Y 25
#define WORLD_NODECOUNT_X 25
#define WORLD_WIDTH ((WORLD_NODESPACING * WORLD_NODECOUNT_Y) + (2 * WORLD_NODESPACING))
#define WORLD_HEIGHT ((WORLD_NODESPACING * WORLD_NODECOUNT_X) + (2 * WORLD_NODESPACING))

extern struct WorldNode WORLD_ARRAY[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y];

// function declarations
void printWorld(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y], int sizeX, int sizeY);
void setNodePositions(struct WorldNode world[WORLD_NODECOUNT_X][WORLD_NODECOUNT_Y]);

#endif