// Initial write date: 22nd of July
// Written by Arta, under MIT license

// TODO: https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference

#include "Raylib/raylib.h"
#include "Types.hpp"
#include "config.h"
#include "Maze.hh"
#include "Player.hh"

#include <iostream>

// Variables in PascalCase are imported from src/config.h, a file necessary for the game to work.
// This will probably change in near future.

static inline void render_map(i32 const MapWidth, std::vector<i32> const map) noexcept;

i32 main()
{
    // Definitions
    Vector2 player1pos = {60.0, 60.0};
    Vector2 player2pos = {40.0, 20.0};
    FuckingGame::KeySet WASD = {KEY_W, KEY_S, KEY_A, KEY_D}; // This works on any keyboard, not only QWERTY
    FuckingGame::KeySet ARROW = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
    u8 color;
    bool cup = true;
    bool processed = false;
    u8 collisions = 0;
    FuckingGame::Maze maze(MapWidth, MapHeight);

    FuckingGame::Player player1(player1pos, ARROW, Player1Speed, maze.as_int_vector);
    FuckingGame::Player player2(player2pos, WASD, Player2Speed, maze.as_int_vector);
    // End of definitions

    InitWindow(ScreenWidth, ScreenHeight, "Deutsche Bahn Simulator");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        player1.update_position();
        player2.update_position();
        BeginDrawing();
        if (!processed) // rendered only once when requested, to save resources
        {
            ClearBackground(BLUE);
            render_map(MapWidth, maze.as_int_vector);
            player1.set_position_to_maze_block(maze.exit);
            player2.set_position_to_maze_block(maze.entrance);
            player1.render(RectSize / 3, PURPLE, true);
            player2.render(RectSize / 3, (Color){u8(color - 20), u8(color - 10), color, 250}, true);
            processed = true;
        }
        // Rendered and processed each frame
        if (++color == 255)
        {
            cup = !cup;
        }
        if (!cup)
        {
            color--;
        }
        if (IsKeyPressed(KEY_R) || collisions >= 30)
        {
            collisions = 0;
            processed = false;
        }
        // player1.render(RectSize / 3, (Color){120, 222, 255, u8(100 - color)}, false);
        player1.render(RectSize / 3, (Color){u8(color - 10), u8(color + 20), color, 200}, false);
        player2.render(RectSize / 3, (Color){u8(color - 20), u8(color - 10), color, 100}, false);
        auto p1p = player1.get_position();
        auto p2p = player2.get_position();
        if (i32(p1p.x) == i32(p2p.x) && i32(p2p.y) == i32(p1p.y))
        {
            std::cout << "The players collided and you lost\n";
            goto END;
        }
        switch (player1.HitScanner())
        {
        [[likely]] case FuckingGame::GRAY_SQUARE:
            collisions++;
            player1.set_position_to_maze_block(maze.exit);
            break;
        [[unlikely]] case FuckingGame::RED_SQUARE:
            std::cout << "Player 1 won\n";
            goto END;
        default:
            break;
        }
        switch (player2.HitScanner())
        {
        [[likely]] case FuckingGame::GRAY_SQUARE:
            collisions++;
            player2.set_position_to_maze_block(maze.entrance);
            break;
        [[unlikely]] case FuckingGame::GREEN_SQUARE:
            std::cout << "Player 2 won\n";
            goto END;
        default:
            break;
        }
        EndDrawing();
    }
END:

    CloseWindow();
}

static inline void render_map(i32 const MapWidth, std::vector<i32> const map) noexcept
{
    f32 row = 0.0f;
    u64 j = 0;
    for (u64 i = 0; i < map.size(); i++)
    {
        if (i % MapWidth == 0 && i != 0)
        {
            row += RectSize;
            j = 0;
        }
        Vector2 pos = {f32(j * RectSize), row};
        Vector2 sz = {RectSize, RectSize};
        switch (map[i])
        {
        [[likely]] case FuckingGame::WHITE_SQUARE:
            DrawRectangleV(pos, sz, WHITE);
            break;
        case FuckingGame::GRAY_SQUARE:
            DrawRectangleV(pos, sz, GRAY);
            break;
        [[unlikely]] case FuckingGame::RED_SQUARE: // Entrance
            DrawRectangleV(pos, sz, RED);
            break;
        [[unlikely]] case FuckingGame::GREEN_SQUARE: // Exit
            DrawRectangleV(pos, sz, GREEN);
            break;
        }
        j++;
    }
}