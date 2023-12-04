#include "Obstacle.h"
#include "raymath.h"

Obstacle::Obstacle(Vector2 pos, Texture2D tex)
{
  world_pos = pos;
  texture = tex;

  scale = 4.0f;
}

void Obstacle::Render(Vector2 hero_pos)
{
  Vector2 screen_pos = Vector2Subtract(world_pos, hero_pos);

  DrawTextureEx(texture, screen_pos, 0.0, scale, WHITE);
}

Rectangle Obstacle::get_collision_rec(Vector2 hero_pos)
{
  Vector2 screen_pos = Vector2Subtract(world_pos, hero_pos);

  return Rectangle{screen_pos.x, screen_pos.y, static_cast<float>(texture.width) * scale, static_cast<float>(texture.height) * scale};
}