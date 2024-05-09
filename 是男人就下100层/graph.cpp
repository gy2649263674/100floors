#define CRT_SECURE_NO_WARNINGS 1
#include"all.h"


void draw_lucency(int x, int y, IMAGE* ori, IMAGE* mask)
{
	BeginBatchDraw();
	putimage(x, y, mask, SRCAND);
	putimage(x, y, ori, SRCPAINT);
	EndBatchDraw();
	return;
}
IMAGE* Atlas::get_image(int index, int cate)
{
	if (index >= 0)
	{
		if (cate == 0 && index < arr.size())
			return arr[index];
		else if (index < arr_mask.size())
		{
			return arr_mask[index];
		}
	}
	return NULL;
}

