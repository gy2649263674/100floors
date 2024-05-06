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
#define PICDIR "picture"
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
	virtual void add_image(const char* rootdir, const char* filename, int w, int h, int n = 1)
	{
		string t = PICDIR+string("\\") + string(rootdir) + "\\" + string(filename);
		for (int i = 1; i < n; i++)
		{
			fstream in;
			IMAGE* temp = new IMAGE;
			string path = t + " (" + to_string(i) + ")" + ".png";
			in.open(path, std::ios::in);
			if (in.is_open() == false)
			{
				delete temp;
				perror(" ");
				return;
			}
			loadimage(temp, &path[0], w, h);
			arr.push_back(temp);
		}
		return;
	}
	IMAGE*operator[](int index)
	{
		if (index < arr.size() && index)
			return arr[index];
	}
	int get_size()
	{
		return  arr.size();
	}
private:
	deque<IMAGE*>arr;
};
