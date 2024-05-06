#include "Character.h"
#include "board.h"
#include "easyx.h"
#include "Draw.h"
#include "Timer.h"
#include <ctime>
extern Board board[10];
extern int act;
extern IMAGE character_img[10];
extern IMAGE character_img_mask[10];

void Character::character_move()
{
	
	int speed = 1;
	if (GetAsyncKeyState(VK_LEFT))
	{
		x -= speed;
		Draw::flipimage(x, y, character_img_mask[act], SRCAND);
		Draw::flipimage(x, y, character_img[act], SRCPAINT);
		act++;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		x += speed;
		putimage(x, y, &character_img_mask[act], SRCAND);
		putimage(x, y, &character_img[act], SRCPAINT);
		act++;
	}
	/*putimage(x, y, &character_img_mask[0], SRCAND);
	putimage(x, y, &character_img[0], SRCPAINT);*/
	if (act > 5)
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
			break;
		}
		else
			ob = -1;
	}
	if (ob = -1 )
	{
		y += 1;
	}
}