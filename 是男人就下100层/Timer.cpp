#include "Timer.h"
bool Timer::timer(clock_t ms,int num)
{
	static clock_t t[10] = { 0 };
	//clock表示程序运行到调用该函数所经过的毫秒数
	if (clock() - t[num] > ms)
	{
		t[num] = clock();
		return true;
	}
	return false;
}