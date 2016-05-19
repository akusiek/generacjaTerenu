#pragma once
#include <Windows.h>
class Timer
{
	float shift;
	long lastTime;
	HWND * hwnd;
	int id;
	int elapse;
public:
	Timer(HWND* hwnd, int id, int elapse);
	void nextFrame();
	~Timer();
};

