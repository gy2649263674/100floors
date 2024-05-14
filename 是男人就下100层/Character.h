
#pragma once
#include <Windows.h>
#include"scene.h"
#include"board.h"

#define PICGAP 2
#define STOPGAP 8
extern Board board[150];
class Character
{
	friend void draw_lucency(Character& role, int direct);
public:
	Character()
	{}
	Character(const char* name, int run_pic_size, int standsize);
	int character_move();
	void set_sta()
	{
		this->h = 60;
		this->x = board[0].x + board[0].len / 2 - this->h / 2;
		this->y = board[0].y - this->h;
		this->health = 3;
	}
	void resetrun()
	{
		curframe = 0;
		act = 0;
	}
	void reset_standing()
	{
		stact = 0;
		standing_frame = 0;
	}
	Pic get_pic(int dir = RIGHT)
	{
		auto it = dir == LEFT ? rimages : images;
		return it->get_pic(curframe / PICGAP);
	}
	void draw_standing()
	{
		static auto it = direct == RIGHT ? images : rimages;;
		if (direct != 0)
		{
			it = direct == RIGHT ? images : rimages;
		}
		draw_lucency(x, y, it->get_image(standing_frame), it->get_mask_image(standing_frame));
		standing(direct);
	}
	void standing(int direct = RIGHT)
	{
		++stact;
		resetrun();
		if (stact / STOPGAP > standing_size)
		{
			stact = 0;
		}
		standing_frame = stact / STOPGAP;
		this->direct = direct;
	}
	void move()
	{
		//++curframe;
		++act;
		curframe = standing_size - 1 + (act / PICGAP == 0 ? 1 : act / PICGAP);
		if (curframe >= runsize - 1)
		{
			act = 0;
			curframe = standing_size - 1;
		}
	}

	int direct;
	int x;
	int y;
	int h;
	int ob;
	int health;
	int stact = 0;
	int curframe = 0;
	int uv;
	int dircetion;
	int jump = 0;
	bool have_armo;
	int standing_size = 0;
	int standing_frame = 0;
	bool is_dead();
	void exhibit(int dir = LEFT);
	int act = 0;
private:
	int runsize = 0;
	Atlas* images;
	Atlas* rimages;
	string name;
};

