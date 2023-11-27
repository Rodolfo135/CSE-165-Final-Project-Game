#include "raylib.h"
#include "raymath.h"


int main()
{
    // Window dimensions: width x height
    Vector2 dims;
    dims.x = 784;
    dims.y = 784;

    // Initialize our window with dimensions and name
    InitWindow(dims.x, dims.y, "Botched Rogue-Light Game");

    // Load the world map: 24 x 24 where each block in the grid is 32 x 32.
    // Note: Had to use the complete path. For some reason the relative path wasn't working.
    Texture2D world_map = LoadTexture("C:/Users/Galva/Desktop/Project(game)/tileset/WorldMap.png");

    // Game FPS
    SetTargetFPS(60);

    // Game Loop: Run until closed by user (press esc to exit)
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 map_pos;
        map_pos.x = 0.0;
        map_pos.y = 0.0;

        DrawTextureEx(world_map, map_pos, 0.0, 4.0, WHITE);

        EndDrawing();
    }

    CloseWindow();
 }