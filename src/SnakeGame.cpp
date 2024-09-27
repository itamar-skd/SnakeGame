#include "SnakeGame.h"
#include <conio.h>

using namespace std::chrono_literals;

SnakeGame::SnakeGame(uint32_t graphLength)
	: __graph(graphLength)
	, __direction(DIRECTION_UP)
	, __keepAlive(true)
	, __inputThrd(&SnakeGame::getInput, this)
	, __advanceThrd(&SnakeGame::advance, this)
	, __lastInput(system_clock::now())
	, __speed(1.0)
{
};

SnakeGame::~SnakeGame()
{
	this->__keepAlive = false;
	this->__inputThrd.join();
	this->__advanceThrd.join();
}

void SnakeGame::getInput()
{
	int input{ -1 };

	while (this->__keepAlive)
	{
		input = _getch();
		if (input != KEY_UP && input != KEY_RIGHT && input != KEY_DOWN && input != KEY_LEFT)
			continue;

		this->__lastInput = system_clock::now();

		MoveStatus res{ MOVE_SUCCESS };
		uint8_t snakeSize{ this->__graph.snakeSize() };

		switch (input)
		{
			case KEY_UP:
				res = this->__graph.snakeMoveUp();
				if (res != MOVE_PRESSED_OPPOSITE) this->__direction = DIRECTION_UP;
				break;
			case KEY_RIGHT:
				res = this->__graph.snakeMoveRight();
				if (res != MOVE_PRESSED_OPPOSITE) this->__direction = DIRECTION_RIGHT;
				break;
			case KEY_DOWN:
				res = this->__graph.snakeMoveDown();
				if (res != MOVE_PRESSED_OPPOSITE) this->__direction = DIRECTION_DOWN;
				break;
			case KEY_LEFT:
				res = this->__graph.snakeMoveLeft();
				if (res != MOVE_PRESSED_OPPOSITE) this->__direction = DIRECTION_LEFT;
				break;
		}

		this->__graph.printGraph();

		if (this->__graph.snakeSize() != snakeSize)
			this->__speed -= 1 / 16;

		if (res == MOVE_SNAKE_CRASHED)
			this->~SnakeGame();
	}
}

void SnakeGame::advance()
{
	while (this->__keepAlive)
	{
		if (duration_cast<milliseconds>(system_clock::now() - this->__lastInput).count() > 1e3)
		{
			MoveStatus res{ MOVE_SUCCESS };
			uint8_t snakeSize{ this->__graph.snakeSize() };

			switch (this->__direction)
			{
				case DIRECTION_UP:
					res = this->__graph.snakeMoveUp();
					break;

				case DIRECTION_RIGHT:
					res = this->__graph.snakeMoveRight();
					break;

				case DIRECTION_DOWN:
					res = this->__graph.snakeMoveDown();
					break;

				case DIRECTION_LEFT:
					res = this->__graph.snakeMoveLeft();
					break;
			}

			this->__graph.printGraph();

			if (this->__graph.snakeSize() != snakeSize)
				this->__speed -= 1.0 / 10;

			if (res == MOVE_SNAKE_CRASHED)
				this->~SnakeGame();

			auto a = 1s * this->__speed;
			std::this_thread::sleep_for(1s * this->__speed);
		}
	}
}