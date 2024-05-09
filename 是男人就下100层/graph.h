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
void draw_lucency(int x, int y, IMAGE* ori, IMAGE* mask);
using namespace std;
class Atlas//图片集合类
{
public:
	IMAGE* get_image(int index, int cate = 0);
	Atlas()
	{}
	Atlas(const char* imageName, int nums);
	Atlas(const char* image_path, const char* imageName, int nums);
	IMAGE* get_mask_image(int index = 0)
	{
		if (index >= 0)
			return arr_mask[index];
	}
	virtual void add_image(const char* rootdir, const char* filename, int w, int h, int n = 1, const char* filetype = ".png", const char* mask = "")
	{
		string t = PICDIR + string("\\") + string(rootdir) + "\\" + string(filename) + mask;
		//图片标号从1开始
		for (int i = 1; i <= n; i++)
		{
			fstream in;
			IMAGE* temp = new IMAGE;
			string path = t;
			if (n > 1)
			{
				path += " (" + to_string(i) + ")";
			}
			path += filetype;
			in.open(path, std::ios::in);
			if (in.is_open() == false)
			{
				delete temp;
				printf("\033[31m%s没有成功导入检查路径\033[0m\n", &path[0]);
				perror("\033[31m\n");
				return;
			}
			loadimage(temp, &path[0], w, h);
			if (mask == "")
			{
				arr.push_back(temp);
			}
			else
			{

				arr_mask.push_back(temp);
			}
		}
		return;
	}
	IMAGE* operator[](int index)
	{
		if (index < arr.size() && index >= 0)
			return arr[index];
	}
	int get_size()
	{
		return  arr.size();
	}
private:
	deque<IMAGE*>arr;
	deque<IMAGE*>arr_mask;
};
