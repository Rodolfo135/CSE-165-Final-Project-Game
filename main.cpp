#include "raylib.h"
#include "raymath.h" // Useful mathematical operations

int main()
{
    // Window dimensions: width x height
    Vector2 dims;
    dims.x = 584;
    dims.y = 584;

    // Initialize our window with dimensions and name
    InitWindow(dims.x, dims.y, "Botched Rogue-Like Game");

    // Load the world map: 24 x 24 where each block in the grid is 32 x 32.
    // Note: Had to use the complete path. For some reason the relative path wasn't working.
    Texture2D world_map = LoadTexture("C:/Users/Galva/Desktop/Project(game)/tileset/WorldMap.png");

    // Starting Map position in window
    Vector2 map_pos;
    map_pos.x = 0.0;
    map_pos.y = 0.0;
    // Speed scalar
    float move_scale = 4.5;


    // Character Creation
    Texture2D viking = LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/idle viking mini -Sheet.png");

    Texture2D viking_idle = LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/idle viking mini -Sheet.png");
    Texture2D viking_moving = LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/HeroAnims.png");

    // Initial Character position is the center of the Window. This scales with the size of the window.
    Vector2 viking_pos;
    viking_pos.x = (float)dims.x/2.0f - 4.0f * (0.5f * (float)viking.width/8.0f);
    viking_pos.y = (float)dims.y/2.0f - 4.0f * (0.5f * (float)viking.height);

    // 1: facing right, -1: facing left
    float right_left = 1.f;

    // Animation variables
    float running_time = 0.0f;
    int frame = 0;
    const int max_frames = 8;
    const float update_time = 1.f/12.f;


    // Game FPS
    SetTargetFPS(60);

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

            // Check the direction of the sprite
            (dir.x < 0.f) ? right_left = -1.f : right_left = 1.f;

            // Based on the outcome of the if statement, we can "move" the character or remain idle
            viking = viking_moving;
        }
        else
        {
            viking = viking_idle;
        }

        // Draw map starting at the top-left corner of the window (0,0). Move with key inputs
        DrawTextureEx(world_map, map_pos, 0.0, 3.0, WHITE);

        // Update animation frame
        running_time += GetFrameTime();

        if (running_time >= update_time)
        {
            frame++;
            running_time = 0.f;

            if (frame > max_frames)
            {
                frame = 0;
            }
        }



        // Draw the main character
        Rectangle src;
        src.x = frame * (float)viking.width/8.f; 
        src.y = 0.f;
        src.width = right_left * (float)viking.width/8.f;
        src.height = (float)viking.height;

        Rectangle dest;
        dest.x = viking_pos.x;
        dest.y = viking_pos.y;
        dest.width = 3.0f * (float)viking.width/8.0f;
        dest.height = 3.0f * (float)viking.height;

        Vector2 origin;
        origin.x = 0.0;
        origin.y = 0.0;

        DrawTexturePro(viking, src, dest, origin, 0.f, WHITE);

        EndDrawing();
    }

    CloseWindow();
 }
