#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "Character.h"
#include "Player.h"

/*
Enemy inherits publically from Character
*/

class Enemy : public Character
{
public:
  Enemy(Vector2 pos, Texture2D idle_tex, Texture2D move_tex, int idle_frame, int move_frame, float enemy_speed);

  void set_target(Player* player);

  virtual void tick(float delta_time) override;
  virtual Vector2 get_screen_pos() override;

private:
  Player* target;
  float damage_rate;
  float track_radius;
};

#endif