#include "Character.h"
#include "easyx.h"
#include "Draw.h"
#include "Timer.h"
#include <ctime>
#include"unit.h"
extern Board board[150];
extern int act;
extern Board roof;
extern IMAGE character_img[10];
extern IMAGE character_img_mask[10];
extern ExMessage msg;
const double gap = 1000.0 / FRAME;
const int yu = 250;
#define SPEED 40
static double lspeed = SPEED;
static double rspeed = SPEED;
void Character::character_move()
{
<<<<<<< Updated upstream

	int speed = 8;
=======
	//int speed = 8;
>>>>>>> Stashed changes
	if (GetAsyncKeyState(VK_LEFT) && x > 0)
	{
		if (rspeed != SPEED)
		{
			rspeed = SPEED;
		//	Sleep(FRAME);
			//standing();
		}
		lspeed += 10;
		x -= min(lspeed, yu) * gap;
		msg.vkcode = VK_LEFT;
		move();
	}
	else if (GetAsyncKeyState(VK_RIGHT) && x < 750)
	{
		if (lspeed != SPEED)
		{
			lspeed = SPEED;
			//	Sleep(FRAME);
				//standing();
		}
		rspeed += 10;
		x += min(rspeed, yu) * gap;
		msg.vkcode = VK_RIGHT;
		move();
	}
	else
	{
		standing();
	}
	/*//判断玩家在哪一块板子上
	for (int i = 0; i < 150; i++)
	{
		int x2 = this->x + h / 2;
		int y2 = this->y + h;
		if (x2 >= board[i].x && x2 <= board[i].len + board[i].x
<<<<<<< Updated upstream
			&& y2 >= board[i].y - 10 && y2 <= board[i].y + 10)
=======
			&& y2 >= board[i].y - 6 && y2 <= board[i].y + 6)
>>>>>>> Stashed changes
		{
			this->y = board[i].y - h;
			ob = i;
			if (board[i].type == 1 && board[i].used == false)
			{
				health--;
				board[i].used = true;
				break;
			}
			else if (board[i].type == 2)
			{
				//y += 3;
				board[i].stay++;
				if (board[i].stay > 10)
				{
					y += 3;
					break;

				}
				//Anime::anime_fake(i);
				//break;
			}
			else if (board[i].type == 3)
			{
				if (x > 0)
					x -= SPEED / 4;
				break;
			}
			else if (board[i].type == 4)
			{
				if (x < 900)
<<<<<<< Updated upstream
					x += speed / 4;
=======
					x += SPEED / 4;
>>>>>>> Stashed changes
				break;
			}
			break;
		}
		else
			ob = -1;
	}
<<<<<<< Updated upstream
	if (ob = -1)
=======
	if (ob == -1)
>>>>>>> Stashed changes
	{
		y += 6;
	}
	if (y <= 0 && roof.used == false)
	{
		health--;
		roof.used = true;
	}
	if (y > 720)
	{
		health = 0;
	}
	if (y > 0)
	{
		roof.used = false;
	}*/

}

//void Character::character_move()
//{
//
//	int speed = 5;
//	if (GetAsyncKeyState(VK_LEFT) && x > 0)
//	{
//		x -= speed;
//		msg.vkcode == VK_LEFT;
//		act++;
//	}
//	if (GetAsyncKeyState(VK_RIGHT) && x < 750)
//	{
//		x += speed;
//		msg.vkcode = VK_RIGHT;
//		act++;
//	}
//	/*putimage(x, y, &character_img_mask[0], SRCAND);
//	putimage(x, y, &character_img[0], SRCPAINT);*/
//	if (act > 20)
//		act = 1;
//	//判断玩家在哪一块板子上
//	for (int i = 0; i < 150; i++)
//	{
//		int x2 = this->x + h / 2;
//		int y2 = this->y + h;
//		if (x2 >= board[i].x && x2 <= board[i].len + board[i].x
//			&& y2 >= board[i].y - 8 && y2 <= board[i].y + 8)
//		{
//			this->y = board[i].y - h;
//			ob = i;
//			if (board[i].type == 1 && board[i].used == false)
//			{
//				health--;
//				board[i].used = true;
//				break;
//			}
//			else if (board[i].type == 2)
//			{
//				//y += 3;
//				board[i].stay++;
//				if (board[i].stay > 10)
//				{
//					y += 3;
//					break;
//
//				}
//				//Anime::anime_fake(i);
//				//break;
//			}
//			else if (board[i].type == 3)
//			{
//				if (x > 0)
//					x -= speed / 4;
//				break;
//			}
//			else if (board[i].type == 4)
//			{
//				if (x < 900)
//					x += speed / 4;
//				break;
//			}
//			else if (board[i].type == 5)
//			{
//				uv = 5;
//				y -= 5;
//				Timer::beginkeep();
//				break;
//			}
//			break;
//		}
//		else
//			ob = -1;
//	}
//	if (uv > 0)
//	{
//		y -= uv;
//		uv -= 10 * (clock() - Timer::time) / 100;
//		return;
//	}
//	if (ob == -1)
//	{
//		y += 6;
//	}
//	if (y <= 0 && roof.used == false)
//	{
//		health--;
//		roof.used = true;
//	}
//	if (y > 720)
//	{
//		health = 0;
//	}
//	if (y > 0)
//	{
//		roof.used = false;
//	}
//}
void filp(Atlas* src, Atlas* des)
{

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

Character::Character(const char* name, int runsize)
{
	images = new Atlas(name, "run", ROLEW, ROLEH, runsize + 1, "_maks");
	rimages = new Atlas(runsize + 1);
	this->runsize = runsize;
	for (int i = 0; i < images->get_size(); i++)
	{
		filp(images->get_image(i), rimages->get_image(i));
		filp(images->get_mask_image(i), rimages->get_mask_image(i));
	}
	set_sta();
	//exhibit(LEFT);
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
