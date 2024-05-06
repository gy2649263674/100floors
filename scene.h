#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include"graph.h"
#include"sys.h"

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



#define MAINW 660
#define MAINH 1024
#define BUTTONW 128
#define BUTTONH 64
#define BTPOSX 250
#define BTPOSY 20
#define BTPOSGAP 20
#define MAPNUM 5

using namespace std;
extern int winx, winy;
class scene
{
public:
	scene() = default;
	virtual void draw_pic() = 0;
	virtual void update_scene() = 0;
	virtual void exit_scene() = 0;
	virtual void enter_scene() = 0;
	virtual void process_command(ExMessage &msg) = 0;

};
class Button
{
public:
	Button()
	{

	}
	Button(int n)
	{

	}
	bool in_area(ExMessage&msg)
	{
		return msg.x > x && msg.x<x + w && msg.y>y && msg.y < y + h;
	}
	bool react()
	{

	}
private:
	int x, y, w, h;
	Atlas* a;
};


class Start :public scene
{
public:
	Start()
	{
		//initgraph(WINW, WINH);
		back_ground = new Atlas;
		start_button = new Atlas;
		role_button = new Atlas;
		map_button = new Atlas;
		exit_button = new Atlas;
		back_ground->add_image("scene\\menu", "back_ground", MAPNUM);
		start_button->add_image("scene\\menu", "start", 2);
		map_button->add_image("scene\\menu", "map", MAPNUM);
		role_button->add_image("scene\\menu", "role", 2);
		exit_button->add_image("scene\\menu", "exit", 2);
	}
	void draw_pic()
	{
		cleardevice();
		setfillcolor(0xDEA1A3);
		BeginBatchDraw();
		setorigin(winx, winy);
		initgraph(MAINW, MAINH);
		putimage(BTPOSX, BTPOSY, start_button->get_image(0));
		putimage(BTPOSX, BTPOSY + BTPOSGAP, role_button->get_image(0));
		putimage(BTPOSX, BTPOSY + BTPOSGAP * 2, map_button->get_image(0));
		putimage(BTPOSX, BTPOSY + BTPOSGAP * 3, exit_button->get_image(0));
		EndBatchDraw();
	}
	void exit_scene()
	{

	}
	void enter_scene()
	{

	}
	void process_command(ExMessage &msg)
	{
	}
	void update_scene()
	{

	}
private:
	Atlas* back_ground;
	Atlas* start_button;
	Atlas* role_button;
	Atlas* map_button;
	Atlas* exit_button;
};
class Playing :public scene
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

class GameOver :public scene
{
public:

};
