#include "Cell.h"
#include <stdlib.h>
#include <math.h>
#include <errno.h>


static float radiusFunction1(int cellConnectionCount); 

// public functions
float calculateCellRadius(Cell* cell) {
    return radiusFunction1(cell->connectionCount);
}

int getConnectedCellIdx(const Cell* a, const Cell* b) {
    int bX = b->baseCellAttrs.posX;
    int bY = b->baseCellAttrs.posY;

    for (int i = 0; i < a->connectionCount; i++) {
        const BaseCell* baseCell = &a->cellConnections[i];

        if (baseCell->posX == bX && baseCell->posY == bY) {
            return i;
        }
    }

    errno = ERROR_CELLCONNECTIONS_NO_CONNECTION_BETWEEN_CELLS;
    return -1;
}

void deleteConnectionBaseCellAtIdx(Cell* a, const int idx) {
    for (int i = idx; i < a->connectionCount - 1; ++i) {
        a->cellConnections[i] = a->cellConnections[i + 1];
    }

    a->connectionCount = a->connectionCount - 1;
}


// private functions
static float radiusFunction1(int cellConnectionCount) {
    float radius = 5.0f * sqrt(cellConnectionCount);
    return radius;
}
