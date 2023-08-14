#include "Maze.hh"
#include "config.h"

#include <random>
#include <stdexcept>

/* Returns a random number in range 0 to 10 */
static inline i32 get_rand(i32 start, i32 end)
{
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<i32> dist(start, end);
    return dist(mt);
}

/* Creates a maze border with an exit and an entrance. */
std::vector<FuckingGame::MazeBlocks> FuckingGame::Maze::create()
{
    if (this->width <= 3)
    {
        throw std::range_error("The maze's width has to be greater than 3, otherwise it will be stuck in an infinite loop.");
    }
    bool has_exit = false;
    bool has_entrance = false;
    std::vector<FuckingGame::MazeBlocks> vec;
    auto entrance = get_rand(1, MapWidth - 1);
    auto exit = get_rand(1, MapWidth - 1);
    for (i32 y = 0; y < this->height; y++)
    {
        for (i32 x = 0; x < this->width; x++)
        {
            Vector2 coord = {f32(x), f32(y)};
            if (0 == y || y == this->height - 1 || 0 == x || x == this->width - 1) // create a border.
            {
                // create entrance
                if (x == entrance && !has_entrance && x != 0 && x != this->width - 1 && y != this->height - 1)
                {
                    this->as_int_vector.push_back(FuckingGame::RED_SQUARE);
                    vec.push_back(MazeBlocks({false, FuckingGame::RED_SQUARE, coord}));
                    this->entrance = coord;
                    has_entrance = true;
                    continue;
                }
                // create exit
                if (exit == x && !has_exit && y == this->height - 1 && x != 0 && x != this->width - 1)
                {
                    this->as_int_vector.push_back(FuckingGame::GREEN_SQUARE);
                    vec.push_back(MazeBlocks({false, FuckingGame::GREEN_SQUARE, coord}));
                    this->exit = coord;
                    has_exit = true;
                    continue;
                }

                // Gray cells are by default marked as visited and on collision you will lose.

                vec.push_back(MazeBlocks({true, FuckingGame::GRAY_SQUARE, coord}));
                this->as_int_vector.push_back(FuckingGame::GRAY_SQUARE);
            }
            else
            {
                if (get_rand(0, i32(100 / SPAWNCHANCE - 1)) == 0 && y != 2 && y != this->height - 2)
                {
                    vec.push_back(MazeBlocks({false, FuckingGame::GRAY_SQUARE, coord}));
                    this->as_int_vector.push_back(FuckingGame::GRAY_SQUARE);
                }
                else
                {
                    vec.push_back(MazeBlocks({false, FuckingGame::WHITE_SQUARE, coord}));
                    this->as_int_vector.push_back(FuckingGame::WHITE_SQUARE);
                }
            }
        }
    }
    // Try to create a maze if something fails
    if (!has_exit || !has_entrance)
    {
        vec.clear();
        this->as_int_vector.clear();
        this->create();
    }
    return vec;
}