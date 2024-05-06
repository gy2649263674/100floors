#include "Character.h"
#include "board.h"
extern Board board[10];
void Character::character_move()
{
	int speed = 1;
	if (GetAsyncKeyState(VK_LEFT))
	{
		x -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		x += speed;
	}
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
	if (ob = -1)
	{
		y += 1;
	}
}