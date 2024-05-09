#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<unordered_map>
#include<map>
#include"sys.h"

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










// |----------------------------------------------------------------------------|
// |	[pause]									HP:		----------------------								|
// |													----------------------
//					
// |							
// 
// 												
// |																			|
// |															|
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

//inline



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

	int react(ExMessage& msg)
	{
		while (in_area(msg))
		{
			draw_words(HANGON);
			draw_lucency(x +wordsw+gap*1.5, y, arrow, arrow + 1);
			peekmessage(&msg, EX_MOUSE);
			if (msg.lbutton)
			{
				draw_words(HANGON);
				draw_lucency(msg.x - 20, msg.y - 20, cursor, cursor + 1);
				while (msg.message != WM_LBUTTONUP)
				{
					peekmessage(&msg, EX_MOUSE);
				}
				if (in_area(msg))
				{
					draw_words(CLICKED);
					return true;
				}
				else
				{
					draw_words(UNIN);
					continue;
				}
			}
		}
	}
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

	}
	void enter_scene();
	int process_command(ExMessage& msg);
	void ChooseMap(ExMessage& msg);
	void update_scene()
	{

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
class Playing :public Scene
{
public:
	Playing();
	void draw_pic()
	{
	}
private:

	//IMAGE* start;
	//IMAGE* exit;
	//IMAGE* role;
	//IMAGE*
		//Atlas* menu_atlas;
		//int widgetw, widgeth, menux, menuy;
};
