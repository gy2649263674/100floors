#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include"graph.h"
#include"sys.h"

#define MAINX 256
#define MAINY 256
#define MAINW 660
#define MAINH 1024
#define  BTW 128
#define BTH 64
#define BTPOSX 250
#define BTPOSY 20
#define BTPOSGAP 20
#define MAPNUM 5
#define WORDSX 
#define WORDSX 
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
class Button :public Atlas
{
public:
	Button()
	{

	}
	Button(int n)
	{

	}
	bool in_area(ExMessage& msg)
	{
		if (msg.x > x && msg.x<x + w && msg.y>y && msg.y < y + h)
		{
			react();
			return true;
		}
		else
		{
			return  false;
		}
	}
	void react()
	{

	}
private:
	int x, y, w, h;
	Atlas* images;
};
enum StartOpt
{
	null = -1,
	choose_role,
	startgame,
	choose_map,
	exit_game,
};
class Start :public Scene
{
public:

	Start()
	{
		back_ground = new Atlas;
		start_button = new Button;
		role_button = new Button;
		map_button = new Button;
		exit_button = new Button;
		back_ground->add_image("scene\\menu", "back_ground", BTW, BTH, 1);
		start_button->add_image("scene\\menu", "start", BTW, BTH, 1);
		map_button->add_image("scene\\menu", "map", MAINW, MAINH, MAPNUM);
		role_button->add_image("scene\\menu", "role", BTW, BTH, 1);
		exit_button->add_image("scene\\menu", "exit", BTW, BTH, 1);
	}
	void draw_pic()
	{
		cleardevice();
		setfillcolor(theme[cur_back]);
		BeginBatchDraw();
		setbkcolor(theme[cur_back]);
		putimage(MAINX, MAINY, back_ground->get_image(cur_back));
		putimage(BTPOSX, BTPOSY, start_button->get_image(0));
		putimage(BTPOSX, BTPOSY + BTPOSGAP, role_button->get_image(0));
		putimage(BTPOSX, BTPOSY + BTPOSGAP * 2, map_button->get_image(0));
		putimage(BTPOSX, BTPOSY + BTPOSGAP * 3, exit_button->get_image(0));
		EndBatchDraw();
	}
	void choose_menu()
	{

	}
	void ChooseMap(ExMessage& msg);
	void exit_scene()
	{

	}
	void enter_scene();
	void ExplainMap();
	int process_command(ExMessage& msg);
	void update_scene()
	{

	}
private:
	Atlas* back_ground;
	vector<string>map_explain;
	vector<string>role_explain;
	Button* start_button;
	Button* role_button;
	Button* map_button;
	Button* exit_button;
	vector<int>theme;
	int cur_back = 0;
	int cur_role = 0;
	//Atlas* back_ground;
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

//class Map :public Scene
//{
//public:
//	void draw_pic();
//	void update_scene();
//	void exit_scene();
//	void enter_scene();
//	int process_command(ExMessage& msg);
//};
