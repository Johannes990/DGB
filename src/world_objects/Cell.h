#ifndef CELL_H
#define CELL_H

#include "BaseCell.h"
#include "../globals/Constants.h"
#include "../globals/Errors.h"


typedef struct Cell {
    BaseCell baseCellAttrs;
    BaseCell cellConnections[MAX_CELL_CONNECTION_COUNT];
    int connectionCount;
} Cell;


// function declarations
float calculateCellRadius(Cell* cell);
int getConnectedCellIdx(const Cell* a, const Cell* b);
void deleteConnectionBaseCellAtIdx(Cell* a, const int idx);

#endif
