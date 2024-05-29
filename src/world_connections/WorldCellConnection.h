#ifndef WORLDCELLCONNECTION_H
#define WORLDCELLCONNECTION_H

#include "../world_objects/Cell.h" 

typedef struct WorldCellConnection {
    Cell *start;
    Cell *end;
} WorldCellConnection;

#endif
