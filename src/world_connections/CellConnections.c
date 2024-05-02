#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "CellConnections.h"


// local declarations
int globalConnections = 0;


// public functions
void addUndirectedConnection(Cell *a, Cell *b) {
    if (globalConnections >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    if (a->connectionCount >= CELL_CONNECTION_SIZE || b->connectionCount >= CELL_CONNECTION_SIZE) {
        errno = ERROR_CELLCONNECTIONS_CONNECTION_SIZE_OVER_MAX;
        return;
    }

    a->cellConnections[a->connectionCount] = b->baseCellAttrs;
    a->connectionCount++;
    b->cellConnections[b->connectionCount] = a->baseCellAttrs;
    b->connectionCount++;

    globalConnections++;
}

void addDirectedConnection(Cell *a, const Cell b) {
    if (globalConnections >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    if (a->connectionCount >= CELL_CONNECTION_SIZE) {
        errno = ERROR_CELLCONNECTIONS_CONNECTION_SIZE_OVER_MAX;
        return;
    }

    a->cellConnections[a->connectionCount] = b.baseCellAttrs;
    a->connectionCount++;

    globalConnections++;
}

void spawnRandomUndirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount) {
    if (globalConnections + spawnCount >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    if (currentCellCount < 2) {
        errno = ERROR_CELLCONNECTIONS_WORLD_CONTAINS_SINGULAR_CELL;
        return;
    }

    for (int i = 0; i < spawnCount; i++) {
        int cell1Idx = randIntInRange(0, currentCellCount - 1);
        int cell2Idx = randIntInRange(0, currentCellCount - 1);

        while (cell1Idx == cell2Idx) {
            cell2Idx = randIntInRange(0, currentCellCount - 1);
        }

        addUndirectedConnection(&worldCells[cell1Idx], &worldCells[cell2Idx]);
    }
}

void spawnRandomDirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount) {
    if (globalConnections + spawnCount >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    if (currentCellCount < 2) {
        errno = ERROR_CELLCONNECTIONS_WORLD_CONTAINS_SINGULAR_CELL;
        return;
    }

    for (int i = 0; i < spawnCount; i++) {
        int cell1Idx = randIntInRange(0, currentCellCount - 1);
        int cell2Idx = randIntInRange(0, currentCellCount - 1);

        while (cell1Idx == cell2Idx) {
            cell2Idx = randIntInRange(0, currentCellCount - 1);
        }

        addDirectedConnection(&worldCells[cell1Idx], worldCells[cell2Idx]);
    }
}
