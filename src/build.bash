cc -c globals/UtilFunctions.c -o UtilFunctions.o
cc -c world_connections/CellConnections.c -o CellConnections.o
cc -c Main.c -o Main.o
cc -c world/World.c -o World.o

cc Main.o World.o CellConnections.o UtilFunctions.o -o DGB -lraylib -lGL -lm -lpthread -ldl -lrt -lX11