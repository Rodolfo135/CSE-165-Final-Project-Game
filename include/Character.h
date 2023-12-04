#ifndef CHARACTER_H

#define CHARACTER_H

#include "raylib.h"

/*
Parent class for any Drawable Character to be added in the game.
For ex (the current case): Player and Enemy both derive from Character.
*/

class Character
{
public:
  Character();
  Vector2 get_world_pos();
  Rectangle get_collision_rectangle();

  void stop_moving();
  bool get_is_alive();
  void set_is_alive(bool alive);

  virtual void tick(float delta_time);
  virtual Vector2 get_screen_pos() = 0; // Will be defined in derived classes

protected:
  /*
  Allow derived classes to access these common member variables
  */
  Texture2D texture;
  Texture2D idle;
  Texture2D move;
  Texture2D attack;

  Vector2 world_pos;
  Vector2 last_frame;
  Vector2 velocity;

  float right_left;
  float running_time;
  float width;
  float height;
  float update_time;
  float speed;
  float scale;

  int frame;
  int max_frames_idle;
  int max_frames_move;


private:
bool is_alive;
};

#endif