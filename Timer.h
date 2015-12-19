#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void start(int start_time);
	unsigned int getElapsedTime();

private:
	int _startTime;

};