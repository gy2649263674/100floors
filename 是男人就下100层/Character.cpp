#include "Character.h"
#include "board.h"
#include "easyx.h"
#include "Draw.h"
#include "Timer.h"
#include "Anime.h"
#include <ctime>
extern Board board[150];
extern int act;
extern IMAGE character_img[10];
extern IMAGE character_img_mask[10];
extern ExMessage msg;
void Character::character_move()
{
	
	int speed = 8;
	if (GetAsyncKeyState(VK_LEFT)&&x>0)
	{
		x -= speed;
		msg.vkcode == VK_LEFT;
		/*Draw::flipimage(x, y, character_img_mask[act], SRCAND);
		Draw::flipimage(x, y, character_img[act], SRCPAINT);*/
		act++;
	}
	if (GetAsyncKeyState(VK_RIGHT)&&x<900)
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
	for (int i = 0; i < 150; i++)
	{
		int x2 = this->x + h / 2;
		int y2 = this->y + h;
		if (x2 >= board[i].x && x2 <= board[i].len + board[i].x
			&& y2 >= board[i].y - 10 && y2 <= board[i].y + 10)
		{
			this->y = board[i].y - h;
			ob = i;
			if (board[i].type == 1)
			{
				health--;
				break;
			}
			else if (board[i].type == 2)
			{
				y += 3;
				//Anime::anime_fake(i);
				break;
			}
			else if (board[i].type == 3)
			{
				if (x > 0)
					x -= speed/4;
				break;
			}
			else if (board[i].type == 4)
			{
				if (x < 900)
					x += speed/4;
				break;
			}
			break;
		}
		else
			ob = -1;
	}
	if (ob = -1 )
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