#ifndef CELLCONNECTIONS_H
#define CELLCONNECTIONS_H

#include "../world_dwellers/Cell.h"

// constants
#define MAX_CONNECTION_SIZE 2
#define MAX_CONNECTION_COUNT 1000

typedef struct CellConnections {
    Cell*** connectionArray; // pointer to a 2D array of pointers to Cell
    int connectionCount;
    int connectionSize;
} CellConnections;

CellConnections* createCellConnectionArray(int connectionSize, int connectionCount);
void freeCellConnectionArray(CellConnections* connections);

#endif