#include "Character.h"
#include "board.h"
#include "easyx.h"
#include "Draw.h"
#include "Timer.h"
#include <ctime>
#include"unit.h"
extern Board board[10];
extern int act;
extern IMAGE character_img[10];
extern IMAGE character_img_mask[10];
extern ExMessage msg;
void Character::character_move()
{

	int speed = 8;
	if (GetAsyncKeyState(VK_LEFT) && x > 0)
	{
		x -= speed;
		msg.vkcode == VK_LEFT;
		/*Draw::flipimage(x, y, character_img_mask[act], SRCAND);
		Draw::flipimage(x, y, character_img[act], SRCPAINT);*/
		act++;
	}
	if (GetAsyncKeyState(VK_RIGHT) && x < 900)
	{
		x += speed;
		msg.vkcode = VK_RIGHT;
		/*putimage(x, y, &character_img_mask[act], SRCAND);
		putimage(x, y, &character_img[act], SRCPAINT);*/
		act++;
	}
	/*putimage(x, y, &character_img_mask[0], SRCAND);
	putimage(x, y, &character_img[0], SRCPAINT);*/
	if (act > 20)
		act = 1;
	//判断玩家在哪一块板子上
	for (int i = 0; i < 10; i++)
	{
		int x2 = this->x + h / 2;
		int y2 = this->y + h;
		if (x2 >= board[i].x && x2 <= board[i].len + board[i].x
			&& y2 >= board[i].y - 10 && y2 <= board[i].y + 10)
		{
			this->y = board[i].y - h;
			ob = i;
			if (board->type == 1)
				health--;
			break;
		}
		else
			ob = -1;
	}
	if (ob = -1)
	{
		y += 5;
	}
	if (y == 0)
	{
		health--;
		Timer::timer(2000, 5);
	}
	if (y > 720)
		health = 0;
}
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
	//for (int i = 0; i < h; i++)
	//{
	//	for (int j = 0; j < w; j++)
	//	{
	//		des_[i * w + j] = src_[i * w + w - j];
	//	}
	//}
	return;
}


Character::Character(const char* name, int runsize)
{
	images = new Atlas(name, "run", ROLEW, ROLEH, runsize + 1, "_maks");
	rimages = new Atlas(runsize + 1);
	this->runsize = runsize;
	for (int i = 0; i < images->get_size(); i++)
	{
		filp(images->get_image(i), rimages->get_image(i));
	}
	for (int i = 0; i < images->get_size(); i++)
	{
		filp(images->get_mask_image(i), rimages->get_mask_image(i));
	}
	return;
}
void Character::exhibit(int direct)
{
	if (direct == RIGHT)
	{
		draw_lucency(x, y, images->get_image(curframe), images->get_mask_image(curframe));
		curframe = ((++curframe) %= runsize) == 0 ? 1 : curframe;
		//= 0->1
	}
	else
	{
		//draw_lucency(x, y, rimages->get_image(curframe), rimages->get_mask_image(curframe));
		for (int i = 0; i <= 4; i++)
		{
			draw_lucency(x, y, rimages->get_image(i), rimages->get_mask_image(i));
			i %= 4;
		}
		curframe = ((++curframe) %= runsize) == 0 ? 1 : curframe;

	}
}
