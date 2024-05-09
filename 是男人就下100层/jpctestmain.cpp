//
//#include <iostream>
//#include <easyx.h>
//#include <ctime>
//#include <Windows.h>
//#include "Timer.h"
//#include "Anime.h"
//#include "board.h"
//#include "Character.h"
//#include "Draw.h"
//#include"scene.h"
//#include<system.h>
//IMAGE cursor[2];
//IMAGE arrow[2];
//bool EXIT = false;
//Atlas back;
//IMAGE border[2];
//
//
//using namespace std;
//Board board[10];
//IMAGE character_img[10];
//IMAGE character_img_mask[10];
//IMAGE character_img_l[10];
//IMAGE character_img_l_mask[10];
//IMAGE background;
//IMAGE board_img[4];
//IMAGE conveyor_right;
//IMAGE conveyor_left;
//IMAGE fake;
//Character role;
//ExMessage msg = { 0 };
//int act = 1;
//
////putimage(100, 100, yuan.get_mask_image(0));
//void creatgame()
//{
//	initgraph(MAINW, MAINH);
//	initgraph(LENGTH,WIDTH);
//	cleardevice();
//	HWND handle = GetHWnd();
//	MoveWindow(HWND(handle), MAINX, MAINY, MAINW, MAINH, true);
//}
//void gameInit()
//{
//	loadimage(board_img, "./picture/unit/normal.png");
//	loadimage(board_img + 1, "./picture/unit/nails.png");
//	loadimage(character_img, "./picture/character 1/stand.png", 60, 60);
//	loadimage(character_img + 1, "./picture/character 1/run1.png", 60, 60);
//	loadimage(character_img + 2, "./picture/character 1/run2.png", 60, 60);
//	loadimage(character_img + 3, "./picture/character 1/run3.png", 60, 60);
//	loadimage(character_img + 4, "./picture/character 1/run4.png", 60, 60);
//	loadimage(character_img + 5, "./picture/character 1/falling.png", 60, 60);
//	loadimage(character_img_mask, "./picture/character 1/stand_mask.png", 60, 60);
//	loadimage(character_img_mask + 1, "./picture/character 1/run1_mask.png", 60, 60);
//	loadimage(character_img_mask + 2, "./picture/character 1/run2_mask.png", 60, 60);
//	loadimage(character_img_mask + 3, "./picture/character 1/run3_mask.png", 60, 60);
//	loadimage(character_img_mask + 4, "./picture/character 1/run4_mask.png", 60, 60);
//	loadimage(character_img_mask + 5, "./picture/character 1/falling_mask.png", 60, 60);
//	loadimage(character_img_l, "./picture/character 1/stand.png", 60, 60);
//	loadimage(character_img_l + 1, "./picture/character 1/run1_l.png", 60, 60);
//	loadimage(character_img_l + 2, "./picture/character 1/run2_l.png", 60, 60);
//	loadimage(character_img_l + 3, "./picture/character 1/run3_l.png", 60, 60);
//	loadimage(character_img_l + 4, "./picture/character 1/run4_l.png", 60, 60);
//	loadimage(character_img_l + 5, "./picture/character 1/falling.png", 60, 60);
//	loadimage(character_img_l_mask, "./picture/character 1/stand_mask.png", 60, 60);
//	loadimage(character_img_l_mask + 1, "./picture/character 1/run1_l_mask.png", 60, 60);
//	loadimage(character_img_l_mask + 2, "./picture/character 1/run2_l_mask.png", 60, 60);
//	loadimage(character_img_l_mask + 3, "./picture/character 1/run3_l_mask.png", 60, 60);
//	loadimage(character_img_l_mask + 4, "./picture/character 1/run4_l_mask.png", 60, 60);
//	loadimage(character_img_l_mask + 5, "./picture/character 1/falling_mask.png", 60, 60);
//	srand((unsigned int)time(NULL));
//
//	for (int i = 0; i < 10; i++)
//	{
//		if (i == 0)
//		{
//			board[i].y = rand() % (WIDTH / 3) + 100;
//		}
//		else
//		{
//			board[i].y = BOARD_GAP + board[i - 1].y;
//		}
//		board[i].x = rand() % (LENGTH - 150);
//		//board[i].y = rand() % (WIDTH);
//		board[i].len = 100;
//		board[i].exist = true;
//		board[i].type = rand() % 5;
//	}
//	role.h = 60;
//	role.x = board[0].x + board[0].len / 2 - role.h / 2;
//	role.y = board[0].y - role.h;
//	role.health = 5;
//	role.ob = -1;
//}
////锟斤拷戏锟斤拷锟斤拷
////锟斤拷锟斤拷0为锟斤拷通锟斤拷1为锟斤拷锟?2为锟劫板，3为锟斤拷锟酵ｏ拷4为锟揭达拷锟斤拷
//void gamedraw()
//{
//	for (int i = 0; i < 10; i++)
//	{
//		if (board[i].type == 0)
//		{
//			putimage(board[i].x, board[i].y, &board_img[0]);
//		}
//		else if (board[i].type == 1)
//		{
//			putimage(board[i].x, board[i].y, &board_img[1]);
//		}
//	}
//	if (msg.vkcode == VK_LEFT)
//	{
//		putimage(role.x, role.y, &character_img_l_mask[act / 4], SRCAND);
//		putimage(role.x, role.y, &character_img_l[act / 4], SRCPAINT);
//	}
//	else if (msg.vkcode == VK_RIGHT)
//	{
//		putimage(role.x, role.y, &character_img_mask[act / 4], SRCAND);
//		putimage(role.x, role.y, &character_img[act / 4], SRCPAINT);
//	}
//	else
//	{
//		putimage(role.x, role.y, &character_img_mask[0], SRCAND);
//		putimage(role.x, role.y, &character_img[0], SRCPAINT);
//	}
//	msg.message = 0;
//}
//
//void board_move()
//{
//
//	for (int i = 0; i < 10; i++)
//	{
//		board[i].y -= 1;
//		if (board[i].y < 0)
//		{
//			board[i].y = 8 * BOARD_GAP;
//			board[i].x = rand() % (LENGTH - 150);
//			board[i].type = rand() % 3;
//		}
//	}
//}
//int main()
//{
//	//锟斤拷锟斤拷图锟轿达拷锟斤拷
//	creatgame();
//	initgraph(LENGTH, WIDTH);
//	gameInit();
//	while (1)
//	{
//		BeginBatchDraw();
//		cleardevice();
//		gamedraw();
//		if (Timer::timer(20, 1))
//			role.character_move();
//		if (Timer::timer(5, 0))
//			board_move();
//		EndBatchDraw();
//	}
//
//
//	system("pause");
//}
//
//
//
//
//
