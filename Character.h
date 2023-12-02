#include "raylib.h"

class Character
{
public:
    // public members here
    Character();
    Vector2 get_world_pos();
    void set_screen_pos(int window_width, int window_height);
    void tick(float delta_time);
    void undo_movement();

private:
    // private members here
    Texture2D texture = LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/idle viking mini -Sheet.png");
    Texture2D idle = LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/idle viking mini -Sheet.png");
    Texture2D move = LoadTexture("C:/Users/Galva/Desktop/Project(game)/characters/HeroAnims.png");

    Vector2 screen_pos{};
    Vector2 world_pos{};
    Vector2 last_frame{};
    
    float right_left = 1.f;
    float running_time = 0.f;
    float width = 0.0;
    float height = 0.0; 
    int frame = 0;
    int max_frames = 8;
    float update_time = 1.f / 12.f;
    float speed = 6.f;
};
