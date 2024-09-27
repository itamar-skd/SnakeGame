#pragma once

#include "Snake.h"
#include <vector>

class Graph
{
private:
	uint32_t __graphLength;

	Snake __snake;
	Point* __apple;

public:
	Graph(uint32_t graphLength);
	~Graph() = default;

private:
	void generateApple();
	void snakeAppleOverlay(uint8_t x, uint8_t y);

public:
	void printGraph();

	uint8_t snakeSize();
	MoveStatus snakeMoveUp();
	MoveStatus snakeMoveRight();
	MoveStatus snakeMoveDown();
	MoveStatus snakeMoveLeft();
};

