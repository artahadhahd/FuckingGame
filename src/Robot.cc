// 27July

#include "Robot.hh"
#include <iostream>

void FuckingGame::Robot::set_position_to_maze_block(Vector2 pos)
{
    this->position = Vector2({(pos.x + 0.5f) * RectSize, (pos.y + 0.5f) * RectSize});
}

void FuckingGame::Robot::render(f32 const size, Color color, bool const force)
{
    if (this->moving || force)
    {
        DrawCircleV(this->position, size, color);
    }
}

Vector2 FuckingGame::Robot::get_position()
{
    return Vector2({this->position.x / RectSize, this->position.y / RectSize});
}

FuckingGame::Blocks FuckingGame::Robot::look(FuckingGame::Direction direction, u16 const times)
{
    using FuckingGame::Direction;
    auto h = this->get_position();
    i32 x = h.x;
    i32 y = h.y;
    if (times == 0)
    {
        return (Blocks)this->maze[y * MapWidth + x];
    }
    if (y == MapWidth - 1)
    {
        return FuckingGame::GRAY_SQUARE;
    }
    switch (direction)
    {
    case Down:
        return (Blocks)this->maze[(y + i32(times)) * (MapWidth) + x];
    case Up:
        if (y == 0)
        {
            return GRAY_SQUARE;
        }
        return (Blocks)this->maze[(y - times) * MapWidth + x];
    case Left:
        return (Blocks)this->maze[y * MapWidth + x - times];
    case Right:
        return (Blocks)this->maze[y * MapWidth + x + times];
    default:
        break;
    }
}

void FuckingGame::Robot::go(FuckingGame::Direction direction, u16 times)
{
    if (times == 0)
    {
        return;
    }
    using FuckingGame::Direction;
    if (direction == Up)
    {
        for (u8 i = 0; i < times; i++)
        {
            this->position.y -= this->speed;
            if (0 >= position.y)
            {
                position.y = ScreenHeight;
            }
        }
        this->moving = true;
    }
    if (direction == Down)
    {
        this->position.y += this->speed;
        if (ScreenHeight <= position.y)
        {
            position.y = 0;
        }
        this->moving = true;
    }
    if (direction == Left)
    {
        this->position.x -= this->speed;
        if (0 >= position.x)
        {
            position.x = ScreenWidth;
        }
        this->moving = true;
    }
    if (direction == Right)
    {
        this->position.x += this->speed;
        if (ScreenWidth <= position.x)
        {
            position.x = 0;
        }
        this->moving = true;
    }
}

FuckingGame::Blocks FuckingGame::Robot::HitScanner()
{
    auto h = this->get_position();
    return (FuckingGame::Blocks)this->maze[i32(h.y) * MapWidth + i32(h.x)];
}

void FuckingGame::Robot::set_target_to_mazeblock(Vector2 target)
{
    this->target = target;
}

void FuckingGame::Robot::set_start(Vector2 m)
{
    this->start = m;
}

void FuckingGame::Robot::find()
{
    using FuckingGame::Blocks;
    using FuckingGame::Direction;
    auto p = this->get_position();
    bool goright = false;
    if (p.x < target.x)
    {
        goright = true;
    }
    auto dir = goright ? Right : Left;
    auto ndir = goright ? Left : Right;
    if (this->look(Down, 1) == GREEN_SQUARE)
    {
        this->go(Down, 1);
    }
    if (this->look(Left, 1) == GRAY_SQUARE && this->look(Right, 1) == GRAY_SQUARE)
    {
        this->go(Down, 1);
    }
    if (this->look(Down, 1) == WHITE_SQUARE)
        this->go(Down, 1);
    if (p.x != target.x) // || this->look(Down, 1) == GRAY_SQUARE)
    {
        if (this->look(dir, 1) == WHITE_SQUARE)
            this->go(dir, 1);
        else
            this->go(ndir, 1);
    };
    if (this->look(Down, 1) == GRAY_SQUARE)
    {
        this->go(Up, 2);

        if (this->look(dir, 1) == WHITE_SQUARE)
            this->go(dir, 1);
        else
            this->go(ndir, 1);
    }

    // if (this->look(dir, 1) == WHITE_SQUARE)
    // {
    //     this->go(dir, 1);
    // }
    // else
    // {
    //     this->go(ndir, 1);
    // }
    // if (this->look(Left, 1) == GRAY_SQUARE && this->look(Right, 1) == GRAY_SQUARE)
    // {
    //     this->go(Down, 1);
    // }
    // if (this->look(Down, 1) == WHITE_SQUARE || this->look(Down, 1) == GREEN_SQUARE)
    // {
    //     this->go(Down, 1);
    // }
    // if (/*p.x < target.x &&*/ this->look(Down, 1) == WHITE_SQUARE)
    // {
    //     this->look(Right, 1) == WHITE_SQUARE ? this->go(Right, 1) : this->go(Left, 1);
    // }
    // else if (p.x > target.x && this->look(Down, 1) == WHITE_SQUARE)
    // {
    //     this->look(Left, 1) == WHITE_SQUARE ? this->go(Left, 1) : this->go(Right, 1);
    // }

    // if (this->look(Left, 1) == GRAY_SQUARE && this->look(Right, 1) == WHITE_SQUARE)
    // {
    //     this->go(Right, 1);
    // }
    // if (this->look(Down, 1) == GRAY_SQUARE)
    // {
    //     if (this->look(Right, 1) == WHITE_SQUARE)
    //         this->go(Right, 1);
    //     else
    //         this->go(Left, 1);
    // }

    // else if (this->look(Left, 1) == WHITE_SQUARE)
    // {
    //     if (!right)
    //         this->go(Left, 1);
    //     else
    //         this->go(Right, 1);
    // }
    // else if (this->look(Right, 1) == WHITE_SQUARE && right)
    // {
    //     this->go(Right, 1);
    // }
    // else
    // {
    //     this->go(Up, 1);
    // }
}