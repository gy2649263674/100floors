
#include <iostream>
#include <easyx.h>
#include <ctime>
#include <Windows.h>
#include"board.h"
#include"all.h"
#include "Timer.h"
#include "Anime.h"
#include "Character.h"
#include "Draw.h"
#include"scene.h"
#include "Item.h"
Character role;
using namespace std;
const  int fps = 60;
const  int frame = 1000 / 60;
int Timer::time = 0;
bool EXIT = false;
IMAGE cursor[2];
IMAGE arrow[2];
IMAGE border[2];
Board roof;
Board board[150];
IMAGE background;
IMAGE board_img[4];
IMAGE conveyor_right;
IMAGE conveyor_left;
IMAGE fake[2];
IMAGE health[2];
IMAGE roof_img[2];
IMAGE trampoline_img[2];
IMAGE cure_img[2];
IMAGE gold_img[2];
IMAGE defend_img[2];
IMAGE armo_img[2];
ExMessage msg = { 0 };
int act = 1;
Start se;
void creatgame()
{
	initgraph(MAINW, MAINH);
	cleardevice();
	HWND handle = GetHWnd();
	MoveWindow(HWND(handle), MAINX, MAINY, MAINW, MAINH, true);
}
void loadboard()
{

}

void loadresource()
{
	loadimage(&conveyor_left, "./picture/conveyor_left.png");
	loadimage(&conveyor_right, "./picture/conveyor_right.png");
	loadimage(fake, "./picture/fake.png");
	loadimage(fake + 1, "picture/fake_mask.png");
	loadimage(border, "picture/button/border.png", Button::wordsw, Button::h);
	loadimage(border + 1, "picture/button/border_mask.png", Button::wordsw, Button::h);
	loadimage(roof_img, "./picture/ceiling.png");
	loadimage(roof_img + 1, "./picture/ceiling_mask.png");
	loadimage(board_img, "./picture/unit/normal.png");
	loadimage(board_img + 1, "./picture/unit/nails.png");
	loadimage(board_img + 2, "picture/nails_mask.png");
	loadimage(&arrow[0], "picture/button/arrow.png");
	loadimage(&arrow[1], "picture/button/arrow_mask.png");
	loadimage(cursor, "picture/button/cursor.ico");
	loadimage(cursor + 1, "picture/button/cursor_mask.ico");
	loadimage(health, "./picture/health/health1.png", 40, 40);
	loadimage(health + 1, "./picture/health/health1_mask.png", 40, 40);
}
void gameInit()
{
	loadresource();
	loadimage(trampoline_img, "./picture/trampoline.png");
	loadimage(trampoline_img + 1, "./picture/trampoline_mask.png");
	loadimage(cure_img, "./picture/item/cure.png", 40, 40);
	loadimage(cure_img + 1, "./picture/item/cure_mask.png", 40, 40);
	loadimage(gold_img, "./picture/item/gold.png", 40, 40);
	loadimage(gold_img + 1, "./picture/item/gold_mask.png", 40, 40);
	loadimage(defend_img, "./picture/item/defend.png", 40, 40);
	loadimage(defend_img + 1, "./picture/item/defend_mask.png", 40, 40);
	loadimage(armo_img, "./picture/item/defend.png", 40, 40);
	loadimage(armo_img + 1, "./picture/item/defend_mask.png", 40, 40);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 150; i++)
	{
		if (i == 0)
		{
			board[i].y = rand() % (WIDTH / 3) + 100;
			board[i].type = 0;
		}
		else
		{
			board[i].y = BOARD_GAP + board[i - 1].y;
			int judge = rand() % 10;
			int btype = rand() % 6;
			if (judge > 7 && btype != 0)
			{
				board[i].type = 0;
			}
			else
			{
				board[i].type = btype;
			}
		}
		board[i].x = rand() % (LENGTH - 350);
		board[i].len = 100;
		board[i].exist = true;
		board[i].used = false;
		board[i].stay = 0;
	}
	role.h = 60;
	role.have_armo = false;
	role.jump = 100;
	role.x = board[0].x + board[0].len / 2 - role.h / 2;
	role.y = board[0].y - role.h;
	role.set_sta();
	role.health = 3;
	role.ob = -1;
	roof.type = 1;
	roof.len = LENGTH;
	roof.used = false;
	roof.x = 0;
	roof.y = 0;
}


void draw_lucency(Character& role, int direct = RIGHT)
{
	auto it = direct == RIGHT ? role.images : role.rimages;
	draw_lucency(role.x, role.y, it->get_image(role.curframe), it->get_mask_image(role.curframe));
	//if (role.curframe)
		//cout << "now direct:" << (direct == LEFT ? "left" : "right") << role.curframe << endl;
	return;
}

void gamedraw(int& count, int dir)
{
	++count;
	draw_lucency(0, 0, roof_img, roof_img + 1);
	draw_lucency(400, 0, roof_img, roof_img + 1);
	draw_lucency(800, 0, roof_img, roof_img + 1);
	if (count >= 5)
	{
		count = 0;
		int index;
		int index2 = Item::creatitem(index);
		if (board[index].have_item == false)
		{
			board[index].have_item = true;
			board[index].item_type = index2;
		}
	}
	int i = 0;
	for (i = 0; i < role.health; i++)
	{
		putimage(600 + i * 40, 10, &health[1], SRCAND);
		putimage(600 + i * 40, 10, &health[0], SRCPAINT);
	}
	if (role.have_armo == true)
	{
		putimage(600 + i * 40, 10, &armo_img[1], SRCAND);
		putimage(600 + i * 40, 10, &armo_img[0], SRCPAINT);
	}
	for (i = 0; i < 150; i++)
	{
		if (board[i].type == 0)
		{
			putimage(board[i].x, board[i].y, &board_img[0]);
			if (board[i].have_item == true)
			{
				if (board[i].item_type == 0)
				{
					putimage(board[i].x + 4, board[i].y - 20, cure_img + 1, SRCAND);
					putimage(board[i].x + 4, board[i].y - 20, cure_img, SRCPAINT);
				}
				else if (board[i].item_type == 1)
				{
					putimage(board[i].x + 4, board[i].y - 20, defend_img + 1, SRCAND);
					putimage(board[i].x + 4, board[i].y - 20, defend_img, SRCPAINT);
				}
				else if (board[i].item_type == 2)
				{
					putimage(board[i].x + 4, board[i].y - 20, gold_img + 1, SRCAND);
					putimage(board[i].x + 4, board[i].y - 20, gold_img, SRCPAINT);
				}
			}
		}
		else if (board[i].type == 1)
		{
			putimage(board[i].x, board[i].y, &board_img[2], SRCAND);
			putimage(board[i].x, board[i].y, &board_img[1], SRCPAINT);
		}
		else if (board[i].type == 2)
		{
			putimage(board[i].x, board[i].y, 96, 217 / 6, fake + 1, 0, 0, SRCAND);
			putimage(board[i].x, board[i].y, 96, 217 / 6, fake, 0, 0, SRCPAINT);
		}
		else if (board[i].type == 3)
		{
			putimage(board[i].x, board[i].y, 96, 16, &conveyor_left, 0, 0);
			//Anime::anime_conveyor_left(i);
		}
		else if (board[i].type == 4)
		{
			putimage(board[i].x, board[i].y, 96, 16, &conveyor_right, 0, 0);
			//Anime::anime_conveyor_right(i);
		}
		else if (board[i].type == 5)
		{
			putimage(board[i].x, board[i].y, 97, 132 / 6, trampoline_img + 1, 0, 0, SRCAND);
			putimage(board[i].x, board[i].y, 97, 132 / 6, trampoline_img, 0, 0, SRCPAINT);
		}
	}
	if (dir == LEFT)
	{
		draw_lucency(role, LEFT);
	}
	else if (dir == RIGHT)// (msg.vkcode == VK_RIGHT)
	{
		draw_lucency(role, RIGHT);
	}
	else if (dir == 0)
	{
		role.draw_standing();
	}
	//falling
	else if (dir == 2)
	{

	}
	//peekmessage(&msg, -1);
}

void board_move()
{

	for (int i = 0; i < 150; i++)
	{
		board[i].y -= 3;
		if (board[i].y < 0)
		{
			board[i].y = 150 * BOARD_GAP;
			board[i].x = rand() % (LENGTH - 350);
			board[i].type = rand() % 6;
			board[i].used = false;
			board[i].stay = 0;
		}
	}
}
void tempgameing()
{

	int count = 0;
	settextcolor(WHITE);
	setfillcolor(BLACK);
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, se.get_background());
		board_move();
		gamedraw(count, role.character_move());
		outtextxy(0, 0, "开发者模式");
		Timer::endkeep(1000 / 144);
		EndBatchDraw();

	}
}


void testbutton()
{
	se = Start();
	creatgame();
	gameInit();
	//se.enter_scene();
	role = Character("ch", 36, 9);
	//role = Character("fox", 8,1);
	tempgameing();
	while (1 ^ EXIT)
	{
		while (peekmessage(&msg, EX_KEY | EX_MOUSE))
		{
			StartOpt opt;
			opt = StartOpt(se.process_command(msg));
			if (opt == startgame)
			{
				cout << "start game" << endl;
				tempgameing();
			}
			else if (opt == choose_map)
			{
				se.ChooseMap(msg);
				cout << "choose map" << endl;
			}
			else if (opt == choose_role)
			{
				cout << "choose role" << endl;
			}
			else if (opt == exit_game)
			{
				EXIT = true;
				cout << "exit game" << endl;
			}
		}
	}
	return;
}
int main(void)
{

	//testbutton();
	testbutton();
	return 0;

}

