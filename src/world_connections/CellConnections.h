#ifndef CELLCONNECTIONS_H
#define CELLCONNECTIONS_H

#include "../world_objects/Cell.h"
#include "../globals/Constants.h"
#include "../globals/Errors.h"
#include "../globals/UtilFunctions.h"
#include "../world/World.h"


void addRandomUndirectedConnection(int cellCount);
void addUndirectedConnection(Cell *a, Cell *b);
void addRandomDirectedConnection(int cellCount);
void addDirectedConnection(Cell *a, const Cell b);
void spawnRandomUndirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount);
void spawnRandomDirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount);

#endif
