#define CRT_SECURE_NO_WARNINGS 1
#include"all.h"
//using namespace std;

Atlas::Atlas(const char* characterName, int n)
{
	for (int i = 0; i < n; i++)
	{
		IMAGE* temp = new IMAGE;
		char imageName[255] = { 0 };
		//sprintf(imageName, "%s%d.png", imageName, i);
		loadimage(temp, imageName, 128, 256);
		(this->arr).push_back(temp);
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
