#ifndef CELLCONNECTIONS_H
#define CELLCONNECTIONS_H

#include "../world_objects/Cell.h"
#include "../globals/constants.h"
#include "../globals/Errors.h"

/*
typedef struct CellConnections {
    Cell*** connectionArray; // pointer to a 2D array of pointers to Cell
    int connectionCount;
    int connectionSize;
} CellConnections;

CellConnections* createCellConnectionArray(int connectionSize, int connectionCount);
void freeCellConnectionArray(CellConnections* connections);
void addConnection(CellConnections* CellConnections, Cell connectedCells[]);
void printCellConnections(CellConnections* cellConnections);
*/

void addUndirectedConnection(Cell *a, Cell *b);
void addDirectedConnection(Cell *a, const Cell b);

#endif