#include "Maze.hh"
#include "Player.hh"
#include "Raylib/raylib.h"
#include "Robot.hh"
#include "Types.hpp"
#include "config.h"

#include <iostream>

static inline void render_map(i32 const MapWidth,
                              std::vector<i32> const map) noexcept;

i32 main()
{
  // Definitions
  Vector2 player1pos = {60.0, 60.0};
  FuckingGame::KeySet WASD = {
      KEY_W, KEY_S, KEY_A,
      KEY_D}; // This works on any keyboard, not only QWERTY
  u8 color;
  bool cup = true;
  bool processed = false;
  FuckingGame::Maze maze(MapWidth, MapHeight);
  FuckingGame::Player player1(player1pos, WASD, Player1Speed,
                              maze.as_int_vector);
  FuckingGame::Robot robot(Player2Speed, maze.as_int_vector);
  robot.set_start(maze.entrance);
  robot.set_target_to_mazeblock(maze.exit);
  auto lookb = robot.look(FuckingGame::Down, 1);
  auto lookr = robot.look(FuckingGame::Right, 1);
  auto lookl = robot.look(FuckingGame::Left, 1);
  auto looka = robot.look(FuckingGame::Up, 1);

  if (lookb == FuckingGame::GRAY_SQUARE && lookr == FuckingGame::GRAY_SQUARE &&
      lookl == FuckingGame::GRAY_SQUARE && looka == FuckingGame::GRAY_SQUARE)
  {
    std::cout << "This maze is unsolvable lol\n";
    return 0;
  }

  // End of definitions

  InitWindow(ScreenWidth, ScreenHeight, "Deutsche Bahn Simulator");
  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    player1.update_position();
    BeginDrawing();
    if (!processed)
    {
      ClearBackground(BLUE);
      render_map(MapWidth, maze.as_int_vector);
      player1.set_position_to_maze_block(maze.exit);
      robot.set_position_to_maze_block(maze.entrance);
      // robot.set_position_to_maze_block((Vector2){20.0, 1.0});
      player1.render(RectSize / 3, BLACK, true);
      processed = true;
    }
    if (++color == 255)
    {
      cup = !cup;
    }
    if (!cup)
    {
      color--;
    }
    if (IsKeyPressed(KEY_R))
    {
      processed = false;
    }
    if (IsKeyPressed(KEY_L))
    {
      EndDrawing();
      CloseWindow();
      main();
    }
    player1.render(RectSize / 3,
                   (Color){u8(color - 10), u8(color + 20), color, 200}, false);
    robot.render(RectSize / 3, BLACK, false);
    // if (robot.look(FuckingGame::Down, 1) == FuckingGame::WHITE_SQUARE)
    // {
    //     robot.go(FuckingGame::Down, 1);
    // }
    robot.find();
    switch (player1.HitScanner())
    {
    [[likely]] case FuckingGame::GRAY_SQUARE:
      player1.set_position_to_maze_block(maze.exit);
      break;
    [[unlikely]] case FuckingGame::RED_SQUARE:
      std::cout << "Player 1 won\n";
      goto END;
      break;
    default:
      break;
    }
    if (robot.HitScanner() ==
        FuckingGame::GREEN_SQUARE) // pretty fucking impossible but it's there
    {
      std::cout << "The robot won, we're fucking doomed lol\n";
      processed = false;
    }
    if (robot.HitScanner() == FuckingGame::GRAY_SQUARE)
    {
      robot.set_position_to_maze_block(maze.entrance);
      std::cout << "Crashed\n";
    }
    EndDrawing();
  }
END:
  CloseWindow();
  return 0;
}

static inline void render_map(i32 const MapWidth,
                              std::vector<i32> const map) noexcept
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
