#pragma once

#include "defines.h"
#include <iostream>
#include <stdint.h>
#include <math.h>

class Point
{
	friend class Snake;

protected:
	uint32_t _x;
	uint32_t _y;

public:
	Point();
	Point(uint32_t y, uint32_t x);
	~Point() = default;

public:
	inline uint32_t x();
	inline uint32_t y();

	inline void setX(uint32_t x);
	inline void setY(uint32_t y);
};

class SnakeTail final : public Point
{
private:
	SnakeTail* __next;
	SnakeTail* __prev;

public:
	SnakeTail();
	SnakeTail(uint32_t y, uint32_t x);
	~SnakeTail();

public:
	inline SnakeTail* next();
	inline SnakeTail* prev();

	inline void setNext(SnakeTail* next);
	inline void setPrev(SnakeTail* prev);
};

class Snake
{
private:
	SnakeTail* __head;
	SnakeTail* __tail;
	uint8_t __size;

public:
	Snake(uint32_t y, uint32_t x);
	~Snake() = default;

private:
	void move();

public:
	SnakeTail* head();
	SnakeTail* tail();
	uint8_t size();

	bool hasTailAt(uint32_t x, uint32_t y);
	void addTail(uint32_t x, uint32_t y);

	/// <summary>
	/// Move the snake up
	/// </summary>
	/// <param name="graphLength">Length of the graph</param>
	/// <returns>Move status: 0 - Success, 1 - Pressed opposite, 2 - Crashed</returns>
	MoveStatus moveUp(uint32_t graphLength);

	/// <summary>
	/// Move the snake right
	/// </summary>
	/// <param name="graphLength">Length of the graph</param>
	/// <returns>Move status: 0 - Success, 1 - Pressed opposite, 2 - Crashed</returns>
	MoveStatus moveRight(uint32_t graphLength);

	/// <summary>
	/// Move the snake down
	/// </summary>
	/// <param name="graphLength">Length of the graph</param>
	/// <returns>Move status: 0 - Success, 1 - Pressed opposite, 2 - Crashed</returns>
	MoveStatus moveDown(uint32_t graphLength);

	/// <summary>
	/// Move the snake left
	/// </summary>
	/// <param name="graphLength">Length of the graph</param>
	/// <returns>Move status: 0 - Success, 1 - Pressed opposite, 2 - Crashed</returns>
	MoveStatus moveLeft(uint32_t graphLength);
};

