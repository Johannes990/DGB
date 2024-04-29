#ifndef CELLCONNECTIONS_H
#define CELLCONNECTIONS_H

#include "../world_dwellers/Cell.h"

// constants
#define NO_CELLS_SINGLE_CONNECTION 2
#define MAX_CELL_CONNECTIONS 1000

typedef struct CellConnections {
    Cell*** array; // pointer to a 2D array of pointers to Cell
    int connectionSize;
    int connectionCount;
} CellConnections;

CellConnections* createCellConnections(int connectionSize, int connectionCount);
void freeCellConnections(CellConnections* connections);

#endif