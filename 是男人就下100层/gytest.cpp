
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
#include<deque>
using namespace std;
const  int fps = 60;
const  int frame = 1000 / 60;
int Timer::time = 0;
bool EXIT = false;
IMAGE cursor[2];
IMAGE arrow[2];
IMAGE border[2];
Board roof;
deque<Board>board(150);
IMAGE background;
IMAGE health[2];
IMAGE roof_img[2];
IMAGE cure_img[2];
IMAGE gold_img[2];
IMAGE defend_img[2];
IMAGE armo_img[2];
IMAGE wall;
ExMessage msg = { 0 };
int act = 1;
Start se;
void loadapp();;
Character role;
deque<Picset*>appearence;
map<Boardtype, map<int, IMAGE>>boardimg;
map<Boardtype, map<int, IMAGE>>boardimg_mask;
void draw_speed(Character& role);

void creatgame()
{
	initgraph(MAINW, MAINH);
	cleardevice();
	HWND handle = GetHWnd();
	MoveWindow(HWND(handle), MAINX, MAINY, MAINW, MAINH, true);
}
#include <direct.h>
void loadresource()
{
	loadimage(&boardimg[normaltype][0], "./picture/unit/normal.png");
	loadimage(&boardimg[nailtype][0], "./picture/unit/nail.png");
	loadimage(&boardimg_mask[nailtype][0], "./picture/unit/nail_mask.png");
	loadimage(&boardimg[faketype][0], "./picture/unit/fake.png");
	loadimage(&boardimg_mask[faketype][0], "picture/unit/fake_mask.png");
	loadimage(&boardimg[lefttype][0], "./picture/unit/conveyor_left.png");
	loadimage(&boardimg[righttype][0], "./picture/unit/conveyor_right.png");
	for (int i = 1; i <= 6; i++)
	{
		string path("picture\\unit\\ori\\trampoline" + to_string(i) + ".png");
		char s[256];
		_getcwd(s, 100);
		cout << s;
		loadimage(&boardimg[trampolinetype][i], &path[0]);
		loadimage(&boardimg_mask[trampolinetype][i], &("./picture/unit/trampoline/mask/trampoline" + to_string(i) + ".png")[0]);
	}


	loadimage(&arrow[0], "picture/button/arrow.png");
	loadimage(&arrow[1], "picture/button/arrow_mask.png");
	loadimage(cursor, "picture/button/cursor.ico");
	loadimage(cursor + 1, "picture/button/cursor_mask.ico");
	loadimage(health, "./picture/health/health1.png", 40, 40);
	loadimage(health + 1, "./picture/health/health1_mask.png", 40, 40);
	loadimage(cure_img, "./picture/item/cure.png", 40, 40);
	loadimage(cure_img + 1, "./picture/item/cure_mask.png", 40, 40);
	loadimage(gold_img, "./picture/item/gold.png", 40, 40);
	loadimage(gold_img + 1, "./picture/item/gold_mask.png", 40, 40);
	loadimage(defend_img, "./picture/item/defend.png", 40, 40);
	loadimage(defend_img + 1, "./picture/item/defend_mask.png", 40, 40);
	loadimage(armo_img, "./picture/item/defend.png", 40, 40);
	loadimage(armo_img + 1, "./picture/item/defend_mask.png", 40, 40);
}

Boardtype wanttype(entertain mode = normal)
{//
	
	//根据当前模式控制板子概率 
	switch (mode)
	{
	case normal:
		return  normaltype;
	case jump_jump:
		return trampolinetype;
	case fake_world:
		return  faketype;
	case run_run:
	{
		srand(rand()*time(0));
		return rand() % 10 > rand() % 10 ? lefttype : righttype;
	}
	}
}
#define PERCENT 7
int setboard(entertain mode = normal)
{
	static int judge = 0;
	judge = rand() % 10;
	int btype = rand() % 6;
	if (judge < 7 && btype!= wanttype(mode))
	{
		return wanttype(mode);
	}
	else
	{
		return btype;
	}
}
void gameInit(entertain mode = normal)
{
	loadresource();
	loadapp();
	srand((unsigned int)time(NULL));
	board[0].y = rand() % (WIDTH / 3) + 100;
	board[0].x = MAINW/ 2;
	board[0].type = 0;
	//srand(time(0));
	for (int i = 1; i < 150; i++)
	{
		board[i].y = BOARD_GAP+ board[i - 1].y;
		board[i].type = setboard(mode);
		board[i].x = rand() % (LENGTH - 350);
	}
	role.set_sta(board[0]);
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
	return;
}

void gamedraw(int& count, int dir)
{
	++count;
	draw_lucency(0, 0, roof_img, roof_img + 1);
	draw_lucency(350, 0, roof_img, roof_img + 1);
	//draw_lucency(800, 0, roof_img, roof_img + 1);
	putimage(0, 0, &wall);
	putimage(0, 380, &wall);
	putimage(750, 0, &wall);
	putimage(750, 380, &wall);
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
	for (i = 0; i < 150&&board[i].y>=0&&board[i].y<=MAINH; i++)
	{

		if (board[i].type == 0)
		{
			putimage(board[i].x, board[i].y, &boardimg[normaltype][0]);
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
		else if (board[i].type == nailtype)
		{
			putimage(board[i].x, board[i].y, &boardimg_mask[nailtype][0], SRCAND);
			putimage(board[i].x, board[i].y, &boardimg[nailtype][0], SRCPAINT);
		}
		else if (board[i].type == faketype)
		{
			putimage(board[i].x, board[i].y, 96, 217 / 6, &boardimg_mask[faketype][0], 0, 0, SRCAND);
			putimage(board[i].x, board[i].y, 96, 217 / 6, &boardimg[faketype][0], 0, 0, SRCPAINT);
			//putimage(board[i].x, board[i].y, 96, 217 / 6, fake, 0, 0, SRCPAINT);
		}
		else if (board[i].type == lefttype)
		{
			putimage(board[i].x, board[i].y, 96, 16, &boardimg[lefttype][0], 0, 0);
		}
		else if (board[i].type == righttype)
		{
			putimage(board[i].x, board[i].y, 96, 16, &boardimg[righttype][0], 0, 0);
		}
		else if (board[i].type == trampolinetype)
		{
			putimage(board[i].x, board[i].y, &boardimg_mask[trampolinetype][board[i].stay + 1],SRCAND);
			putimage(board[i].x, board[i].y, &boardimg[trampolinetype][board[i].stay + 1],SRCPAINT);
			//
			// draw_lucency(board[i].x, board[i].y, &boardimg[trampolinetype][board[i].stay + 1], &boardimg_mask[trampolinetype][board[i].stay + 1]);
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
	draw_speed(role);
}
#define BOARD_A 0.001
#define MAXV 10
const double v0 = 3;
double Board::V = 3;
#define BOARDSIZE 20
#define BOARDBUFFER 30
extern string getv[10];
#define STAX 300
void draw_speed(Character& role)
{
	settextstyle(20, 10, "consola");
	outtextxy(MAINW- STAX, 0, &("board v:" + to_string(Board::V))[0]);
	outtextxy(MAINW- STAX, 30, &getv[0][0]);
	outtextxy(MAINW- STAX, 60, &getv[1][0]);
	outtextxy(MAINW- STAX, 90, &getv[2][0]);
}

void board_move(bool rebegin, entertain mode = normal)
{
	Board::V = min(rebegin ? v0 : (Board::V += BOARD_A), MAXV);
	cout << "board v:" << Board::V << endl;
	for (int i = 0; i < 150; i++)
	{
		board[i].y -= Board::V;
		if (board[i].y < 0)
		{
			board.push_back(board.front());
			board.pop_front();
			board.back().y = board[board.size() - 2].y + (rand() % 50) + 30;
			board.back().x = rand() % (LENGTH - 350);
			board.back().type = setboard(mode);///rand() % 6;
			board.back().used = false;
			board.back().stay = 0;
		}
	}
}

void tempgameing(entertain mode = normal)
{

	int count = 0;
	settextcolor(WHITE);
	settextstyle(50, 15, "consola");;
	setfillcolor(BLACK);
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, se.get_background());
		board_move(false,mode);
		gamedraw(count, role.character_move());
		outtextxy(0, 0, "开发者模式");
		Timer::endkeep(1000 / 144);
		EndBatchDraw();
	}
}
Picset fox;
Picset ch;
Picset kun;
void loadapp()
{
	ch = *new Picset("ch", 36, 26, 10);
	fox = *new Picset("fox", 8, 7, 1);
	kun = *new Picset("kun", 25, 3, 21, 40,60);
	appearence.push_back(&ch);
	appearence.push_back(&fox);
	appearence.push_back(&kun);
}
void testbutton()
{
	se = Start();
	creatgame();
	gameInit(jump_jump);
	role = Character("kun",3, 21, &kun);
	while (1 ^ EXIT)
	{
		se.enter_scene();
		while (peekmessage(&msg, EX_KEY | EX_MOUSE) | 1)
		{
			Btname opt;
			opt = Btname(se.process_command(msg));
			if (opt == start_bt)
			{
				cout << "start game" << endl;
				tempgameing(jump_jump);
			}
			else if (opt == map_bt)
			{
				se.ChooseMap(msg);
				cout << "choose map" << endl;
				se.enter_scene();
			}
			else if (opt == role_bt)
			{
				se.change_role(&role, appearence);
				cout << "choose role" << endl;
				se.enter_scene();
			}
			else if (opt == exit_bt)
			{
				EXIT = true;
				cout << "exit game" << endl;
			}
			else if (opt == choosemode_bt)
			{

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

