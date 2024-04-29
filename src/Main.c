/*******************************************************************************************
*
*   raylib [core] example - 2D Camera platformer
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.0
*
*   Example contributed by arvyy (@arvyy) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 arvyy (@arvyy)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "world/World.h"
#include "world_connections/CellConnections.h"
#include <stdio.h>


//----------------------------------------------------------------------------------
// Module functions declaration
//----------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = WORLD_WIDTH;
    const int screenHeight = WORLD_HEIGHT;
    const int cellCount = 100;
    const float minCellRadius = 5.0f;
    const float maxCellRadius = 15.0f;
    const int seed = 135;
    const int worldConnectionNumber = 5;

    seedRandomTime();
    initializeWorldBaseGrid(WORLD_BASE_GRID);
    initializeCells(cellCount, minCellRadius, maxCellRadius, 1);
    initializeCellConnectionArray(worldConnectionNumber, CELL_CONNECTION_SIZE);
    // add our 5 connections
    const int conn1[] = {1, 2};
    const int conn2[] = {2, 3};
    const int conn3[] = {10, 36};
    const int conn4[] = {5, 60};
    const int conn5[] = {7, 1};
    addConnectedCellGroup(conn1);
    addConnectedCellGroup(conn2);
    addConnectedCellGroup(conn3);
    addConnectedCellGroup(conn4);
    addConnectedCellGroup(conn5);
    printWorld(WORLD_BASE_GRID);

    InitWindow(screenWidth, screenHeight, "");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ screenHeight/2.0f, screenHeight/2.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();


        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
        }

        // Call update camera function by its pointer
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(WHITE);

            BeginMode2D(camera);

                for (int i = 0; i < WORLD_NODECOUNT_X; i++) {
                    for (int j = 0; j < WORLD_NODECOUNT_Y; j++) {
                        DrawCircle(
                            WORLD_BASE_GRID[i][j].posX,
                            WORLD_BASE_GRID[i][j].posY,
                            1.0f,
                            GRAY
                        );
                    }
                }

                for (int j = 0; j < cellCount; j++) {
                    DrawCircle(
                        WORLD_INHABITED_CELLS[j].posX,
                        WORLD_INHABITED_CELLS[j].posY,
                        WORLD_INHABITED_CELLS[j].radius + 1,
                        BLACK
                    );

                    DrawCircle(
                        WORLD_INHABITED_CELLS[j].posX,
                        WORLD_INHABITED_CELLS[j].posY,
                        WORLD_INHABITED_CELLS[j].radius,
                        PURPLE
                    );
                }

                // assuming a connection consists of 2 cells here
                for (int i = 0; i < WORLD_CELL_CONNECTIONS->connectionCount; i++) {
                    Cell* a = WORLD_CELL_CONNECTIONS->connectionArray[i][0];
                    Cell* b = WORLD_CELL_CONNECTIONS->connectionArray[i][1];
                    int startX = a->posX;
                    int startY = a->posY;
                    int endX = b->posX;
                    int endY = b->posY;
                    DrawLine(startX, startY, endX, endY, RED);
                }

            EndMode2D();

            DrawText("World node positions here", 20, 20, 10, BLACK);
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
