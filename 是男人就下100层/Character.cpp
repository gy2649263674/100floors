#include "Character.h"
#include "easyx.h"
#include "Draw.h"
#include "Timer.h"
#include <ctime>
#include"unit.h"
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
#define INCREASE 40
#define FALL_INCREASE 6
static double lspeed = SPEED;
static double rspeed = SPEED;

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
		rspeed += INCREASE*4;
		x += min(rspeed, yu) * gap;
		cout << "rspeed :" << rspeed <<" ";
		cout << "lspeed :" << lspeed << endl;
		msg.vkcode = VK_RIGHT;
		move();
		pre = RIGHT;
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
			&& y2 >= board[i].y - 6 && y2 <= board[i].y + 6)
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
					if(have_armo==false)
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
					y += 5;
					break;

				}
			}
			else if (board[i].type == 3)
			{
				if (x > 0)
					x -= SPEED *gap* conveyer_ratio;
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
				jump = 0;
				y -= 10;
				break;
			}
			break;


		}
		else
			ob = -1;
	}
	if (jump<10)
	{
		y -= 10;
		jump++;
		return;
	}
	if (ob === -1)
	{
		y += G+=0.3;
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

Character::Character(const char* name, int runsize,int standing_size)
{
	images = new Atlas(name, "未标题-", ROLEW, ROLEH, runsize);
	rimages = new Atlas(runsize);
	this->runsize = runsize;
	this->standing_size = standing_size;
	this->standing_frame = 0;
	for (int i = 0; i < images->get_size(); i++)
	{
		filp(images->get_image(i), rimages->get_image(i));
		filp(images->get_mask_image(i), rimages->get_mask_image(i));
	}
	set_sta();
	return;
}

void Character::exhibit(int direct)
{
	Atlas* temp = direct == RIGHT ? images : rimages;
	for (int i = 0; ; i++)
	{
		i = i % (runsize - 1);
		i = i == 0 ? 1 : i;
		Timer::beginkeep();
		BeginBatchDraw();
		cleardevice();
		draw_lucency(x, y, temp->get_image(i), temp->get_mask_image(i));
		EndBatchDraw();
		Timer::endkeep();
	}
	curframe = ((++curframe) %= runsize) == 0 ? 1 : curframe;
}
