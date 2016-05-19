#include "Timer.h"



Timer::Timer(HWND* hwnd, int id, int elapse)
{
	this->hwnd = hwnd;
	this->id = id;
	this->elapse = elapse;
	SetTimer(*hwnd, id, elapse, NULL);
	shift = 0;
	lastTime = GetTickCount();
}
void Timer::nextFrame()
{
	long time = GetTickCount();
	shift += elapse * 0.00001*(time-lastTime);
	lastTime = time;
}

Timer::~Timer()
{
	KillTimer(*hwnd, id);
}
