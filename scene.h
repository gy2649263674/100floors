#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include"graph.h"
#include"sys.h"
using namespace std;
class scene
{
public:
	scene() = default;
	virtual void draw_pic() = 0;
	virtual void update_scene() = 0;
	virtual void exit_scene() = 0;
	virtual void enter_scene() = 0;
	virtual void process_command() = 0;

};
class Menu :public scene
{
public:
	Menu()
	{
		initgraph(WINW, WINH);
	}
	void draw_pic ()
	{}
private:
	Atlas* img;
};
class Playing :public scene
{
public:
	Playing();
	void draw_pic()
	{
	}
private:
	Atlas* menu_atlas;
	//int widgetw, widgeth, menux, menuy;
};

class GameOver :public scene
{
public:

};
