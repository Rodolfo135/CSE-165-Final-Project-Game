#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D move_tex, int idle_frame, int move_frame, float enemy_speed)
{
  world_pos = pos;
  texture = idle_tex;
  idle = idle_tex;
  move = move_tex;

  max_frames_idle = idle_frame;
  max_frames_move = move_frame;

  width = texture.width / max_frames_idle;
  height = texture.height;

  damage_rate = 30.0f;
  track_radius = 20.0f;

  speed = enemy_speed;
}

void Enemy::tick(float delta_time)
{

  if (!get_is_alive())
  {
    return;
  }

  /*
  Track player by using vector operations.
  Let v1 be the position of enemy, and v2 be the vector that points from the enemy to the player. Then to get the
  vector from the origin to the player we simply add v1 + v2 = v3. Where v3 is the positional vector of the player.

  So if we want to compute v2 we subtract v1 - v3 = v2. This is the vector that will track the player and move the enemy closer to the player.
  */

  // Normalization and scaling done in base class
  velocity = Vector2Subtract(target->get_screen_pos(), get_screen_pos());

  if (Vector2Length(velocity) <= track_radius)
  {
    velocity = {};
  }

  // Use parent class tick functionality
  Character::tick(delta_time);

  if (CheckCollisionRecs(target->get_collision_rectangle(), get_collision_rectangle()))
  {
    // If the enemy and the player collision boxes are overlapping then the player takes damage continuously
    target->taking_damage(damage_rate * delta_time);
  }


  // Draw Collision Rectangle for the enemy
  DrawRectangleLines(get_collision_rectangle().x, get_collision_rectangle().y, get_collision_rectangle().width, get_collision_rectangle().height, RED);

}

void Enemy::set_target(Player *player)
{
  target = player;
}

Vector2 Enemy::get_screen_pos()
{
  /*
Prevent the enemy from being stuck to the player as they move along the map.
Subtract the players positional vector from the enemys and it will stay in the appropriate location.
*/
  return Vector2Subtract(world_pos, target->get_world_pos());
}
