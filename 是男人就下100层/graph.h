#pragma once
#include<iostream>
#include<fstream>
#include<easyx.h>
#include<graphics.h>
#include<deque>
#include<vector>
#include"sys.h"
#include<string>
#include"role.h"
//class Role;
using namespace std;
class Atlas//图片集合类
{
public:
	const IMAGE* get_image(int index)const;
	Atlas()
	{}
	Atlas(const char* imageName, int nums);
	Atlas(const char* image_path, const char* imageName, int nums);
	Atlas(const char* scene_name)
	{

		//string path = "source\\"+*scene_name+"";
	}
	virtual void draw_image(int posx,int posy,int index)
	{
		putimage(posx, posy, arr[index]);
	}
	//const scene_path
	virtual void add_image(const char* rootdir, const char* filename, int w,int h,int n = 1)
	{
		string t = "source\\" + string(rootdir) + "\\" + string(filename);
		for (int i = 1; i < n; i++)
		{
			fstream in;
			IMAGE* temp = new IMAGE;
			string path = t + " (" + to_string(i) + ")" + ".png";
			//string path = "E:\\zzs\\100floors\\NsHaft\\source\\scene\\menu\\back_ground (" + to_string(i) + ").png";
			in.open(path, std::ios::in);
			if (in.is_open() == false)
			{
				delete temp;
				perror(" ");
				return;
			}
			loadimage(temp,&path[0],w,h);
			arr.push_back(temp);
		}
		return;
	}
private:
	deque<IMAGE*>arr;
	/*Atlas(const Role& role)
	{
		*this = Atlas(role.get_role_name(), role.get_image_num());
	}
	Atlas(const Role* role)
	{
		*this = Atlas(role->get_role_name(), role->get_image_num());
	}*/
	//private:
		//std::vector<IMAGE*>arr;
};

class Animation
{
public:
	Animation(void)
	{}
	void showAnimation(const Role& role, ExMessage& msg);
};
class Point
{
	Point(int x, int y) :x(x), y(y)
	{}
	Point();
	int  x, y;

};


class Widget
{
public:
	Widget()
	{}
	Widget(int x, int y, int w, int h);
	Widget(int x, int y);
protected:
	int posx = 0, posy = 0, w, h;
};
