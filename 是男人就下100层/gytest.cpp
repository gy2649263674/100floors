
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
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
bool GODMODE = false;
using namespace std;
const double v0 = 4;
const  int fps = 60;
const  int frame = 1000 / 60;
int Timer::time = 0;
bool EXIT = false;
IMAGE cursor[2];
IMAGE arrow[2];
IMAGE border[2];
IMAGE roof_img[2];
Board roof;
deque<Board>board(150);
IMAGE background;
IMAGE health[2];
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
enum {
	goback,
	restart,
	continuebt,
}Overallbt;
void gamedraw(int dir);
class Moniter
{
public:
	void init()
	{
		overall[goback].init("goback", "返回主菜单");
		overall[restart].init("restart", "游戏可以重开，人生不能重来");
		overall[continuebt].init("suspend", "继续");
		overall[goback].setpos(MAINW / 2, MAINH / 2);
		overall[continuebt].setpos(MAINW / 2, MAINH / 2 + BTH * 3);
		overall[restart].setpos(MAINW / 2, MAINH / 2);
	}
	int gaming(ExMessage msg = { 0 })
	{
		//setbkcolor(WHITE);
		setbkmode(OPAQUE);
		settextstyle(80, 10, "");
		settextcolor(WHITE);
		outtextxy(800, 0, "");
		//setfillcolor(WHITE);
		outtextxy(800, 500, "按空格键暂停");
		if (GetAsyncKeyState(VK_SPACE) == 0)
		{
			return 0;
		}
		peekmessage(&msg, EX_KEY, true);
		while (1)
		{
			BeginBatchDraw();
			gamedraw(0);
			settextstyle(60, 10, "");
			outtextxy(550, MAINH - 100, "按enter键返回游戏");
			outtextxy(550, MAINH - 200, "按esc键返回主菜单");
			EndBatchDraw();
			while (peekmessage(&msg, EX_MOUSE | EX_KEY) | 1)
			{
				if (msg.vkcode == VK_RETURN)
				{
					return 0;
				}
				else if (msg.vkcode == VK_ESCAPE)
				{
					return -1;
				}
			}
		}
	}
	int died_restart()
	{
		Sleep(100);
		EndBatchDraw();
		cleardevice();
		putimage(0, 0, se.get_background());
		setfillcolor(BLACK);
		settextcolor(RED);
		settextstyle(50, 10, "");
		outtextxy(MAINW / 2, MAINH / 2, "骚年,游戏可以重开，人生不能重来");
		outtextxy(MAINW / 2, MAINH / 2 + 50, "摁ESC退出");
		outtextxy(MAINW / 2, MAINH / 2 + 100, "按ENTER重开");
		ExMessage msg;
		while (1)
		{
			peekmessage(&msg, -1);
			if (msg.vkcode == VK_ESCAPE)//F
			{
				return 0;
			}
			else if (msg.vkcode == VK_RETURN)
			{
				return 1;
			}
		}

		//outtextxy(MAINW / 2, MAINH / 2, "游戏可以重开，人生不能重来");
	}
	Button overall[3];
};
Moniter master;
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
	loadapp();
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
	loadimage(&wall, "./picture/unit/wall.png");
	loadimage(roof_img, "./picture/ceiling/ceiling.png");
	loadimage(roof_img + 1, "./picture/ceiling/ceiling_mask.png");
	loadimage(&arrow[0], "picture/button/arrow.png");
	loadimage(&arrow[1], "picture/button/arrow_mask.png");
	loadimage(cursor, "picture/button/cursor.ico");
	loadimage(cursor + 1, "picture/button/cursor_mask.ico");
	loadimage(border + 1, "picture/button/border_mask.png", Button::wordsw, BTH);
	loadimage(border, "picture/button/border.png", Button::wordsw, BTH);
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

Boardtype wanttype(const entertain mode = normal)
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
		srand(rand() * time(0));
		return rand() % 10 > rand() % 10 ? lefttype : righttype;
	}
	}
}
#define PERCENT 7
int setboard(const entertain mode = normal)
{
	static int judge = 0;
	judge = rand() % 10;
	int btype = rand() % 6;
	if (judge < 7 && btype != wanttype(mode))
	{
		return wanttype(mode);
	}
	else
	{
		return btype;
	}
}

void gameInit(const entertain mode = normal)
{
	Board::reset();
	role.score = 0;
	srand((unsigned int)time(NULL));
	board[0].y = rand() % (WIDTH / 3) + 100;
	board[0].x = MAINW / 2;
	board[0].type = 0;
	//srand(time(0));
	for (int i = 1; i < 150; i++)
	{
		board[i].y = BOARD_GAP + board[i - 1].y;
		board[i].stay = 0;
		board[i].type = setboard(mode);
		board[i].x = rand() % (LENGTH - 350);
		board[i].play = 0;
	}
	role.set_sta(board[4]);
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

void gamedraw(int dir = 0)
{
	static int count = 0;
	++count;
	draw_lucency(0, 0, roof_img, roof_img + 1);
	draw_lucency(350, 0, roof_img, roof_img + 1);
	fillrectangle(750, 0, 1000, 1000);
	setfillcolor(BLACK);
	putimage(0, 0, &wall);
	putimage(0, 380, &wall);
	putimage(750, 0, &wall);
	putimage(750, 380, &wall);
	if (count >= 100)
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
		putimage(780 + i * 40, 10, &health[1], SRCAND);
		putimage(780 + i * 40, 10, &health[0], SRCPAINT);
	}
	if (role.have_armo == true)
	{
		putimage(780 + i * 40, 10, &armo_img[1], SRCAND);
		putimage(780 + i * 40, 10, &armo_img[0], SRCPAINT);
	}
	for (i = 0; i < 150 && board[i].y >= 0 && board[i].y <= MAINH; i++)
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
			if (board[i].play > 18)
			{
				putimage(board[i].x, board[i].y, 96, 217 / 6, &boardimg_mask[faketype][0], 0, 0, SRCAND);
				putimage(board[i].x, board[i].y, 96, 217 / 6, &boardimg[faketype][0], 0, 0, SRCPAINT);
			}
			else {
				putimage(board[i].x, board[i].y, 96, 217 / 6, &boardimg_mask[faketype][0], 0, (board[i].play / 3) * 217 / 6, SRCAND);
				putimage(board[i].x, board[i].y, 96, 217 / 6, &boardimg[faketype][0], 0, (board[i].play / 3) * 217 / 6, SRCPAINT);
				if (board[i].play == 12)
				{
					board[i].play++;
				}
			}
			//putimage(board[i].x, board[i].y, 96, 217 / 6, fake, 0, 0, SRCPAINT);
		}
		else if (board[i].type == lefttype)
		{
			putimage(board[i].x, board[i].y, 96, 16, &boardimg[lefttype][0], 0, (board[i].play % 16 / 4) * 16);
		}
		else if (board[i].type == righttype)
		{
			putimage(board[i].x, board[i].y, 96, 16, &boardimg[righttype][0], 0, (board[i].play % 16 / 4) * 16);
		}
		else if (board[i].type == trampolinetype)
		{
			putimage(board[i].x, board[i].y, &boardimg_mask[trampolinetype][board[i].stay + 1], SRCAND);
			putimage(board[i].x, board[i].y, &boardimg[trampolinetype][board[i].stay + 1], SRCPAINT);
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
	//draw_speed(role);
	role.draw_score();
}
#define BOARD_A 0.005
#define MAXV 10
double Board::V = 3;
#define BOARDSIZE 20
#define BOARDBUFFER 30
extern string getv[10];
#define STAX 300
void draw_speed(Character& role)
{
	settextstyle(20, 10, "consola");
	outtextxy(MAINW - STAX, 0, &("board v:" + to_string(Board::V))[0]);
	outtextxy(MAINW - STAX, 30, &getv[0][0]);
	outtextxy(MAINW - STAX, 60, &getv[1][0]);
	outtextxy(MAINW - STAX, 90, &getv[2][0]);
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
			board[i].play = 0;
		}
	}
}
//1 restart
int tempgameing(entertain mode = normal)
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
		board_move(false, mode);
		gamedraw(role.character_move());
		if (master.gaming(msg) == -1)
		{
			EndBatchDraw();
			while (peekmessage(&msg, -1))
				(flushmessage());
			return 2;
		}
		if (role.is_dead() && !GODMODE)
		{
			while (peekmessage(&msg, -1))
				(flushmessage());
			if (master.died_restart())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (GODMODE)
		{
			outtextxy(0, 0, "god模式");
		}
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
	kun = *new Picset("kun", 25, 4, 21, 40, 60);
	appearence.push_back(&ch);
	appearence.push_back(&fox);
	appearence.push_back(&kun);
}
void testbutton(entertain defaultmode = normal)
{
	se = Start();
	creatgame();
	loadresource();
	gameInit(fake_world);
	role = Character("kun", 4, 21, &kun);
	//tempgameing(defaultmode);
	while (1 ^ EXIT)
	{
		se.enter_scene();
		while (peekmessage(&msg, EX_KEY | EX_MOUSE) | 1)
		{
			Btname opt;
			opt = Btname(se.process_command(msg));
			if (opt == start_bt)
			{
				while (1)
				{
					gameInit(defaultmode);
					cout << "start game" << endl;//1 restart
					//0 exut
					//2 mainmenu
					while (peekmessage(&msg, EX_KEY))
						(flushmessage());
					int op = tempgameing(defaultmode);

					if (op == 1)
					{
						continue;
					}
					else if (op == 2)
					{
						se.enter_scene();

						break;
					}
					else
					{
						return;
					}

				}
			}
			else if (opt == map_bt)
			{
				se.ChooseMap(msg);
				cout << "choose map" << endl;
				break;

			}
			else if (opt == role_bt)
			{
				se.change_role(&role, appearence);
				cout << "choose role" << endl;
				break;

			}
			else if (opt == exit_bt)
			{
				EXIT = true;
				cout << "exit game" << endl;
				break;

			}
			else if (opt == choosemode_bt)
			{
				defaultmode = se.setmode(msg);
				gameInit(defaultmode);
				cout << "set mode";
				break;
			}
			else if (opt == enter_bt)
			{
				GODMODE ^= 1;
				se.chanegbt(enter_bt)->rename(GODMODE ? "关闭作弊" : "开启作弊");
			}
			
		}
	}
	return;
}
int main(void)
{

	testbutton();
	return 0;

}

