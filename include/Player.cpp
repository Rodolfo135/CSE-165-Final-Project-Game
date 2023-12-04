#include "Player.h"
#include "raymath.h"

// Constructor
Player::Player(int win_width, int win_height, Texture2D idle_tex, Texture2D move_tex, Texture2D sword_tex,int idle_frame, int move_frame)
{
    texture = idle_tex;
    idle = idle_tex;
    move = move_tex;
    sword = sword_tex;

    window_width = win_width;
    window_height = win_height;

    max_frames_idle = idle_frame;
    max_frames_move = move_frame;

    width = texture.width / max_frames_idle;
    height = texture.height;

    health_points = 100.0f;

    speed = 5.0;
}

Vector2 Player::get_screen_pos()
{
    return Vector2{
        static_cast<float>(window_width) / 2.0f - scale * (0.5f * width),
        static_cast<float>(window_height) / 2.0f - scale * (0.5f * height)};
}

Rectangle Player::get_sword_collision()
{

    return sword_collision_rec;
}

float Player::set_health_points(float hp)
{
    // Used when increasing the players health points
    health_points = hp;
}

float Player::get_health_points()
{
    return health_points;
}

void Player::taking_damage(float dmg)
{
    health_points = health_points - dmg;

    // Check if player is still alive
    if(health_points <= 0)
    {
        set_is_alive(false);
    }
}

void Player::tick(float delta_time)
{

    // Check if player is still alive. If alive, call tick else stop calling tick

    if (!get_is_alive())
    {
        return;
    }

    // Movement Controls: Up, Down, Left, Right (WASD).
    if (IsKeyDown(KEY_A))
    {
        velocity.x -= 1.0;
    }
    else if (IsKeyDown(KEY_D))
    {
        velocity.x += 1.0;
    }
    else if (IsKeyDown(KEY_W))
    {
        velocity.y -= 1.0;
    }
    else if (IsKeyDown(KEY_S))
    {
        velocity.y += 1.0;
    }

    // Use base tick functionality of parent class
    Character::tick(delta_time);

    // origin
    Vector2 origin{};

    // offset
    Vector2 offset{};

    // rotation value
    float rotation{};

    // Check right_left
    if (right_left > 0.0f)
    {
        origin = {0.0f, sword.height * scale};
        offset = {87.0f, 105.0f};

        // Define collision rectangle when facing the right
        sword_collision_rec = {
            get_screen_pos().x + offset.x,
            get_screen_pos().x + offset.y - sword.height * scale,
            sword.width * scale,
            sword.height * scale};

        // Sword movement/rotation dependent on mouse clicks
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            rotation = 35.0f;
        }
        else
        {
            rotation = 0.0f;
        }
    }
    else
    {
        origin = {sword.width * scale, sword.height * scale};
        offset = {37.0f, 105.0f};

        // Define collision rectangle when facing the left
        sword_collision_rec = {
            get_screen_pos().x + offset.x - sword.width * scale,
            get_screen_pos().x + offset.y - sword.height * scale,
            sword.width * scale,
            sword.height * scale};

        // Sword movement/rotation dependent on mouse clicks
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            rotation = -35.0f;
        }
        else
        {
            rotation = 0.0f;
        }
    }

    // Draw sword
    Rectangle src;
    src.x = 0.0f;
    src.y = 0.0f;
    src.width = static_cast<float>(sword.width) * right_left;
    src.height = static_cast<float>(sword.height);

    Rectangle dest;
    dest.x = get_screen_pos().x + offset.x;
    dest.y = get_screen_pos().y + offset.y;
    dest.width = sword.width * scale;
    dest.height = sword.height * scale;

    DrawTexturePro(sword, src, dest, origin, rotation, WHITE);

    // Vizualize the collision rectangles below

    // Draw collision rectangle for player
    DrawRectangleLines(get_collision_rectangle().x, get_collision_rectangle().y, get_collision_rectangle().width, get_collision_rectangle().height, RED);

    // Need collision for sword to do dmg
    DrawRectangleLines(
        sword_collision_rec.x, sword_collision_rec.y, sword_collision_rec.width, sword_collision_rec.height, RED);
}