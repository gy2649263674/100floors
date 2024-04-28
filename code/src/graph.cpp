#define CRT_SECURE_NO_WARNINGS 1
#include"all.h"
#include<conio.h>
#include<windows.h>
#include <direct.h>
using namespace std;

Atlas::Atlas(const char* role_name, int n)
{
	for (int i = 0; i<n; i++)
	{
		
		IMAGE* temp = new IMAGE;
		char s[256];
		//"E:\zzs\100floors\100_floors_down\100_floors_down\source\girl\run (1).png"
		std::string path = "source\\" + string(role_name) + "\\run (" + to_string(i) + ").png";
		loadimage(temp, &path[0],520, 520);
		
		(this->arr).push_back(temp);
	}
	
}
void test(Atlas&a)
{
	initgraph(1000, 1024);
	setfillcolor(WHITE);
	clock_t be = 1000 / 15;
	clock_t acc = 0;
	for (int i = 0;; i++)
	{
		BeginBatchDraw();
		cleardevice();
		putimage(100, 100,a.arr[i]);
		EndBatchDraw();
		if (acc < be)
		{
			Sleep(be - acc);
		}
		i %= (a.arr.size() - 1);
	}

}
const IMAGE* Atlas::get_image(int index)const
{
	return arr[index];
}
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
