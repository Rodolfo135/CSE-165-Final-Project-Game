#include "raylib.h"
#include "raymath.h" // Useful mathematical operations
#include "Character.h"

int main()
{
    // Window dimensions: width x height
    Vector2 dims;
    dims.x = 684;
    dims.y = 684;

    // Initialize our window with dimensions and name
    InitWindow(dims.x, dims.y, "Final_Proj");

    // Load the world map: 24 x 24 where each block in the grid is 32 x 32.
    // Note: Had to use the complete path. For some reason the relative path wasn't working.
    Texture2D world_map = LoadTexture("C:/Users/Galva/Desktop/Project(game)/tileset/new_world.png");

    // Starting Map position in window
    Vector2 map_pos;
    map_pos.x = 0.0;
    map_pos.y = 0.0;

    // scale
    const float map_scale = 4.0;

    // Character creation
    Character hero;
    hero.set_screen_pos(dims.x, dims.y);

    // Game FPS
    SetTargetFPS(60);

    // Game Loop: Run until closed by user (press esc to exit)
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Updating map position
        map_pos = Vector2Scale(hero.get_world_pos(), -1);

        // Draw map starting at the top-left corner of the window (0,0). Move with key inputs
        DrawTextureEx(world_map, map_pos, 0.0, map_scale, WHITE);

        // Update any varaibles dependent on new frames (animations etc)
        hero.tick(GetFrameTime());

        // Check map bounds
        if(hero.get_world_pos().x < 0 || hero.get_world_pos().y < 0 || 
        hero.get_world_pos().x + dims.x > world_map.width * map_scale || hero.get_world_pos().y + dims.y > world_map.height * map_scale)
        {
            // Stop player
            hero.undo_movement();
        }

        EndDrawing();
    }

    CloseWindow();
} 
