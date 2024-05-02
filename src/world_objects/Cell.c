#include "Cell.h"
#include <stdlib.h>
#include <math.h>


static float radiusFunction1(int cellConnectionCount); 

float calculateCellRadius(Cell* cell) {
    return radiusFunction1(cell->connectionCount)
}

// private functions
static float radiusFunction1(int cellConnectionCount) {
    float radius = 5.0f * sqrt(cellConnectionCount);
}
