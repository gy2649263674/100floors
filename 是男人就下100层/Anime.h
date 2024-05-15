#pragma once
#include <ctime>
#include <easyx.h>
#include"scene.h"
#include"board.h"
class Anime
{
public:
	//const clock_t FPS = 1000 / 60;
	int begintime;
	int freamtime;
	static void anime_conveyor_right(int i);
	static void anime_fake(Board& a)
	{
		//draw_lucency(a.x,a.y,
		//putimage()
	}
	static void draw_trampolines(Board& bd, unordered_map<Boardtype, map<int, IMAGE>>& boardimg, unordered_map<Boardtype, map<int, IMAGE>>& boardimg_mask)
	{
		draw_lucency(bd.x, bd.y, &boardimg[trampolinetype][bd.stay], &boardimg[trampolinetype][bd.stay]);
	}
	static void anime_conveyor_left(int i);
	static void ppt(Atlas* image, int dir, int transparent = false);

};

