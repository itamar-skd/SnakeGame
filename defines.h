#pragma once

#include <stdint.h>

enum Direction : uint8_t { DIRECTION_UP = 1, DIRECTION_RIGHT = 2, DIRECTION_DOWN = 3, DIRECTION_LEFT = 4 };

enum MoveStatus : uint8_t { MOVE_SUCCESS = 0, MOVE_PRESSED_OPPOSITE = 1, MOVE_SNAKE_CRASHED = 2 };

#define KEY_UP		72
#define KEY_RIGHT	77
#define KEY_DOWN	80
#define KEY_LEFT	75