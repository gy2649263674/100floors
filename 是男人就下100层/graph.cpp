#define CRT_SECURE_NO_WARNINGS 1
#include"all.h"
//using namespace std;

//Atlas::Atlas(const char* characterName, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		IMAGE* temp = new IMAGE;
//		char imageName[255] = { 0 };
//		loadimage(temp, imageName, 128, 256);
//		(this->arr).push_back(temp);
//	}
//}
//void Animation::showAnimation(const Role&role,ExMessage&msg)
//void Animation::showAnimation(const Role&role,ExMessage&msg)
//{
//	int index = 0;
//	while (peekmessage(&msg,EX_KEY))
//	{
//		//switch(msg.vkcode)
//			//case:
//		putimage(role.getx(), role.gety(), role.get_frame(index));
//		index = (++index) % role.get_image_num();
//	}
//	return;
//}
//void putimage(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGE* pSrcImg, int srcX, int srcY, DWORD dwRop = SRCCOPY);		// Put image to device

//void draw_lucency(int x,int y ,IMAGE* ori,IMAGE* mask, double ratio)
//{
//	BeginBatchDraw();
//	//putimage(x, y, mask, ori->getwidth() * ratio, ori->getheight() * ratio, SRCAND, ori->getwidth(), ori->getheight(),);
//	putimage(x, y, ori, SRCPAINT);
//	EndBatchDraw();
//}


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

