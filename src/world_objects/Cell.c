#include "Cell.h"
#include <stdlib.h>
#include <math.h>


float calculateCellRadius(Cell* cell) {
    int connections = cell.connectionCount;
    float radius = M_PI * sqrt(connections);
    return radius;
}
