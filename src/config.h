#pragma once

#define SPAWNCHANCE 10 // percentage!

const float RectSize = 10.0f; // should be bigger than 10.0, otherwise you wouldn't see the player(s)
const int MapHeight = 50;
const int MapWidth = 30;

// This is actually the window's width and height, but i am too lazy to press 3 buttons to fix the name.
const int ScreenWidth = MapWidth * RectSize;
const int ScreenHeight = MapHeight * RectSize;

const float Player1Speed = 3.0f;
const float Player2Speed = 3.0f; // for the robot