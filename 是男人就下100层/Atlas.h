#pragma once
#include"unit.h"
#include<deque>
using namespace std;
class Atlas
{
public:
	IMAGE* get_image(int index, int cate = 0);
	Atlas(int n)
	{
		for (int i = 0; i < n; i++)
		{
			this->arr.push_back(new IMAGE);
			arr_mask.push_back(new IMAGE);
		}
	}
	Atlas()
	{}
	Atlas(const char* rootdir, const char* s, int n, int w = ROLEW, int h = ROLEH);
	void role_add_image(const char* rootdir, const char* filename, int n, int w = ROLEW, int h = ROLEH, const char* filetype = ".png");
	IMAGE* get_mask_image(int index = 0)
	{
		if (index >= 0)
			return arr_mask[index];
	}
	void add_image(const char* rootdir, const char* filename, int w, int h, int n = 1, const char* filetype = ".png", const char* mask = "");
	int get_size()
	{
		return  arr.size();
	}
	void push(IMAGE* img)
	{
		arr.push_back(img);

	}
	void left()
	{
		arr.push_front(arr.back());
		arr.pop_back();
		if (!arr_mask.empty())
		{
			arr_mask.push_front(arr.back());
			arr_mask.pop_back();
		}
	}
	void right()
	{
		arr.push_back(arr.front());
		arr_mask.push_back(arr.front());
		arr_mask.pop_front();
		arr.pop_front();
	}
	deque<IMAGE*>arr;
	deque<IMAGE*>arr_mask;
};
void flip(Atlas* pic, Atlas* rpic);
struct Picset
{
	int stand, run = 0;
	Atlas* pic = 0;
	Atlas* rpic = 0;
	Picset()
	{}
	Picset(const char* rootdir, int n, int run, int stand, int w = ROLEW, int h = ROLEH, const char* filename = "")
	{
		pic = new Atlas(rootdir, filename, n, w, h);
		rpic = new Atlas(n);
		flip(pic, rpic);
		this->run = run;
		this->stand = stand;
	}
};
