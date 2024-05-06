#pragma once
#include <ctime>
#include <easyx.h>

class Anime
{
public:
	const clock_t FPS = 1000 / 60;
	int begintime;
	int freamtime;
	static void anime_conveyor_right(int i);
	static void anime_fake(int i);
	static void anime_conveyor_left(int i);
};

