#ifndef CELL_H
#define CELL_H

#include "BaseCell.h"
#include "../globals/Constants.h"

typedef struct Cell {
    BaseCell baseCellAttrs;
    BaseCell cellConnections[MAX_CELL_CONNECTION_COUNT];
    int connectionCount;
} Cell;

#endif
