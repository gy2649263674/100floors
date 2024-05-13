
#pragma once
#include <Windows.h>
#include"scene.h"
#define PICGAP 4
extern Board board[150];
class Character
{
	friend void draw_lucency(Character& role, int direct);
public:
	Character()
	{}
	void set_sta()
	{
		this->h = 60;
		this->x = board[0].x + board[0].len / 2 - this->h / 2;
		this->y = board[0].y - this->h;
		this->health = 3;
	}
	void reset()
	{
		curframe = 0;
		act = 0;
	}
	Character(const char* name, int run_pic_size);
	Pic get_pic(int dir = RIGHT)
	{
		auto it = dir == LEFT ? rimages : images;
		return it->get_pic(curframe / PICGAP);
	}
	void standing(int direct = RIGHT)
	{
		auto it = direct == RIGHT ? images : rimages;
		reset();
		draw_lucency(x, y, it->get_image(0), it->get_mask_image(0));
	}
	int x;
	int y;
	int h;
	int ob;
	int health;
	int curframe = 0;
<<<<<<< Updated upstream
=======
	int uv;
>>>>>>> Stashed changes
	int dircetion;
	void character_move();
	bool is_dead();
	void exhibit(int dir = LEFT);
	int act = 0;
	void move()
	{
		//++curframe;
		++act;
		curframe = act / PICGAP;
		if (curframe >= runsize-1)
		{
			act = 0;
			curframe = 0;
		}
	}
private:
	int runsize = 0;
	Atlas* images;
	Atlas* rimages;
	string name;
};

