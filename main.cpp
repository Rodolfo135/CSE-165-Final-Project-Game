#include "raylib.h"
#include "raymath.h" // Useful mathematical operations
#include "include/Player.h"
// #include "Obstacle.h" <- Could not get the collisions to properly work, so no extra obstacles are included
#include "include/Enemy.h"
#include <string>
#include <vector>

int main()
{
    // Window dimensions: width x height
    Vector2 window_dims;
    window_dims.x = 684;
    window_dims.y = 684;

    // Initialize our window with dimensions and name
    InitWindow(window_dims.x, window_dims.y, "Botched Rogue-Like Game");

    // Initialize sound
    InitAudioDevice();

    // Load music file
    Music game_music = LoadMusicStream("C:/Users/Galva/Desktop/Project(game)/mixkit-game-level-music-689.wav"); // Generic retro game music

    PlayMusicStream(game_music);

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

    // Number of Hero Animations for idle, moving, and attacking
    int hero_idle_frame = 4;
    int hero_move_frame = 6;

    Player hero(
        window_dims.x,
        window_dims.y,
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/Pink_Monster_Idle_4.png"),
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/Pink_Monster_Run_6.png"),
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/sword.png"),
        hero_idle_frame,
        hero_move_frame);

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

    // Enemy Creation: Does not need to be bats. This can be changed by altering LoadTexture() to a
    // different sprite sheet. If this is done, be sure to check paths, and the frame/speed variables.

    // Number of Enemy Animations for idle and moving
    int enemy_idle_frame = 4;
    int enemy_move_frame = 4;

    Enemy bat1(
        Vector2{},
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        enemy_idle_frame,
        enemy_move_frame,
        3.5f);

    Enemy bat2(
        Vector2{800, 0},
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        enemy_idle_frame,
        enemy_move_frame,
        4.5f);

    Enemy bat3(
        Vector2{400, 800},
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        enemy_idle_frame,
        enemy_move_frame,
        2.5f);

    Enemy bat4(
        Vector2{300, 1000},
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        enemy_idle_frame,
        enemy_move_frame,
        5.5f);

    Enemy bat5(
        Vector2{},
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/SimpleEnemies Bat_Idle Spritesheet.png"),
        enemy_idle_frame,
        enemy_move_frame,
        3.0f);

    std::vector<Enemy*> mobs = { &bat1, &bat2, &bat3, &bat4, &bat5 }; // <- You add more enemies by defining them above and then adding them to this vector, or you can define them directly in the vector by passing arguments to the constructor.

    for (auto mob : mobs)
    {
        mob->set_target(&hero);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // Game FPS
    SetTargetFPS(60);

    // Game Loop: Run until closed by user (press esc to exit)
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        UpdateMusicStream(game_music);

        // Updating map position
        map_pos = Vector2Scale(hero.get_world_pos(), -1);

        // Draw map starting at the top-left corner of the window (0,0). Move with key inputs
        DrawTextureEx(world_map, map_pos, 0.0, map_scale, WHITE);

        if (!hero.get_is_alive())
        {
            // Dead
            DrawText("DEAD!", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else if (!mobs[0]->get_is_alive() && !mobs[1]->get_is_alive() && !mobs[2]->get_is_alive() && !mobs[3]->get_is_alive() && !mobs[4]->get_is_alive())
        {
            // Win Condition
            DrawText("WINNER WINNER!", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;

        }
        else
        {
            // Alive
            std::string hero_health = "Health: ";
            hero_health.append(std::to_string(hero.get_health_points()), 0, 5);
            DrawText(hero_health.c_str(), 55.0f, 45.0f, 40, RED);
        }

        // Update any varaibles dependent on new frames (animations etc)
        hero.tick(GetFrameTime());

        // Check map bounds
        if (hero.get_world_pos().x < 0 || hero.get_world_pos().y < 0 ||
            hero.get_world_pos().x + window_dims.x > world_map.width * map_scale || hero.get_world_pos().y + window_dims.y > world_map.height * map_scale)
        {
            // Stop player
            hero.stop_moving();
        }

        // Update any varaibles dependent on new frames (animations etc)
        for (auto mob : mobs)
        {
            mob->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Check weapon and enemy collisions
            for (auto mob : mobs)
            {
                if (CheckCollisionRecs(mob->get_collision_rectangle(), hero.get_sword_collision()))
                {
                    mob->set_is_alive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadMusicStream(game_music);
    CloseAudioDevice();

    CloseWindow();
}
