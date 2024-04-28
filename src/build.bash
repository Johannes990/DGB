cc -c Main.c -o Main.o
cc -c world/World.c -o World.o

cc Main.o World.o -o MyProg -lraylib -lGL -lm -lpthread -ldl -lrt -lX11