
#include <iostream>
#include <easyx.h>
#include <ctime>
#include <Windows.h>
#include"all.h"
#include "Timer.h"
#include "Anime.h"
#include "Character.h"
#include "Draw.h"
#include"scene.h"
//#include <system.h>
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
<<<<<<< Updated upstream
Character role;
=======
>>>>>>> Stashed changes
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
}
void gameInit()
{
	loadresource();
	loadimage(health, "./picture/health/health1.png", 40, 40);
	loadimage(health + 1, "./picture/health/health1_mask.png", 40, 40);
	loadimage(roof_img, "./picture/ceiling.png");
	loadimage(roof_img + 1, "./picture/ceiling_mask.png");
	loadimage(board_img, "./picture/unit/normal.png");
	loadimage(board_img + 1, "./picture/unit/nails.png");
	loadimage(board_img + 2, "picture/nails_mask.png");
	loadimage(&conveyor_left, "./picture/conveyor_left.png");
	loadimage(&conveyor_right, "./picture/conveyor_right.png");
	loadimage(fake, "./picture/fake.png");
	loadimage(fake + 1, "picture/fake_mask.png");
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
			int btype = rand() % 5;
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
		cout << "now direct:" << (direct == LEFT ? "left" : "right") << role.curframe << endl;
	return;
}

void gamedraw(Character& role)
{
	draw_lucency(0, 0, roof_img, roof_img + 1);
	draw_lucency(400, 0, roof_img, roof_img + 1);
	draw_lucency(800, 0, roof_img, roof_img + 1);

	for (int i = 0; i < role.health; i++)
	{
		putimage(600 + i * 40, 10, &health[1], SRCAND);
		putimage(600 + i * 40, 10, &health[0], SRCPAINT);
	}
	for (int i = 0; i < 150; i++)
	{
		if (board[i].type == 0)
		{
			draw_lucency(board[i].x, board[i].y, board_img, board_img + 1);
		}
		else if (board[i].type == 1)
		{
			putimage(board[i].x, board[i].y, &board_img[2], SRCAND);
			putimage(board[i].x, board[i].y, &board_img[1], SRCPAINT);
		}
		else if (board[i].type == 2)
		{
			putimage(board[i].x, board[i].y, 96, 217 / 6, fake, 0, 0);
			//putimage(board[i].x, board[i].y, 96, 217 / 6, fake, 0, 0, SRCPAINT);
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
	}
	if (msg.vkcode == VK_LEFT)
	{
		draw_lucency(role, LEFT);
	}
	else if (msg.vkcode == VK_RIGHT)
	{
		draw_lucency(role, RIGHT);
	}
	/*else
	{
		role.standing();
	}*/
	flushmessage();
}

void board_move()
{

	for (int i = 0; i < 150; i++)
	{
<<<<<<< Updated upstream
		board[i].y -= 1;
=======
		board[i].y -= 3;
>>>>>>> Stashed changes
		if (board[i].y < 0)
		{
			board[i].y = 150 * BOARD_GAP;
			board[i].x = rand() % (LENGTH - 350);
			board[i].type = rand() % 5;
			board[i].used = false;
			board[i].stay = 0;
		}
	}
}
void insert(Character& role)
{
	draw_lucency(0, 0, roof_img, roof_img + 1);
	draw_lucency(400, 0, roof_img, roof_img + 1);
	draw_lucency(800, 0, roof_img, roof_img + 1);
	for (int i = 0; i < role.health; i++)
	{
		putimage(600 + i * 40, 10, &health[1], SRCAND);
		putimage(600 + i * 40, 10, &health[0], SRCPAINT);
	}
	for (int i = 0; i < 150; i++)
	{
		if (board[i].type == 0)
		{
			draw_lucency(board[i].x, board[i].y, board_img, board_img + 1);
		}
		else if (board[i].type == 1)
		{
			putimage(board[i].x, board[i].y, &board_img[2], SRCAND);
			putimage(board[i].x, board[i].y, &board_img[1], SRCPAINT);
		}
		else if (board[i].type == 2)
		{
			putimage(board[i].x, board[i].y, 96, 217 / 6, fake, 0, 0);
		}
		else if (board[i].type == 3)
		{
			putimage(board[i].x, board[i].y, 96, 16, &conveyor_left, 0, 0);
		}
		else if (board[i].type == 4)
		{
			putimage(board[i].x, board[i].y, 96, 16, &conveyor_right, 0, 0);
		}
	}
	role.standing();
	//Sleep(FRAME);
}

void tempgameing()
{

	while (1)
	{
		/*if (peekmessage(&msg, EX_KEY, false) == false)
		{
			BeginBatchDraw();
			insert(role);
			EndBatchDraw();
			Timer::endkeep();
			continue;
		}*/
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, se.get_background());
<<<<<<< Updated upstream
		gamedraw();
		if (Timer::timer(20, 1))
			role.character_move();
		if (Timer::timer(5, 0))
			board_move();
=======
		//board_move();
		role.character_move();
		gamedraw(role);
>>>>>>> Stashed changes
		EndBatchDraw();
		Timer::endkeep();

	}
}

//void act()
//{
//	while (peekmessage(&msg, EX_KEY))
//	{
//		if (msg.vkcode == VK_LEFT)
//		{
//			role.
//		}
//	}
//
//}
void testbutton()
{
	se = Start();
	creatgame();
	gameInit();
	role = Character("ch", 4);
	//se.enter_scene();
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
	//se.enter_scene();
	//testbutton();
	testbutton();
	return 0;

}

