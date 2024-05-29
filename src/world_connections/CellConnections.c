#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "CellConnections.h"


//--------------------------------local declarations---------------------------
int globalUndirectedConnections = 0;
int globalDirectedConnections = 0;
WorldCellConnection undirectedConnections[MAX_CELL_CONNECTION_COUNT];
WorldCellConnection directedConnections[MAX_CELL_CONNECTION_COUNT];

//--------------------------------local functions------------------------------
void deleteUndirectedConnection(Cell* a, Cell* b) {
    int connIdxForCellA = getConnectedCellIdx(a, b);
    int connIdxForCellB = getConnectedCellIdx(b, a);

    if (connIdxForCellA == -1 || connIdxForCellB == -1) {
        return;
    }
    
    deleteConnectionBaseCellAtIdx(a, connIdxForCellA);
    deleteConnectionBaseCellAtIdx(b, connIdxForCellB);
}

void deleteDirectedConnection(Cell* a, const Cell b) {
    int connIdxForCellA = getConnectedCellIdx(a, &b);

    if (connIdxForCellA == -1) {
        return;
    }

    deleteConnectionBaseCellAtIdx(a, connIdxForCellA);
}

//--------------------------------public functions-----------------------------
void addUndirectedConnection(Cell *a, Cell *b) {
    if ((globalUndirectedConnections + globalDirectedConnections) >= MAX_CELL_CONNECTION_COUNT) {
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

    WorldCellConnection connection = { a, b };
    undirectedConnections[globalUndirectedConnections] = connection;

    globalUndirectedConnections++;
}

void addRandomUndirectedConnection(int cellCount) {
    if ((globalUndirectedConnections + globalDirectedConnections) >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    Cell* a = &WORLD_INHABITED_CELLS[randIntInRange(0, cellCount - 1)];
    Cell* b = &WORLD_INHABITED_CELLS[randIntInRange(0, cellCount - 1)];

    while (a->connectionCount >= CELL_CONNECTION_SIZE) {
        a = &WORLD_INHABITED_CELLS[randIntInRange(0, cellCount - 1)];
    }

    while (b->connectionCount >= CELL_CONNECTION_SIZE) {
        b = &WORLD_INHABITED_CELLS[randIntInRange(0, cellCount - 1)];
    }

    addUndirectedConnection(a, b);
}

void deleteLastUndirectedConnection() {
    if (globalUndirectedConnections > 0) {
        WorldCellConnection lastUndirectedConnection = undirectedConnections[globalUndirectedConnections - 1];
        deleteUndirectedConnection(lastUndirectedConnection.start, lastUndirectedConnection.end);
        globalUndirectedConnections--;
    }
}

void addDirectedConnection(Cell *a, const Cell *b) {
    if ((globalUndirectedConnections + globalDirectedConnections) >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    if (a->connectionCount >= CELL_CONNECTION_SIZE) {
        errno = ERROR_CELLCONNECTIONS_CONNECTION_SIZE_OVER_MAX;
        return;
    }

    a->cellConnections[a->connectionCount] = b->baseCellAttrs;
    a->connectionCount++;

    WorldCellConnection connection = { a, b };
    directedConnections[globalDirectedConnections] = connection;

    globalDirectedConnections++;
}

void addRandomDirectedConnection(int cellCount) {
    if ((globalUndirectedConnections + globalDirectedConnections) >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    Cell* a = &WORLD_INHABITED_CELLS[randIntInRange(0, cellCount - 1)];

    while (a->connectionCount >= CELL_CONNECTION_SIZE) {
        a = &WORLD_INHABITED_CELLS[randIntInRange(0, cellCount - 1)];
    }

    Cell* b = &WORLD_INHABITED_CELLS[randIntInRange(0, cellCount - 1)];

    addDirectedConnection(a, b);
}

void deleteLastDirectedConnection() {
    if (globalDirectedConnections > 0) {
        WorldCellConnection lastDirectedConnection = directedConnections[globalDirectedConnections - 1];
        deleteDirectedConnection(lastDirectedConnection.start, *lastDirectedConnection.end);
        globalDirectedConnections--;
    }
}

void spawnRandomUndirectedConnections(int spawnCount, Cell worldCells[], int currentCellCount) {
    if ((globalUndirectedConnections + globalDirectedConnections + spawnCount) >= MAX_CELL_CONNECTION_COUNT) {
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
    if ((globalUndirectedConnections = globalDirectedConnections + spawnCount) >= MAX_CELL_CONNECTION_COUNT) {
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

        addDirectedConnection(&worldCells[cell1Idx], &worldCells[cell2Idx]);
    }
}
