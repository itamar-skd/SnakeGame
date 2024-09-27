#include "Graph.h"
#include <iostream>
#include <cstdlib>

Graph::Graph(uint32_t graphLength)
	: __graphLength(graphLength)
	, __snake(graphLength / 2, graphLength / 2)
	, __apple(new Point())
{
	generateApple();
};

void Graph::generateApple()
{
	Point* apple = this->__apple;

	srand(time(0));

	do {
		apple->setX(rand() % this->__graphLength);
		apple->setY(rand() % this->__graphLength);
	} while (this->__snake.hasTailAt(apple->x(), apple->y()));
}

void Graph::snakeAppleOverlay(uint8_t x, uint8_t y)
{
	SnakeTail* head = this->__snake.head();
	Point* apple = this->__apple;

	if (head->x() == apple->x() && head->y() == apple->y())
	{
		if (this->__snake.size() < 8)
		{
			this->__snake.addTail(x, y);
		}

		generateApple();
	}
}

void Graph::printGraph()
{
	system("cls");

	for (size_t i{ 0 }; i < __graphLength; i++)
	{
		std::cout << "--";
	}
	std::cout << std::endl;

	for (size_t i{ 0 }; i < __graphLength; i++)
	{
		std::cout << "| ";
		for (size_t j{ 0 }; j < __graphLength; j++)
		{
			if (this->__apple->x() == j && this->__apple->y() == i)
			{
				std::cout << "* ";
				continue;
			}

			if (this->__snake.hasTailAt(j, i))
				std::cout << (char)254u << std::string(" ");
			else
				std::cout << "  ";
		}

		std::cout << "|" << std::endl;
	}
	
	for (size_t i{ 0 }; i < __graphLength; i++)
	{
		std::cout << "--";
	}
}

uint8_t Graph::snakeSize()
{
	return this->__snake.size();
}

MoveStatus Graph::snakeMoveUp()
{
	MoveStatus res = this->__snake.moveUp(this->__graphLength);

	SnakeTail* tail = this->__snake.tail();
	this->snakeAppleOverlay(tail->x(), tail->y() - 1);

	return res;
}

MoveStatus Graph::snakeMoveRight()
{
	MoveStatus res = this->__snake.moveRight(this->__graphLength);

	SnakeTail* tail = this->__snake.tail();
	this->snakeAppleOverlay(tail->x() - 1, tail->y());

	return res;
}

MoveStatus Graph::snakeMoveDown()
{
	MoveStatus res = this->__snake.moveDown(this->__graphLength);

	SnakeTail* tail = this->__snake.tail();
	this->snakeAppleOverlay(tail->x(), tail->y() + 1);

	return res;
}

MoveStatus Graph::snakeMoveLeft()
{
	MoveStatus res = this->__snake.moveLeft(this->__graphLength);

	SnakeTail* tail = this->__snake.tail();
	this->snakeAppleOverlay(tail->x() + 1, tail->y());

	return res;
}

