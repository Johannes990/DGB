#ifndef CELLCONNECTIONS_H
#define CELLCONNECTIONS_H

#include "../world_objects/Cell.h"
#include "../globals/Constants.h"
#include "../globals/Errors.h"
#include "../globals/UtilFunctions.h"
#include "../world/World.h"



void addUndirectedConnection(Cell *a, Cell *b);
void addRandomUndirectedConnection(int cellCount);
void removeUndirectedConnection(Cell* a, Cell* b);
void addDirectedConnection(Cell *a, const Cell b);
void addRandomDirectedConnection(int cellCount);
void removeDirectedConnection(Cell *a, const Cell b);
void spawnRandomUndirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount);
void spawnRandomDirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount);

#endif
