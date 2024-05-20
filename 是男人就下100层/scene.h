#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<unordered_map>
#include<map>
#include<deque>
#include"unit.h"
#include "Character.h"
class Character;
extern IMAGE arrow[2];
extern IMAGE cursor[2];
extern IMAGE border[2];
const static double ratio = 7.0 / 10.0;
const static double bigger = 1.1;
using namespace std;
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
#include"Atlas.h"

void draw_lucency(int x, int y, IMAGE* ori, IMAGE* mask);
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
		if (images)
		{
			images->add_image(BTDIR, filename, BTW, BTH, 1, ".ico");
			images->add_image(BTDIR, filename, BTW, BTH, 1, ".ico", MASK);
		}
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
		settextcolor(WHITE);
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
		settextcolor(BLACK);
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
		//draw_lucency(x, y, &border[0], &border[1]);
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
	Atlas* images = NULL;
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
	change_difficult = 4
};


enum Btname
{
	start_bt = 0,
	role_bt,
	map_bt,
	choosemode_bt,
	exit_bt,
};
class Start :public Scene
{
public:
	entertain setmode(ExMessage& msg);
	Start()
	{
		buttons = unordered_map<int, Button*>(5);
		back_ground = new Atlas;
		back_ground->add_image(MAPDIR, "background", MAINW, MAINH, 6, ".png");
		init_button();
	}
	void init_button()
	{
		for (int i = 0; i < 5; i++)
		{
			buttons[i] = new Button;
		}
		buttons[start_bt]->init("start", "开始游戏");
		buttons[map_bt]->init("map", "选择地图");
		buttons[role_bt]->init("role", "选择角色");
		buttons[exit_bt]->init("exit", "退出游戏");
		buttons[choosemode_bt]->init("mode", "选择模式");
		locate_button();
	}
	void locate_button()
	{
		const int oriposx = (MAINW - Button::w) * 1.05 / 4;;
		int oriposy = (Button::h * (8 - buttons.size()));
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
	void change_role(Character* role, deque<Picset* >& picarr)
	{
		ExMessage msg;
		int ck = 0;
		while (1)
		{
			while (peekmessage(&msg, EX_KEY))
			{
				cout << ++ck << " ";
				int delt = (msg.vkcode) - (VK_LEFT + VK_RIGHT) / 2;//正负绝对左右移动
				cur_role = (cur_role + 1 * delt + picarr.size()) % picarr.size();
				role->change_app(picarr[cur_role]);
				if (role->exhibit(RIGHT, back_ground->get_image(cur_back)) == 1)
				{
					return;
				}
			}
		}
	}

private:
	const static int btnum = 4;
	unordered_map<int, Button*>buttons;
	Atlas* shot = 0;
	Atlas* back_ground;
	deque<string>mode_explain{ "normal","jump_jump","fake world","runer" };
	vector<string>map_explain;
	vector<string>role_explain;
	int cur_back = 0;
	int cur_role = 0;
	int cur_mode = 0;
};

void flip(Atlas* a, Atlas* b);
