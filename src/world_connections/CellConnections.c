#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "CellConnections.h"
#include "../error_handling/Errors.h"

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
        return;
    }

    for (int i = 0; i < cellConnections->connectionCount; i++) {
        for (int j = 0; j < cellConnections->connectionSize; j++) {
            free(cellConnections->connectionArray[i][j]);
        }
        free(cellConnections->connectionArray[i]);
    }
    free(cellConnections->connectionArray);
    free(cellConnections);
}

void addConnection(CellConnections* cellConnections, Cell cellConnectionGroup[]) {
    if (cellConnections == NULL || cellConnectionGroup == NULL) {
        errno = ERROR_GLOBAL_NULLPOINTER_ARGUMENT;
        return;
    }

    int availablePos = findAvailablePosition(cellConnections);

    if (availablePos == -1) {
        return;
    }

    int freeConnIdx = availablePos / cellConnections->connectionSize;

    if (freeConnIdx >= cellConnections->connectionCount) {
        errno = ERROR_CELLCONNECTIONS_NEW_CONNECTION_OVER_MAX_COUNT;
        return;
    }

    for (int i = 0; i < cellConnections->connectionSize; i++) {
        cellConnections->connectionArray[freeConnIdx][i] = &cellConnectionGroup[i];
    }
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
        for (int j = 0; j > cellConnections->connectionSize; j++) {
            if (cellConnections->connectionArray[i][j] == NULL) {
                return i * cellConnections->connectionSize + j;
            }
        }
    }

    errno = ERROR_CELLCONNECTIONS_STRUCT_MEMORY_FULL;
    return -1;
}