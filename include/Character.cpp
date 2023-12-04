#include "Character.h"
#include "raymath.h"

// Use member initializer list to initialize member vairiables
// initializes before entering the constructor body.
Character::Character() : texture(), idle(), move(),
                         world_pos(), last_frame(), velocity(),
                         right_left(1.0f), running_time(0.0f), width(0.0f),
                         height(0.0f), update_time(1.0f / 12.0f), speed(0.0f), scale(4.0f),
                         frame(0), max_frames_idle(0), max_frames_move(0), is_alive(true)
{
}

Vector2 Character::get_world_pos()
{
  return world_pos;
}

void Character::stop_moving()
{
  world_pos = last_frame;
}

Rectangle Character::get_collision_rectangle()
{
  return Rectangle{get_screen_pos().x, get_screen_pos().y, static_cast<float>(texture.width) - 30, static_cast<float>(texture.height) * scale};
}

void Character::set_is_alive(bool alive)
{
  is_alive = alive;
}

bool Character::get_is_alive()
{
  return is_alive;
}

void Character::tick(float delta_time)
{
  last_frame = world_pos;

  // Update animation frame
  running_time += delta_time;

  if (running_time >= update_time)
  {
    frame++;
    running_time = 0.0f;

    // Check if Character is moving or idle
    if (frame >= (Vector2Length(velocity) != 0.0f ? max_frames_move : max_frames_idle))
    {
      frame = 0;
    }
  }

  // Normalize dir for uniform movement and scale to change the speed. Then add vectors to get new position.
  if (Vector2Length(velocity) != 0.0)
  {
    world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(velocity), speed));

    // Check the direction of the sprite
    if (velocity.x < 0.0f)
    {
      right_left = -1.0f;
    }
    else
    {
      right_left = 1.0f;
    }

    texture = move;
    width = texture.width / max_frames_move;
  }
  else
  {
    texture = idle;
    width = texture.width / max_frames_idle;
  }

  velocity = {};

  // Draw the main character
  Rectangle src;
  src.x = frame * width;
  src.y = 0.0f;
  src.width = right_left * width;
  src.height = height;

  Rectangle dest;
  dest.x = get_screen_pos().x;
  dest.y = get_screen_pos().y;
  dest.width = scale * width;
  dest.height = scale * height;

  Vector2 origin;
  origin.x = 0.0f;
  origin.y = 0.0f;

  DrawTexturePro(texture, src, dest, origin, 0.f, WHITE);
}