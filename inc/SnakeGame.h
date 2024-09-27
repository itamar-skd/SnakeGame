#pragma once

#include "Graph.h"
#include <thread>
#include <chrono>

using namespace std::chrono;

class SnakeGame
{
private:
	Graph __graph;
	Direction __direction;

	bool __keepAlive;
	std::thread __inputThrd;
	std::thread __advanceThrd;

	time_point<system_clock> __lastInput;
	double __speed;

private:
	void getInput();
	void advance();

public:
	SnakeGame(uint32_t graphLength);
	~SnakeGame();
};

