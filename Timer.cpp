#include "Timer.h"

Timer::Timer()
{
	_startTime = 0;
}

Timer::~Timer()
{

}

void Timer::start()
{
	_startTime = SDL_GetTicks();
}

void Timer::start(int add_time)
{
	_startTime = SDL_GetTicks() + add_time;
}

unsigned int Timer::getElapsedTime()
{
	return SDL_GetTicks() - _startTime;
}
