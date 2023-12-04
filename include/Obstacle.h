#include "raylib.h"

class Obstacle
{
public:
  Obstacle(Vector2 pos, Texture2D tex );
  void Render(Vector2 hero_pos);
  Rectangle get_collision_rec(Vector2 hero_pos);

private:
  Texture2D texture;
  Vector2 world_pos;

  float scale;
};