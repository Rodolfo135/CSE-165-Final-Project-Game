#include "raylib.h"
#include "raymath.h" // Useful mathematical operations

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

    Vector2 map_pos;
    map_pos.x = 0.0;
    map_pos.y = 0.0;

    // Game FPS
    SetTargetFPS(60);

    float move_scale = 4.0;

    // Game Loop: Run until closed by user (press esc to exit)
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Directions
        Vector2 dir;
        dir.x = 0.0;
        dir.y = 0.0;

        // Controls: Up, Down, Left, Right (WASD).
        if (IsKeyDown(KEY_A))
        {
            dir.x -= 1.0;
        }
        else if (IsKeyDown(KEY_D))
        {
            dir.x += 1.0;
        }
        else if (IsKeyDown(KEY_W))
        {
            dir.y -= 1.0;
        }
        else if (IsKeyDown(KEY_S))
        {
            dir.y += 1.0;
        }

        // Normalize dir for uniform movement and scale to change the speed. Then subtract vectors to get new map position. 
        if (Vector2Length(dir) != 0.0)
        {
            map_pos = Vector2Subtract(map_pos, Vector2Scale(Vector2Normalize(dir), move_scale));
        }

        // Draw map starting at the top-left corner of the window (0,0). Move with key inputs
        DrawTextureEx(world_map, map_pos, 0.0, 3.0, WHITE);

        EndDrawing();
    }

    CloseWindow();
 }
