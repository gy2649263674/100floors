
#pragma once

#include"board.h"
#include<string>
#include"Atlas.h"
#define PICGAP 2
#define STOPGAP 8
class Character;
void draw_lucency(Character& role, int direct);
void draw_lucency(int x, int y, IMAGE* ori, IMAGE* mask);
class Character
{
	friend void draw_lucency(Character& role, int direct);
	friend void draw_lucency(Character& role, int direct);
public:
	Character()
	{}
	Character(const char* name, int run_pic_size, int standsize,Picset *pic);
	int character_move();
	void set_sta(Board board)
	{
		this->h = 60;
		this->x = board.x + board.len / 2 - this->h / 2;
		this->y = board.y - this->h;
		this->health = 3;
		this->h = 60;
		this->have_armo = false;
		this->jump = 100;
		this->health = 3;
		this->ob = -1;
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
	void change_app(Picset*img)
	{
		this->images = img->pic;
		this->rimages = img->rpic;
		this->standing_size = img->stand;;
		this->runsize = img->run;
	}
	void draw_score()
	{
		//char sc[20] = "";
		settextstyle(30, 30, "Algerian");
		settextcolor(RGB(250, 240, 0));
		outtextxy(780, 100, "SCORE: ");
		settextcolor(WHITE);
		settextstyle(20, 20, "OCR A");
		outtextxy(780, 150, &(to_string(score))[0]);
		//outtextxy(800, 100, sc);
	}

	bool is_dead();
	int exhibit(int dir, IMAGE* back = 0);
	int direct = 0;
	int x = 0;
	int y = 0;
	int h = 0;
	int ob = 0;
	int health = 0 ;
	int stact = 0;
	int curframe = 0;
	int uv = 0;
	int dircetion = 0;
	int jump = 0;
	bool have_armo;
	int standing_size = 0;
	int runsize = 0;
	int standing_frame = 0;
	int score = 0;
	int act = 0;
private:
	Atlas* images;
	Atlas* rimages;
	std::string name;
};
