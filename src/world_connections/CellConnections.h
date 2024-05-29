#ifndef CELLCONNECTIONS_H
#define CELLCONNECTIONS_H

#include "../world_objects/Cell.h"
#include "../globals/Constants.h"
#include "../globals/Errors.h"
#include "../globals/UtilFunctions.h"
#include "../world/World.h"
#include "WorldCellConnection.h"

extern WorldCellConnection undirectedConnections[MAX_CELL_CONNECTION_COUNT];
extern WorldCellConnection directedConnections[MAX_CELL_CONNECTION_COUNT];
extern int globalUndirectedConnections;
extern int globalDirectedConnections;

void addUndirectedConnection(Cell *a, Cell *b);
void addRandomUndirectedConnection(int cellCount);
//void deleteUndirectedConnection(Cell* a, Cell* b);
void deleteLastUndirectedConnection();
void addDirectedConnection(Cell *a, const Cell *b);
void addRandomDirectedConnection(int cellCount);
//void deleteDirectedConnection(Cell *a, const Cell b);
void spawnRandomUndirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount);
void spawnRandomDirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount);
void deleteLastDirectedConnection();

#endif
