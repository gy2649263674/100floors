
#pragma once
#include <Windows.h>
#include"scene.h"
class Character
{
public:
	Character()
	{}
	Character(const char *name,int run_pic_size);
	int x;
	int y;
	int h;
	int ob;
	int health;
	int curframe = 0;
	int dircetion;
	int uv;
	void character_move();
	bool is_dead();
	void exhibit(int dir = 0);
private:
	int runsize = 0;
	Atlas* images;
	Atlas* rimages;
	string name;
};

