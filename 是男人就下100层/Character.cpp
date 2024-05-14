﻿#include "Character.h"
#include "easyx.h"
#include "Draw.h"
#include "Timer.h"
#include <ctime>
#include"unit.h"
#include"Atlas.h"

extern Board board[150];
extern int act;
const double conveyer_ratio = 1.5;
extern Board roof;
extern IMAGE character_img[10];
extern IMAGE character_img_mask[10];
extern ExMessage msg;
const double gap = 1000.0 / FRAME;
const int yu = 500;
#define SPEED 150
#define INCREASE 50
#define FALL_INCREASE 0
static double lspeed = SPEED;
static double rspeed = SPEED;
using namespace std;
int Character::character_move()
{
	static double G = 6;
	static int pre = RIGHT;
	if (GetAsyncKeyState(VK_LEFT) && x > 0)
	{
		rspeed = SPEED;
		lspeed += INCREASE;
		cout << "rspeed :" << rspeed << " ";
		cout << "lspeed :" << lspeed << endl;
		x -= min(lspeed, yu) * gap;
		msg.vkcode = VK_LEFT;
		move();
		pre = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && x < 750)
	{
		lspeed = SPEED;
		rspeed += INCREASE * 4;
		x += min(rspeed, yu) * gap;
		cout << "rspeed :" << rspeed << " ";
		cout << "lspeed :" << lspeed << endl;
		msg.vkcode = VK_RIGHT;
		move();
		pre = RIGHT;

	}
	else if (GetAsyncKeyState(VK_UP) && x < 750)
	{
		y -= 50;
	}
	else if (GetAsyncKeyState(VK_DOWN) && x < 750)
	{
		y += 50;
	}
	else
	{
		if (lspeed != SPEED || rspeed != SPEED)
		{
			lspeed = SPEED;
			rspeed = SPEED;
			reset_standing();
		}
		this->direct = pre;
		standing(pre);
		pre = 0;
	}
	flushmessage();
	//判断玩家在哪一块板子上
	for (int i = 0; i < 150; i++)
	{
		int x2 = this->x + h / 2;
		int y2 = this->y + h;
		if (x2 >= board[i].x && x2 <= board[i].len + board[i].x
			&& y2 >= board[i].y - Board::V*FRAME/4 && y2 <= board[i].y + Board::V*FRAME/4)
		{
			this->y = board[i].y - h;
			ob = i;
			if (board[i].type == 0 && board[i].have_item == true)
			{
				if (board[i].item_type == 0)
				{
					health = 3;
					board[i].have_item = false;
				}
				else if (board[i].item_type == 1)
				{
					if (have_armo == false)
					{
						board[i].have_item = false;
						have_armo = true;
					}
				}

				else if (board[i].item_type == 2)
				{
					board[i].have_item = false;
				}

			}
			if (board[i].type == 1 && board[i].used == false)
			{
				if (have_armo == true)
				{
					have_armo = false;
				}
				else
				{
					health--;
				}
				board[i].used = true;
				break;
			}
			else if (board[i].type == 2)
			{
				board[i].stay++;
				if (board[i].stay >= 10)
				{
					y += Board::V * FRAME/4;
					break;

				}
			}
			else if (board[i].type == 3)
			{
				if (x > 0)
					x -= SPEED * gap * conveyer_ratio;
				break;
			}
			else if (board[i].type == 4)
			{
				if (x < 900)
					x += SPEED * gap * conveyer_ratio;
				break;
			}
			else if (board[i].type == 5)
			{
				jump = 10-Board::V/10;
				y -= Board::V*FRAME/4;
				break;
			}
			break;
		}
		else
			ob = -1;
	}
	if (jump)
	{
		y -= 10;
		jump--;
		//return 0;
	}
	else
	{
		//if(peekmessage(&msg, -1);

	//	system("pause");
	}

	if (ob == -1)
	{
		y += G += 0.3;
	}
	else
	{
		G = FALL_INCREASE;
	}
	if (y <= 0 && roof.used == false)
	{
		if (have_armo == true)
		{
			have_armo = false;
		}
		else
		{
			health--;
		}
		roof.used = true;
	}
	if (y > 720)
	{
		health = 0;
	}
	if (y > 0)
	{
		roof.used = false;
	}
	return pre;
}

void flip(Atlas* s, Atlas* d)
{
	for (int i = 0; i < s->get_size(); i++)
	{
		IMAGE* src = s->get_image(i);
		IMAGE* des = d->get_image(i);
		int h = src->getheight();
		int w = src->getwidth();
		if (des->getwidth() != w || des->getheight() != h)
		{
			des->Resize(w, h);
		}
		DWORD* des_ = GetImageBuffer(des);
		DWORD* src_ = GetImageBuffer(src);
		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++)
				des_[y * w + w - x] = src_[y * w + x];
	}
	return;
}


void filp(IMAGE* src, IMAGE* des)
{
	int h = src->getheight();
	int w = src->getwidth();
	if (des->getwidth() != w || des->getheight() != h)
	{
		des->Resize(w, h);
	}
	DWORD* des_ = GetImageBuffer(des);
	DWORD* src_ = GetImageBuffer(src);
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			des_[y * w + w - x] = src_[y * w + x];
	return;
}
bool Character::is_dead()
{
	if (health <= 0)
	{
		return true;
	}
	return false;
}
#include<graphics.h>
#include<easyx.h>
Character::Character(const char* name, int n, int standing_size, Picset* img)
{
	//images = img.pic;//new Atlas(name, "未标题-", runsize, ROLEW, ROLEH);
	//rimages = img.rpic;//new Atlas(runsize);
	change_app(img);
	this->runsize = img->run;
	this->standing_size = img->stand;
	this->standing_frame = 0;
	set_sta(board);
	return;
}
void draw_lucency(Character& role, int direct);
void draw_lucency(int x, int y, int w, int h, IMAGE* ori, IMAGE* mask);

int co = 0;
int Character::exhibit(int direct,  IMAGE* back)
{
	ExMessage msg;
	Atlas* temp = direct == RIGHT ? images : rimages;
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, back);
	draw_lucency(x, y, temp->get_image(0), temp->get_mask_image(0));
	++co;
	cout << "co" << co << endl;
	while (1)
	{
		while (peekmessage(&msg, EX_KEY)|1)
		{
			for (int i = 0;1; i++)
			{
				peekmessage(&msg, EX_KEY);
				if (msg.vkcode == VK_RETURN)
				{
					return 1;
				}
				else if (msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT)
				{
					ExMessage m = {};
					msg = m;
					return 0;
				}
				static int picfp = i / PICGAP/3;
				picfp = i / PICGAP/3;
				i = picfp >= runsize ? 0 : ++i;
				BeginBatchDraw();
				cleardevice();
				putimage(0, 0, back);
				draw_lucency(x, y, temp->get_image(picfp), temp->get_mask_image(picfp));
				EndBatchDraw();
				Timer::endkeep(FRAME);
			}
		}
	}
	return 0;
}
