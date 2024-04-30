#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "raylib.h"
#include "CellConnections.h"

/*
// local declarations
static void initializeCellConnectionsArray(CellConnections* cellConnections, int totalConnections, int cellsInConnection);
static int findAvailablePosition(CellConnections* cellConnections);


// public function definitions
CellConnections* createCellConnectionArray(int connectionSize, int connectionCount) {
    printf("Creating cellConnectionsArray. connection size: %d, connection count: %d", connectionSize, connectionCount);
    CellConnections* cellConnections = malloc(sizeof(CellConnections));

    if (cellConnections == NULL) {
        errno = ERROR_CELLCONNECTIONS_STRUCT_MEMORY_UNALLOCATED;
        return NULL;
    }

    if (connectionSize > CELL_CONNECTION_SIZE) {
        errno = ERROR_CELLCONNECTIONS_CONNECTION_SIZE_OVER_MAX;
        return NULL;
    }

    if (connectionCount > MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return NULL;
    }
    
    cellConnections->connectionSize = connectionSize;
    cellConnections->connectionCount = connectionCount;
    cellConnections->connectionArray = malloc(connectionCount * sizeof(Cell**));

    if (cellConnections->connectionArray == NULL) {
        errno = ERROR_CELLCONNECTIONS_CELL_POINTER_ARRAY_MEMORY_UNALLOCATED;
        free(cellConnections);
        return NULL;
    }

    for (int i = 0; i < connectionCount; i++) {
        cellConnections->connectionArray[i] = malloc(connectionSize * sizeof(Cell*));

        if (cellConnections->connectionArray[i] == NULL) {
            errno = ERROR_CELLCONNECTIONS_CELL_MEMORY_UNALLOCATED;
            for (int j = 0; j < i; j++) {
                free(cellConnections->connectionArray[j]);
            }
            free(cellConnections->connectionArray);
            free(cellConnections);
            return NULL;
        }
    }

    initializeCellConnectionsArray(cellConnections, connectionCount, connectionSize);

    return cellConnections;
}

void freeCellConnectionArray(CellConnections* cellConnections) {
    if (cellConnections == NULL) {
        errno = ERROR_GLOBAL_NULLPOINTER_ARGUMENT;
        return;
    }
    printf("passes nullpointer\n");
    printf("%d\n", cellConnections->connectionCount);
    printf("%d\n", cellConnections->connectionSize);


    for (int i = 0; i < cellConnections->connectionCount; i++) {
        for (int j = 0; j < cellConnections->connectionSize; j++) {
            printf("entry[][]\n");
            printf("cellPositions[%d][%d]: %p\n", i, j, cellConnections->connectionArray[i][j]);
            if (cellConnections->connectionArray[i][j] == NULL) {
                errno = ERROR_GLOBAL_NULLPOINTER_ARGUMENT;
                return;
            }
            free(cellConnections->connectionArray[i][j]);
            printf("passes[][]\n");

        }
        free(cellConnections->connectionArray[i]);
        printf("passes[]\n");

    }
    free(cellConnections->connectionArray);
    printf("passes array\n");

    free(cellConnections);
    printf("passes cellconnections\n");

}

void addConnection(CellConnections* cellConnections, Cell cellConnectionGroup[]) {
    printf("adding a new connection between the cells\n");
    if (cellConnections == NULL || cellConnectionGroup == NULL) {
        errno = ERROR_GLOBAL_NULLPOINTER_ARGUMENT;
        return;
    }

    int availablePos = findAvailablePosition(cellConnections);
    printf("found available index %d\n", availablePos);

    if (availablePos == -1) {
        return;
    }

    int freeConnIdx = availablePos / cellConnections->connectionSize;
        printf("available spot in CellConnections %d\n", freeConnIdx);


    if (freeConnIdx >= cellConnections->connectionCount) {
        errno = ERROR_CELLCONNECTIONS_NEW_CONNECTION_OVER_MAX_COUNT;
        return;
    }

    for (int i = 0; i < cellConnections->connectionSize; i++) {
        cellConnections->connectionArray[freeConnIdx][i] = &cellConnectionGroup[i];
    }
}

void printCellConnections(CellConnections* cellConnections) {
    if (cellConnections == NULL) {
        printf("cellConnections is null!!\n");
        return;
    }
    int connections = cellConnections->connectionCount;
    int cellsPerConnection = cellConnections->connectionSize;
    printf("cell connection struct has:\n");
    printf("\t%d total connection spots\n", connections);
    printf("\t%d cells per connection\n", cellsPerConnection);

    for (int i = 0; i < connections; i++) {
        Cell cell1 = *cellConnections->connectionArray[i][0];
        Cell cell2 = *cellConnections->connectionArray[i][1];
        printf("cell1 x: %d, y: %d", cell1.baseCellAttrs.posX, cell1.baseCellAttrs.posY);
        printf("cell2 x: %d, y: %d\n", cell2.baseCellAttrs.posX, cell2.baseCellAttrs.posY);

        //DrawLine(cell1.posX, cell1.posY, cell2.posX, cell2.posY, RED);
    }

    printf("\n");
}

// private function definitions
static void initializeCellConnectionsArray(CellConnections* cellConnections, int totalConnections, int cellsInConnection) {
    for (int i = 0; i < totalConnections; i++) {
        for (int j = 0; j < cellsInConnection; j++) {
            cellConnections->connectionArray[i][j] = NULL;
        }
    }
}

static int findAvailablePosition(CellConnections* cellConnections) {
    for (int i = 0; i < cellConnections->connectionCount; i++) {
        for (int j = 0; j < cellConnections->connectionSize; j++) {
            if (cellConnections->connectionArray[i][j] == NULL) {
                return i * cellConnections->connectionSize + j;
            }
        }
    }

    errno = ERROR_CELLCONNECTIONS_STRUCT_MEMORY_FULL;
    return -1;
}
*/

// local declarations
int globalConnections = 0;


// public functions
void addUndirectedConnection(Cell a, Cell b) {
    if (globalConnections >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    if (a.connectionCount >= CELL_CONNECTION_SIZE || b.connectionCount >= CELL_CONNECTION_SIZE) {
        errno = ERROR_CELLCONNECTIONS_CONNECTION_SIZE_OVER_MAX;
        return;
    }

    a.cellConnections[a.connectionCount] = b.baseCellAttrs;
    b.cellConnections[b.connectionCount] = a.baseCellAttrs;
    globalConnections++;
}

void addDirectedConnection(Cell a, const Cell b) {
    if (globalConnections >= MAX_CELL_CONNECTION_COUNT) {
        errno = ERROR_CELLCONNECTIONS_CONNECTIONS_OVER_MAX;
        return;
    }

    if (a.connectionCount >= CELL_CONNECTION_SIZE) {
        errno = ERROR_CELLCONNECTIONS_CONNECTION_SIZE_OVER_MAX;
        return;
    }

    a.cellConnections[a.connectionCount] = b.baseCellAttrs;
    globalConnections++;
}