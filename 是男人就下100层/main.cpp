#include"all.h"
#include<system.h>
IMAGE cursor[2];
IMAGE arrow[2];
bool EXIT = false;
ExMessage msg;
Atlas back;
IMAGE border[2];


void creat()
{
	initgraph(MAINW, MAINH);
	cleardevice();
	HWND handle = GetHWnd();
	MoveWindow(HWND(handle), MAINX, MAINY, MAINW, MAINH, true);
}
void trace(IMAGE* a = NULL, IMAGE* b = NULL)
{
	//creat();
	//setbkcolor(WHITE);
	int fps = 144;
	Button ba;
	Atlas bk;
	//ba.init("exit", "fuck");
	while (1)
	{
		while (peekmessage(&msg, EX_MOUSE | EX_KEY))
		{
			int st = clock();
			//fillcircle(msg.x, msg.y, 5);
			BeginBatchDraw();
			//cleardevice();
			//putimage(msg.x,msg.y,b,SRCPAINT);
			//putimage(msg.x, msg.y, a);//,SRCAND);
			//clearrectangle(msg.x, msg.y, msg.x+a->getwidth()+1, msg.y+a->getheight()+1);
			draw_lucency(msg.x, msg.y, a, b);
			EndBatchDraw();
			//getchar();
			if (msg.vkcode == VK_BACK)
			{
				return;
			}
			int end = clock();
			Sleep(max(0, 1000 / fps - (end - st)));
		}
	}
}
void testmask(IMAGE a[2])
{
	trace(&a[0], &a[1]);
}
void test1()
{
	//IMAGE yuan;
	//setbkcolor(WHITE);
	//setfillcolor(WHITE);

	//	Atlas yuan;
		//back.add_image("map", "background", MAINW, MAINH, 2, ".png");
		//yuan.add_image("button", "exit", 50, 50, 1, ".ico");
		//yuan.add_image("button", "exit", 50, 50, 1, ".ico", "_mask");
		//trace(yuan[0], yuan.get_mask_image(0));;
	fillrectangle(100, 100, 600, 600);
	//putimage(100, 100, yuan.get_mask_image(0));
}
void testbutton()
{
	//initgraph(MAINW, MAINH);
	creat();
	setbkcolor(BLACK);
///testmask(border);
	Start se;
	se.enter_scene();
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


void loadresource()
{
	//arrow = new (IMAGE*)[2];
	loadimage(border,"picture/button/border.png",Button::wordsw,Button::h);
	loadimage(border+1, "picture/button/border_mask.png", Button::wordsw, Button::h);
	loadimage(&arrow[0], "picture/button/arrow.png");
	loadimage(&arrow[1], "picture/button/arrow_mask.png");
	loadimage(cursor, "picture/button/cursor.ico");
	loadimage(cursor+1, "picture/button/cursor_mask.ico");
}
int main(void)
{
	loadresource();
	//testmask(arrow);
	testbutton();
	return 0;
	//SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	Start start_scene;
	ExMessage msg;
	while (1)
	{
		while (peekmessage(&msg, EX_MOUSE | EX_KEY))
		{
			StartOpt opt = StartOpt(start_scene.process_command(msg));
			if (opt == startgame)
			{
				//start_scene.ChooseMap(msg);
			}
			else if (opt == choose_map)
			{
				return 0;
			}
			else if (opt == choose_role)
			{

			}
			else if (opt == exit_game)
			{
				return 0;
			}
		}
	}
	return 0;
}