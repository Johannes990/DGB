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
#include "world_connections/WorldCellConnection.h"
#include "./globals/UtilFunctions.h"
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
    const int cellCount = 25;
    const float minCellRadius = 5.0f;
    const float maxCellRadius = 15.0f;
    const int seed = 135;
    int connectionIdx = 0;

    seedRandomTime();
    initializeWorldBaseGrid(WORLD_BASE_GRID);
    initializeCells(cellCount, minCellRadius, maxCellRadius, 1);

    //spawnRandomUndirectedConnections(3, WORLD_INHABITED_CELLS, cellCount);

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

                // draw world grid
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

                // handle user input
                if (IsKeyPressed(KEY_W)) {
                    printf("\nAdding new undirected connection");
                    addRandomUndirectedConnection(cellCount);
                    WorldCellConnection conn = undirectedConnections[globalUndirectedConnections - 1];
                    Cell *a = conn.start;
                    Cell *b = conn.end;
                    printf("\nCell (%d, %d) has longest chain length of %d",
                            a->baseCellAttrs.posX,
                            a->baseCellAttrs.posY,
                            getCellMaxChainLength(*a) - 2
                    );
                    printf("\nCell (%d, %d) has longest chain length of %d",
                            b->baseCellAttrs.posX,
                            b->baseCellAttrs.posY,
                            getCellMaxChainLength(*b) - 2
                    );
                    
                }

                if (IsKeyPressed(KEY_S)) {
                    printf("\nDeleting last undirected connection");
                    deleteLastUndirectedConnection();
                }

                if (IsKeyPressed(KEY_E)) {
                    printf("\nAdding new directed connection");
                    addRandomDirectedConnection(cellCount);
                }

                if (IsKeyPressed(KEY_D)) {
                    printf("\nDeleting last directed connection");
                    deleteLastDirectedConnection(cellCount);
                }

                // draw connections
                // directed
                for (int dir_idx = 0; dir_idx < globalDirectedConnections; dir_idx++) {
                    WorldCellConnection connection = directedConnections[dir_idx];
                    Cell *start = connection.start;
                    Cell *end = connection.end;
                    DrawLine(
                        start->baseCellAttrs.posX,
                        start->baseCellAttrs.posY,
                        end->baseCellAttrs.posX,
                        end->baseCellAttrs.posY,
                        RED
                    );
                }

                // undirected
                for (int udir_idx = 0; udir_idx < globalUndirectedConnections; udir_idx++) {
                    WorldCellConnection connection = undirectedConnections[udir_idx];
                    Cell *start = connection.start;
                    Cell *end = connection.end;
                    DrawLine(
                        start->baseCellAttrs.posX,
                        start->baseCellAttrs.posY,
                        end->baseCellAttrs.posX,
                        end->baseCellAttrs.posY,
                        BLUE
                    );
                }

                // handle connection dynamics
                recalculateCellRadii();

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
