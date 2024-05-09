#pragma once
#include <ctime>
#include <easyx.h>
#include"scene.h"
class Anime
{
public:
	//const clock_t FPS = 1000 / 60;
	int begintime;
	int freamtime;
	static void anime_conveyor_right(int i);
	static void anime_fake(int i);
	static void anime_conveyor_left(int i);
	static void ppt(Atlas* image,int dir,int transparent = false);
};

