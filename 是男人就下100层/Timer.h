
#pragma once
#include <ctime>
#include<iostream>
#include<windows.h>
#include"unit.h"
class Timer
{
public:
	static bool timer(clock_t ms, int num);
	static void beginkeep()
	{
		time = clock();
	}
	static void endkeep(int fps)
	{
		int endtime = clock();
		//Sleep(FRAME - (endtime - time));
		Sleep(FRAME);
	}
	static int time;
};


