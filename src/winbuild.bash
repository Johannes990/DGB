#!/bin/bash

# Set up directories
INCLUDE_DIR="../include"
LIB_DIR="../lib"
SRC_DIR="./src"

# Compile source files to object files
cc -c globals/UtilFunctions.c -o UtilFunctions.o -I${INCLUDE_DIR}
cc -c world_connections/CellConnections.c -o CellConnections.o -I${INCLUDE_DIR}
cc -c world_objects/Cell.c -o Cell.o -I${INCLUDE_DIR}
cc -c Main.c -o Main.o -I${INCLUDE_DIR}
cc -c world/World.c -o World.o -I${INCLUDE_DIR}

# Link object files and create executable
cc Main.o World.o CellConnections.o UtilFunctions.o Cell.o -o DGB -L${LIB_DIR} -lraylib -lopengl32 -lgdi32 -lwinmm
