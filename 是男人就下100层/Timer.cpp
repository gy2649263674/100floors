#include "Timer.h"
bool Timer::timer(clock_t ms,int num)
{
	static clock_t t[10] = { 0 };
	//clock��ʾ�������е����øú����������ĺ�����
	if (clock() - t[num] > ms)
	{
		t[num] = clock();
		return true;
	}
	return false;
}

bool::Timer:: Delay(int time)
{
	clock_t now = clock();
	while (clock() - now < time);
	return true;
}