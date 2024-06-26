#ifndef CONSTANTS_H
#define CONSTANTS_H

//--------------------------------world constants------------------------------
#define X_PAD 100
#define Y_PAD 100
#define WORLD_NODESPACING 30
#define WORLD_NODECOUNT_Y 25
#define WORLD_NODECOUNT_X 25
#define WORLD_WIDTH ((WORLD_NODESPACING * WORLD_NODECOUNT_X) + (2 * WORLD_NODESPACING) + (2 * X_PAD))
#define WORLD_HEIGHT ((WORLD_NODESPACING * WORLD_NODECOUNT_Y) + (2 * WORLD_NODESPACING) + (2 * Y_PAD))
#define WORLD_MAX_ENTITY_COUNT WORLD_NODECOUNT_X * WORLD_NODECOUNT_Y

//--------------------------------cell connection constants--------------------
#define CELL_CONNECTION_SIZE 10
#define MAX_CELL_CONNECTION_COUNT 1000

#endif
