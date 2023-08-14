#pragma once
#include "Types.hpp"
#include <Raylib/raylib.h>

#include <vector>

namespace FuckingGame
{
    enum Blocks
    {
        WHITE_SQUARE,
        GRAY_SQUARE,
        RED_SQUARE,
        GREEN_SQUARE,
    };

    struct MazeBlocks
    {
        bool visited;
        Blocks value;
        Vector2 coords;
    };

    struct Maze
    {
    public:
        Maze(i32 const x, i32 const y)
        {
            this->width = x;
            this->height = y;
            this->blocks = this->create();
        }
        std::vector<i32> as_int_vector; // requried to render the map
        std::vector<struct MazeBlocks> blocks;
        Vector2 entrance;
        Vector2 exit;

    private:
        std::vector<struct MazeBlocks> create();
        i32 width;
        i32 height;
    };
}