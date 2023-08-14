#include "Player.hh"
#include "config.h"

// Variables in PascalCase are imported from src/config.h, a file necessary for the game to work.

void FuckingGame::Player::update_position()
{
    if (!IsKeyDown(this->keys.RIGHT) && !IsKeyDown(this->keys.LEFT) && !IsKeyDown(this->keys.UP) && !IsKeyDown(this->keys.DOWN))
    {
        this->moving = false;
    }
    if (IsKeyDown(this->keys.RIGHT))
    {
        this->position.x += this->speed;
        if (ScreenWidth <= this->position.x)
        {
            this->position.x = 0;
        }
        this->moving = true;
    }
    if (IsKeyDown(this->keys.LEFT))
    {
        this->position.x -= this->speed;
        if (0 >= this->position.x)
        {
            this->position.x = ScreenWidth;
        }
        this->moving = true;
    }
    if (IsKeyDown(this->keys.DOWN))
    {
        this->position.y += this->speed;
        if (ScreenHeight <= this->position.y)
        {
            this->position.y = 0;
        }
        this->moving = true;
    }
    if (IsKeyDown(this->keys.UP))
    {
        this->position.y -= this->speed;
        if (0 >= this->position.y)
        {
            this->position.y = ScreenHeight;
        }
        this->moving = true;
    }
}

inline void FuckingGame::Player::set_speed(f32 const speed)
{
    this->speed = speed;
}

void FuckingGame::Player::render(f32 const size, Color color, bool const force)
{
    if (this->moving || force)
    {
        DrawCircleV(this->position, size, color);
    }
}

/* This is special because the values inside the vector
 * are multiplied by RectSize - so that the
 * maze coordinations correspond to that of the maze.*/

void FuckingGame::Player::set_position_to_maze_block(Vector2 pos)
{
    this->position = Vector2({(pos.x + 0.5f) * RectSize, (pos.y + 0.5f) * RectSize});
}

Vector2 FuckingGame::Player::get_position()
{
    return Vector2({this->position.x / RectSize, this->position.y / RectSize});
}

[[deprecated]] bool FuckingGame::Player::has_collided() noexcept
{
    auto h = this->get_position();
    return this->maze[i32(h.y) * MapWidth + i32(h.x)] == FuckingGame::GRAY_SQUARE;
}

FuckingGame::Blocks FuckingGame::Player::HitScanner()
{
    auto h = this->get_position();
    return (FuckingGame::Blocks)this->maze[i32(h.y) * MapWidth + i32(h.x)];
}