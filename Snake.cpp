#include "Snake.h"

Point::Point()
	: _x(0), _y(0)
{};

Point::Point(uint32_t x, uint32_t y)
	: _x(x), _y(y)
{};

SnakeTail::SnakeTail()
	: Point(0, 0), __next(nullptr), __prev(nullptr)
{};

SnakeTail::SnakeTail(uint32_t x, uint32_t y)
	: Point(x, y), __next(nullptr), __prev(nullptr)
{};

SnakeTail::~SnakeTail()
{
	delete __next;
	this->__next = nullptr;

	delete __prev;
	this->__prev = nullptr;
}

SnakeTail* SnakeTail::next()
{
	return this->__next;
}

SnakeTail* SnakeTail::prev()
{
	return this->__prev;
}

void SnakeTail::setNext(SnakeTail* next)
{
	this->__next = next;
}

void SnakeTail::setPrev(SnakeTail* prev)
{
	this->__prev = prev;
}

uint32_t Point::x()
{

	return this->_x;
}

uint32_t Point::y()
{
	return this->_y;
}

void Point::setX(uint32_t x)
{
	this->_x = x;
}

void Point::setY(uint32_t y)
{
	this->_y = y;
}

Snake::Snake(uint32_t x, uint32_t y)
	: __size(1)
{
	SnakeTail* tail = new SnakeTail(x, y);
	this->__head = tail;
	this->__tail = tail;
};

SnakeTail* Snake::head()
{
	return this->__head;
}

SnakeTail* Snake::tail()
{
	return this->__tail;
}

uint8_t Snake::size()
{
	return this->__size;
}

void Snake::addTail(uint32_t x, uint32_t y)
{
	SnakeTail* tail = new SnakeTail(x, y);

	this->__tail->setNext(tail);
	tail->setPrev(this->__tail);
	this->__tail = tail;

	this->__size++;
}

bool Snake::hasTailAt(uint32_t x, uint32_t y)
{
	SnakeTail* temp = this->__head;
	while (temp != nullptr)
	{
		if (temp->x() == x && temp->y() == y)
			return true;

		temp = temp->next();
	}

	return false;
}

void Snake::move()
{
	SnakeTail* temp = this->__tail;

	while (temp != this->__head)
	{
		temp->setX(temp->prev()->x());
		temp->setY(temp->prev()->y());

		temp = temp->prev();
	}
}

MoveStatus Snake::moveUp(uint32_t graphLength)
{
	if (this->__head->next() != nullptr)
	{
		// If pressed opposite direction of the direction currently going
		if (this->__head->y() - 1 == this->__head->next()->y())
			return MOVE_PRESSED_OPPOSITE;

		// Snake crashes into its own tail
		if (this->hasTailAt(this->__head->y(), this->__head->y() - 1))
			return MOVE_SNAKE_CRASHED;

		this->move();
	}

	if (this->__head->y() == 0)
		this->__head->setY(graphLength - 1);
	else
		this->__head->setY(this->__head->y() - 1);

	return MOVE_SUCCESS;
}

MoveStatus Snake::moveRight(uint32_t graphLength)
{
	if (this->__head->next() != nullptr)
	{
		// If pressed opposite direction of the direction currently going
		if (this->__head->x() + 1 == this->__head->next()->x())
			return MOVE_PRESSED_OPPOSITE;

		// Snake crashes into its own tail
		if (this->hasTailAt(this->__head->x() + 1, this->__head->y()))
			return MOVE_SNAKE_CRASHED;

		this->move();
	}

	if (this->__head->x() == graphLength - 1)
		this->__head->setX(0);
	else
		this->__head->setX(this->__head->x() + 1);

	return MOVE_SUCCESS;
}

MoveStatus Snake::moveDown(uint32_t graphLength)
{
	if (this->__head->next() != nullptr)
	{
		// If pressed opposite direction of the direction currently going
		if (this->__head->y() + 1 == this->__head->next()->y())
			return MOVE_PRESSED_OPPOSITE;

		// Snake crashes into its own tail
		if (this->hasTailAt(this->__head->x(), this->__head->y() + 1))
			return MOVE_SNAKE_CRASHED;

		this->move();
	}

	if (this->__head->y() == graphLength - 1)
		this->__head->setY(0);
	else
		this->__head->setY(this->__head->y() + 1);

	return MOVE_SUCCESS;
}

MoveStatus Snake::moveLeft(uint32_t graphLength)
{
	if (this->__head->next() != nullptr)
	{
		// If pressed opposite direction of the direction currently going
		if (this->__head->x() - 1 == this->__head->next()->x())
			return MOVE_PRESSED_OPPOSITE;

		// Snake crashes into its own tail
		if (this->hasTailAt(this->__head->x() - 1, this->__head->y()))
			return MOVE_SNAKE_CRASHED;

		this->move();
	}

	if (this->__head->x() == 0)
		this->__head->setX(graphLength - 1);
	else
		this->__head->setX(this->__head->x() - 1);

	return MOVE_SUCCESS;
}