#include <iostream>
#include <easyx.h>
#include <ctime>
#include <Windows.h>
#include "Timer.h"
#include "board.h"
#include "Character.h"
#include "Draw.h"
#define WIDTH 720
#define LENGTH 900
#define BOARD_GAP 150
using namespace std;
const clock_t FPS = 1000 / 60;
int starttime = 0;
int freamtime = 0;
Board board[10];
IMAGE character_img[10];
IMAGE character_img_mask[10];
IMAGE character_img_l[10];
IMAGE character_img_l_mask[10];
IMAGE background;
IMAGE board_img[4];
Character role;
ExMessage msg = { 0 };
int act = 1;
//游戏初始化
void gameInit()
{
	loadimage(board_img, "./picture/normal.png");
	loadimage(board_img+1, "./picture/nails.png");
	loadimage(character_img, "./picture/character 1/stand.png", 60, 60);
	loadimage(character_img+1, "./picture/character 1/run1.png", 60, 60);
	loadimage(character_img+2, "./picture/character 1/run2.png", 60, 60);
	loadimage(character_img+3, "./picture/character 1/run3.png", 60, 60);
	loadimage(character_img+4, "./picture/character 1/run4.png", 60, 60);
	loadimage(character_img+5, "./picture/character 1/falling.png", 60, 60);
	loadimage(character_img_mask, "./picture/character 1/stand_mask.png", 60, 60);
	loadimage(character_img_mask + 1, "./picture/character 1/run1_mask.png", 60, 60);
	loadimage(character_img_mask + 2, "./picture/character 1/run2_mask.png", 60, 60);
	loadimage(character_img_mask + 3, "./picture/character 1/run3_mask.png", 60, 60);
	loadimage(character_img_mask + 4, "./picture/character 1/run4_mask.png", 60, 60);
	loadimage(character_img_mask + 5, "./picture/character 1/falling_mask.png", 60, 60);
	loadimage(character_img_l, "./picture/character 1/stand.png", 60, 60);
	loadimage(character_img_l + 1, "./picture/character 1/run1_l.png", 60, 60);
	loadimage(character_img_l + 2, "./picture/character 1/run2_l.png", 60, 60);
	loadimage(character_img_l + 3, "./picture/character 1/run3_l.png", 60, 60);
	loadimage(character_img_l + 4, "./picture/character 1/run4_l.png", 60, 60);
	loadimage(character_img_l + 5, "./picture/character 1/falling.png", 60, 60);
	loadimage(character_img_l_mask, "./picture/character 1/stand_mask.png", 60, 60);
	loadimage(character_img_l_mask + 1, "./picture/character 1/run1_l_mask.png", 60, 60);
	loadimage(character_img_l_mask + 2, "./picture/character 1/run2_l_mask.png", 60, 60);
	loadimage(character_img_l_mask + 3, "./picture/character 1/run3_l_mask.png", 60, 60);
	loadimage(character_img_l_mask + 4, "./picture/character 1/run4_l_mask.png", 60, 60);
	loadimage(character_img_l_mask + 5, "./picture/character 1/falling_mask.png", 60, 60);
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
		board[i].x = rand() % (LENGTH-150);
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
		if (board[i].type == 0)
		{
			putimage(board[i].x, board[i].y, &board_img[0]);
		}
		else if (board[i].type == 1)
		{
			putimage(board[i].x, board[i].y, &board_img[1]);
		}
	}
	if (msg.vkcode == VK_LEFT)
	{
		putimage(role.x, role.y, &character_img_l_mask[act/4], SRCAND);
		putimage(role.x, role.y, &character_img_l[act/4], SRCPAINT);
	}
	else if (msg.vkcode == VK_RIGHT)
	{
		putimage(role.x, role.y, &character_img_mask[act/4], SRCAND);
		putimage(role.x, role.y, &character_img[act/4], SRCPAINT);
	}
	else
	{
		/*putimage(role.x, role.y, &character_img_l_mask[act / 4], SRCAND);
		putimage(role.x, role.y, &character_img_l[act / 4], SRCPAINT);*/
		putimage(role.x, role.y, &character_img_mask[0], SRCAND);
		putimage(role.x, role.y, &character_img[0], SRCPAINT);
	}
	msg.message = 0;
}

void board_move()
{
	
	for (int i = 0; i < 10; i++)
	{
		board[i].y -= 1;
		if (board[i].y < 0)
		{
			board[i].y = 8 * BOARD_GAP;
			board[i].x = rand() % (LENGTH - 150);
			board[i].type = rand() % 3;
		}
	}
}

int main()
{

	//创建图形窗口
	initgraph(LENGTH, WIDTH);
	gameInit();
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		gamedraw();
		if (Timer::timer(20, 1))
			role.character_move();
		if(Timer::timer(5,0))
			board_move();
		EndBatchDraw();
	}
	










	system("pause");
}