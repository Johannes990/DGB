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
    const int cellCount = 33;
    const float minCellRadius = 5.0f;
    const float maxCellRadius = 15.0f;
    const int seed = 135;

    seedRandomTime();
    initializeWorldBaseGrid(WORLD_BASE_GRID);
    initializeCells(cellCount, minCellRadius, maxCellRadius, 1);


    printCells(WORLD_INHABITED_CELLS);

    addUndirectedConnection(&WORLD_INHABITED_CELLS[0], &WORLD_INHABITED_CELLS[1]);
    addUndirectedConnection(&WORLD_INHABITED_CELLS[3], &WORLD_INHABITED_CELLS[4]);
    addUndirectedConnection(&WORLD_INHABITED_CELLS[3], &WORLD_INHABITED_CELLS[10]);

    printCells(WORLD_INHABITED_CELLS);


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

                /*
                initializeCellConnectionArray(CELL_CONNECTION_SIZE, worldCellConnectionCount);
                printf("\ninitialized Cell connection array, errno = %d\n", errno);
                for (int a = 0; a < cellCount; a++) {
                    Cell worldCell = WORLD_INHABITED_CELLS[a];
                    printf("cell [%d] pos x: %d, pos y: %d\n", a, worldCell.posX, worldCell.posY);
                }
                // add our 5 connections
                const int conn1[] = {1, 2};

                addConnectedCellGroup(conn1, CELL_CONNECTION_SIZE);
                //printCellConnections(WORLD_CELL_CONNECTIONS);
                */

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

                // draw connection lines
                for (int i = 0; i < cellCount; i++) {
                    Cell cell = WORLD_INHABITED_CELLS[i];

                    
                    for (int connIdx = 0; connIdx < cell.connectionCount; connIdx++) {
                        int startX = cell.baseCellAttrs.posX;
                        int startY = cell.baseCellAttrs.posY;
                        int endX = cell.cellConnections[connIdx].posX;
                        int endY = cell.cellConnections[connIdx].posY;

                        DrawLine(startX, startY, endX, endY, RED);
                    }
                }

                // draw cells
                for (int i = 0; i < cellCount; i++) {
                    Cell cell = WORLD_INHABITED_CELLS[i];

                    // boundaries
                    DrawCircle(
                        cell.baseCellAttrs.posX,
                        cell.baseCellAttrs.posY,
                        cell.baseCellAttrs.radius + 1,
                        BLACK
                    );

                    // circle fills
                    DrawCircle(
                        cell.baseCellAttrs.posX,
                        cell.baseCellAttrs.posY,
                        cell.baseCellAttrs.radius,
                        PURPLE
                    );
                }

                

                /*
                // assuming a connection consists of 2 cells here
                for (int i = 0; i < worldCellConnectionCount; i++) {
                    Cell a = *WORLD_CELL_CONNECTIONS->connectionArray[i][0];
                    Cell b = *WORLD_CELL_CONNECTIONS->connectionArray[i][1];
                    int startX = a.posX;
                    int startY = a.posY;
                    int endX = b.posX;
                    int endY = b.posY;
                    printf("cell a (%d, %d)\n", startX, startY);
                    printf("cell b (%d, %d)\n", endX, endY);
                    //DrawLine(startX, startY, endX, endY, RED);
                }
                

                freeCellConnectionArray(WORLD_CELL_CONNECTIONS);
                printf("errno = %d", errno);
                */

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
