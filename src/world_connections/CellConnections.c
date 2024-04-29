#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "CellConnections.h"
#include "../error_handling/Errors.h"


// public function definitions
CellConnections* createCellConnectionArray(int connectionSize, int connectionCount) {
    CellConnections* cellConnections = malloc(sizeof(CellConnections));

    if (cellConnections == NULL) {
        errno = ERROR_CELLCONNECTIONS_STRUCT_MEMORY_UNALLOCATED;
        return NULL;
    }

    if (connectionSize > MAX_CONNECTION_SIZE) {
        errno = ERROR_CELLCONNECTIONS_CONNECTION_SIZE_OVER_MAX;
        return NULL;
    }

    if (connectionCount > MAX_CONNECTION_COUNT) {
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

// private function definitions
void initializeCellConnectionsArray(CellConnections* cellConnections, int totalConnections, int cellsInConnection) {
    for (int i = 0; i < totalConnections; i++) {
        for (int j = 0; j < cellsInConnection; j++) {
            cellConnections->connectionArray[i][j] = NULL;
        }
    }
}