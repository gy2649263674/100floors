#pragma once
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<vector>
#include"role.h"
class Atlas//图片集合类
{
public:
	friend void test(Atlas&a);
	const IMAGE* get_image(int index)const;
	Atlas()
	{}
	Atlas(const char* imageName, int nums);
	Atlas(const char* image_path, const char* imageName, int nums);
	/*Atlas(const Role& role)
	{
		*this = Atlas(role.get_role_name(), role.get_image_num());
	}
	Atlas(const Role* role)
	{
		*this = Atlas(role->get_role_name(), role->get_image_num());
	}*/
	~Atlas()
	{
		for (auto &it : arr)
		{
			delete it;
		}
	}
	void add_image(const char *name ,int n)
	{
		 *this= Atlas(name, n);
	}
private:
	std::vector<IMAGE*>arr;
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
class Button :public Widget
{
public:
	Button(int x, int y, int h, int w)
	{}
private:
	Atlas images;
};


