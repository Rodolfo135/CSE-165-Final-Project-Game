#include "Character.h"
#include "raymath.h"

// Constructor
Character::Character()
{
  width = texture.width/max_frames;
  height = texture.height;
}

Vector2 Character::get_world_pos()
{
  return world_pos;
}

void Character::set_screen_pos(int window_width, int window_height)
{
    screen_pos.x = (float)window_width / 2.0f - 4.0f * (0.5f * width);

    screen_pos.y = (float)window_height / 2.0f - 4.0f * (0.5f * height);
}

void Character::tick(float delta_time)
{
    last_frame = world_pos;


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

    // Normalize dir for uniform movement and scale to change the speed. Then add vectors to get new position.
    if (Vector2Length(dir) != 0.0)
    {
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(dir), speed));

        // Check the direction of the sprite
        (dir.x < 0.f) ? right_left = -1.f : right_left = 1.f;

        texture = move;
    }
    else
    {
        texture = idle;
    }

    // Update animation frame
    running_time += delta_time;

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
    src.x = frame * width;
    src.y = 0.f;
    src.width = right_left * width;
    src.height = height;

    Rectangle dest;
    dest.x = screen_pos.x;
    dest.y = screen_pos.y;
    dest.width = 4.0f * width;
    dest.height = 4.0f * height;

    Vector2 origin;
    origin.x = 0.0;
    origin.y = 0.0;

    DrawTexturePro(texture, src, dest, origin, 0.f, WHITE);
}


void Character::undo_movement()
{
    world_pos = last_frame;
    
}