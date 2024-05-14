#define _CRT_SECURE_NO_WARNINGS
#include"all.h"
#include"Anime.h"
#include"scene.h"
#if 0
void Anime::ppt(Atlas* images, int delt,int trans)
{
	//for(int i = 0;i<)
	//(cur_back + 1 * delt + back_ground->get_size()) % back_ground->get_size();
}
#endif
void draw_lucency(int x, int y, IMAGE* ori, IMAGE* mask)
{
	putimage(x, y, mask, SRCAND);
	putimage(x, y, ori, SRCPAINT);
	return;
}
void draw_lucency(int x, int y,int w,int h, IMAGE* ori, IMAGE* mask)
{
	putimage(x, y,w,h ,mask,0,0, SRCAND);
	putimage(x, y,w,h, ori,0,0, SRCPAINT);
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

void Atlas::role_add_image(const char* rootdir, const char* filename, int n, int w, int h, const char* filetype)
{
	string tori = PICDIR + string("\\") + string(rootdir) + "\\" +"ori"+"\\"+string(filename);
	string tmask = PICDIR + string("\\") + string(rootdir) + "\\" +"mask"+"\\"+string(filename);
	for (int i = 1; i <= n; i++)
	{
		fstream in;
		IMAGE* ori_temp = new IMAGE;;
		IMAGE* mask_temp = new IMAGE;;
		string path1 = tori;
		string path2 = tmask;
		if (n > 1)
		{
			path2 += to_string(i)+" 拷贝";
			path1 += to_string(i)+" 拷贝";
		}
		path1 += filetype;
		path2 += filetype;
		//path1 = "E:\\zzs\\gitstore\\new\\picture\\FOX\\ori\\未标题-6.png";
		FILE* fp = fopen(&path1[0], "rb");
		if(fp == NULL)
		{
			perror("");
			cout << path1 << endl;
		}
		loadimage(ori_temp, &path1[0], w, h);
		loadimage(mask_temp, &path2[0], w, h);
		arr.push_back(ori_temp);
		arr_mask.push_back(mask_temp);
	}
	return;
}
void Atlas::add_image(const char* rootdir, const char* filename, int w, int h, int n, const char* filetype, const char* mask)
{
	string t = PICDIR + string("\\") + string(rootdir) + "\\" + string(filename) + mask;
	auto it = mask == "" ? &arr : &arr_mask;
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
		it->push_back(temp);
	}
	return;
}