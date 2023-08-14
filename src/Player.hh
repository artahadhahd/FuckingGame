#pragma once
#include "Raylib/raylib.h"
#include "Types.hpp"
#include "Maze.hh"

#include "config.h"

namespace FuckingGame
{
    /*UP DOWN LEFT RIGHT ( W S A D for WASD)*/
    struct KeySet
    {
        i32 UP;
        i32 DOWN;
        i32 LEFT;
        i32 RIGHT;
    };

    class Player
    {
    public:
        Player(Vector2 position, KeySet const keys, f32 speed, std::vector<i32> const maze)
        {
            this->position = position;
            this->keys = keys;
            this->speed = speed;
            this->maze = maze;
        }
        void update_position();
        void render(f32 const size, Color, bool const force);
        void set_position_to_maze_block(Vector2 xAndY);
        [[deprecated]] bool has_collided() noexcept;
        std::vector<i32> maze;
        Vector2 get_position();
        FuckingGame::Blocks HitScanner();

    private:
        inline void set_speed(f32 const newspeed);
        bool volatile moving;
        KeySet keys;
        f32 speed;
        Vector2 position;
    };
}