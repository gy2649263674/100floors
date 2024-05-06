#include <iostream>
#include <easyx.h>
#include <Windows.h>
#include "Timer.h"
#include "board.h"
#include "Character.h"
#define WIDTH 720
#define LENGTH 900
#define BOARD_GAP 150
using namespace std;

Board board[10];
IMAGE character_img[2];
IMAGE background;
IMAGE board_img[4];
Character role;

//游戏初始化
void gameInit()
{
	loadimage(board_img, "./picture/normal.png");
	loadimage(board_img+1, "./picture/nails.png");
	loadimage(character_img, "./picture/character 1/stand.png", 60, 60);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			board[i].y = rand() % (WIDTH / 3) + 100;
		}
		else
		{
			board[i].y = BOARD_GAP + board[i - 1].y;
		}
		board[i].x = rand() % (LENGTH-100);
		//board[i].y = rand() % (WIDTH);
		board[i].len = 100;
		board[i].exist = true;
		board[i].type = rand() % 3;
	}
	role.h = 60;
	role.x = board[0].x + board[0].len / 2 - role.h / 2;
	role.y = board[0].y - role.h;
	role.ob = -1;
}
//游戏绘制
void gamedraw()
{
	for (int i = 0; i < 10; i++)
	{
		//solidrectangle(board[i].x, board[i].y, board[i].x + board[i].len, board[i].y + 5);
		if (board[i].type == 0)
		{
			putimage(board[i].x, board[i].y, &board_img[0]);
		}
		else if (board[i].type == 1)
		{
			putimage(board[i].x, board[i].y, &board_img[1]);
		}
	}
	putimage(role.x, role.y, character_img);
}

void board_move()
{
	for (int i = 0; i < 10; i++)
	{
		board[i].y -= 1;
		if (board[i].y < 0)
		{
			board[i].y = 8 * BOARD_GAP;
			board[i].x = rand() % (LENGTH - 100);
			board[i].type = rand() % 3;
		}
	}
}

int main1()
{
	//创建图形窗口
	initgraph(LENGTH, WIDTH);
	gameInit();
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		gamedraw();
		if (Timer::timer(2, 1))
			role.character_move();
		if(Timer::timer(5,0))
			board_move();
		EndBatchDraw();
	}

	system("pause");
}