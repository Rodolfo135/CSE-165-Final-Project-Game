#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "Character.h"

/*
Player inherits publically from character
*/

class Player : public Character
{
public:
    Player(int win_width, int win_height, Texture2D idle_tex, Texture2D move_tex, Texture2D sword_tex,  int idle_frame, int move_frame);

    Rectangle get_sword_collision();

    float set_health_points(float hp);
    float get_health_points();
    void taking_damage(float dmg);

    virtual void tick(float delta_time) override;
    virtual Vector2 get_screen_pos() override;

private:
    int window_width;
    int window_height;
    float health_points;
    Texture2D sword;
    Rectangle sword_collision_rec;
};

#endif