#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<unordered_map>
#include<map>
#include"unit.h"
extern IMAGE arrow[2];
extern IMAGE cursor[2];
extern IMAGE border[2];
const static double ratio = 7.0 / 10.0;
const static double bigger = 1.1;

//extern IMAGE* arrow;
//#define 
//#define MAPN
//(MAINW-BUTTONW)/2-------------------
// |----------------------------------------------------------------------------|
// |																			|
// |						[       start      ]									|
// |																			|
// |							
// 
// 												
// |																			|
// |						[		role		] 									|
// |																			|
// |																			|
// |																			|
// |																			|
// |						[		map			]									|			|
// |																				|
// |																			|
// |																			|
// |																			|
// |						[		exit		 ]									|
// |																			|
// |																			|
// |																			|
// -----------------------------------------------------------------------------
//



#pragma once
#include<iostream>
#include<fstream>
#include<easyx.h>
#include<graphics.h>
#include<deque>
#include<vector>
#include<string>
#include"role.h"
//class Role;

struct Pic
{
	Pic()
	{}
	Pic(IMAGE* ori, IMAGE* mask)
	{
		ori = (ori);
		mask = (mask);
		return;
	}
	IMAGE* ori;
	IMAGE* mask;
};
void draw_lucency(int x, int y, IMAGE* ori, IMAGE* mask);
using namespace std;
class Atlas//图片集合类
{
public:
	IMAGE* get_image(int index, int cate = 0);
	Atlas(int n)
	{
		for (int i = 0; i < n; i++)
		{
			arr.push_back(new IMAGE);
			arr_mask.push_back(new IMAGE);
		}
	}
	Atlas()
	{}
	Atlas(const char* rootdir, const char* s, int w, int h, int n);
	void role_add_image(const char* rootdir, const char* filename, int w, int h, int n, const char* filetype);
	IMAGE* get_mask_image(int index = 0)
	{
		if (index >= 0)
			return arr_mask[index];
	}
	void add_image(const char* rootdir, const char* filename, int w, int h, int n = 1, const char* filetype = ".png", const char* mask = "");
	Pic operator [](int index)
	{
		if (index < arr.size() && index >= 0)
			return Pic(arr[index], arr_mask[index]);
	}
	Pic get_pic(int index)
	{
		if (index < arr.size() && index >= 0)
			return Pic(arr[index], arr_mask[index]);
	}
	int get_size()
	{
		return  arr.size();
	}
private:
	deque<IMAGE*>arr;
	deque<IMAGE*>arr_mask;
};

using namespace std;

//extern int mianx, MAINY;
class Scene
{
public:
	Scene() = default;
	virtual void draw_pic() = 0;
	virtual void update_scene() = 0;
	virtual void exit_scene() = 0;
	virtual void enter_scene() = 0;
	virtual int process_command(ExMessage& msg) = 0;

};



class Button
{
public:

	Button()
	{
		images = new Atlas;
	}
	Button(const char* filename, const char* text_ = " ");

	void setpos(int x, int y)
	{
		this->x = x;
		this->y = y;
		area_w = { x + gap,y,x + gap + wordsw,y + h };
		return;
	}
	void init(const char* filename, const char* text_ = " ")
	{
		images->add_image(BTDIR, filename, BTW, BTH, 1, ".ico");
		images->add_image(BTDIR, filename, BTW, BTH, 1, ".ico", MASK);
		text = string(text_);
		return;
	}
	void draw_button(int posx, int posy)
	{
		draw_lucency(posx, posy, images->get_image(0), images->get_mask_image(0));
		return;
	}
	//xian & mask
	///zai ^ ori
	//(x+gap,y)
	//(x+gap+wordsw,y+h);
	void unin()
	{
		setbkmode(TRANSPARENT);;
		settextcolor(BLACK);
		settextstyle((area_w.top - area_w.bottom) * ratio, (area_w.right - area_w.left) / text.length() * ratio, "consola");;
		//draw_words();
	}
	void clicked()
	{
		setbkmode(OPAQUE);
		settextcolor(RED);
		setbkcolor(DARKGRAY);
		settextstyle((area_w.top - area_w.bottom) * ratio * bigger, (area_w.right - area_w.left) * bigger / text.length() * ratio, "consola");;
		//draw_words();
	}
	void hang_on()
	{
		setbkmode(OPAQUE);
		setbkcolor(DARKGRAY);
		setfillcolor(DARKGRAY);
		settextcolor(WHITE);
		settextstyle((area_w.top - area_w.bottom) * ratio, (area_w.right - area_w.left) / text.length() * ratio, "consola");;
	}
	//1 clicked 
	//0 no in 
	//2 hang on 
	void draw_words(int clicked_ = 0)
	{
		if (clicked_ == UNIN)
		{
			unin();
		}
		else if (clicked_ == CLICKED)
		{
			clicked();
		}
		if (clicked_ == HANGON)
		{
			hang_on();
		}
		drawtext(&text[0], &area_w, DT_CENTER | DT_BOTTOM);
		draw_lucency(area_w.left, area_w.top - 7, border, border + 1);
		return;
	}
	void draw_button()
	{
		draw_lucency(x, y, images->get_image(0), images->get_mask_image(0));
		draw_words(UNIN);
		return;
	}
	bool in_area(ExMessage& msg)
	{

		if (msg.x > area_w.left && msg.x < area_w.right && msg.y > area_w.top && msg.y < area_w.bottom)// && msg.x>x && msg.x<x + w && msg.y>y && msg.y < y + h)
		{
			return true;
		}
		else
		{
			return  false;
		}
	}
	int react(ExMessage& msg);
	const static int w = BTW, h = BTH;
	const static int gap = BTW * 2, wordsw = BTW * 4;
private:
	int x = 0, y = 0;
	string text;
	Atlas* images;
	RECT area_w;

};

//IMAGE Button ::arrow = 
enum StartOpt

{
	null = -1,
	startgame = 0,
	choose_role = 1,
	choose_map = 2,
	exit_game = 3,
};


enum Btname
{
	start_bt = 0,
	role_bt,
	map_bt,
	exit_bt,
};
class Start :public Scene
{
public:
	Start()
	{
		buttons = vector<Button*>(4);
		back_ground = new Atlas;
		back_ground->add_image(MAPDIR, "background", MAINW, MAINH, 5, ".png");
		init_button();

	}
	void init_button()
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i] = new Button;
		}
		buttons[start_bt]->init("start", "开始游戏");
		buttons[map_bt]->init("map", "选择地图");
		buttons[role_bt]->init("role", "选择角色");
		buttons[exit_bt]->init("exit", "退出游戏");
		locate_button();
	}
	void locate_button()
	{
		const int oriposx = (MAINW - Button::w) * 1.05 / 4;;
		int oriposy = (Button::h * 6);
		int gap = static_cast<double>(Button::h) * (2);
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->setpos(oriposx, oriposy + gap * i);
		}
		return;
	}
	void draw_pic()
	{

		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, back_ground->get_image(cur_back));
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->draw_button();
		}
		EndBatchDraw();
	}
	void exit_scene()
	{
		return;
	}
	void enter_scene();
	int process_command(ExMessage& msg);
	void ChooseMap(ExMessage& msg);
	void update_scene()
	{
		return;
	}
	IMAGE* get_background()
	{
		return back_ground->get_image(cur_back);
	}
private:
	const static int btnum = 4;
	vector<Button*>buttons;
	Atlas* back_ground;
	vector<string>map_explain;
	vector<string>role_explain;
	int cur_back = 0;
	int cur_role = 0;
};
class Board
{
public:
	void init()
	{
		img = new Atlas;
		//img->add_image()
	}
	int x;
	int y;
	int len;
	int type;
	bool exist;
	bool used;
	int stay;
private:
	Atlas* img;
};










