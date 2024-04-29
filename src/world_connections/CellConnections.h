#ifndef CELLCONNECTIONS_H
#define CELLCONNECTIONS_H

#include "../world_objects/Cell.h"

// constants
#define CELL_CONNECTION_SIZE 2
#define MAX_CELL_CONNECTION_COUNT 1000

typedef struct CellConnections {
    Cell*** connectionArray; // pointer to a 2D array of pointers to Cell
    int connectionCount;
    int connectionSize;
} CellConnections;

CellConnections* createCellConnectionArray(int connectionSize, int connectionCount);
void freeCellConnectionArray(CellConnections* connections);
void addConnection(CellConnections* CellConnections, Cell** connectedCells);

#endif