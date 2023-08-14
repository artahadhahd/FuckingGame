#pragma once
#include "Player.hh"
#include <optional>

namespace FuckingGame
{
    enum Direction
    {
        Up,
        Left,
        Right,
        Down,
        UpRight,
        UpLeft,
        DownRight,
        DownLeft,
    };
    // Pretty similar to a player but cannot be inherited.
    class Robot
    {
    public:
        Robot(f32 const speed, std::vector<i32> const maze)
        {
            this->speed = speed;
            this->maze = maze;
        }
        void set_position_to_maze_block(Vector2);
        void render(f32 const size, Color, bool const force);
        Vector2 get_position();
        // check for the block in direction (ahead, left, right, behind) for how many blocks.
        FuckingGame::Blocks look(FuckingGame::Direction, u16 const times);
        void go(FuckingGame::Direction, u16 const times);
        void set_target_to_mazeblock(Vector2);
        void set_start(Vector2);
        FuckingGame::Blocks HitScanner();
        void find();

    private:
        bool volatile moving;
        std::vector<i32> maze = {};
        Vector2 position = {}; // Lesson learnt, ALWAYS initialize your vectors
        Vector2 start = {};
        Vector2 target = {};
        f32 speed;
    };
}