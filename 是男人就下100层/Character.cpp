#include "Character.h"
#include "easyx.h"
#include "Timer.h"
#include <ctime>
#include"unit.h"
#include"Atlas.h"
extern int act;
extern deque<Board>board;
const double conveyer_ratio = 2;
extern Board roof;
extern ExMessage msg;
const double gap = 1000.0 / FRAME;
const int yu = 600;
enum Boardtype;
#define SPEED 150
#define INCREASE 50
#define FALL_INCREASE 2
//extern pair<double,double>
string getv[10];
static double lspeed = SPEED;
static double rspeed = SPEED;
using namespace std;
extern bool GODMODE;

int Character::character_move()
{
	score += 1;
	Rank::score += 1;
	static double G = 6;
	static int pre = RIGHT;
	if (GetAsyncKeyState(VK_LEFT) && x > 0)
	{
		rspeed = SPEED;
		lspeed += INCREASE;
		cout << "rspeed :" << rspeed << " ";
		cout << "lspeed :" << lspeed << endl;
		x -= min(lspeed, yu) * gap;
		rspeed = SPEED;
		lspeed += INCREASE;
		cout << "rspeed :" << rspeed << " ";
		cout << "lspeed :" << lspeed << endl;
		x -= min(lspeed, yu) * gap;
		msg.vkcode = VK_LEFT;
		move();
		pre = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && x < 700)
	{
		lspeed = SPEED;
		rspeed += INCREASE;
		x += min(rspeed, yu) * gap;
		cout << "rspeed :" << rspeed << " ";
		cout << "lspeed :" << lspeed << endl;
		msg.vkcode = VK_RIGHT;
		move();
		pre = RIGHT;
	}
	else
	{
		if (lspeed != SPEED || rspeed != SPEED)
		{
			lspeed = SPEED;
			rspeed = SPEED;
			reset_standing();
		}
		this->direct = pre;
		standing(pre);
		pre = 0;
	}
	if (GODMODE)
	{
		if (GetAsyncKeyState(VK_UP) && x < 750)
		{
			y -= 50;
		}
		else if (GetAsyncKeyState(VK_DOWN) && x < 750)
		{
			y += 50;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			msg.vkcode = VK_SPACE;
			//return pre;
		}
	}

	int x2 = this->x + h / 2;
	int y2 = this->y + h;
	//判断玩家在哪一块板子上
	for (int i = 0; i < 150; i++)
	{
		if (board[i].type == lefttype || board[i].type == righttype)
		{
			board[i].play++;
		}
		if (board[i].type == faketype && board[i].play >= 12)
		{
			board[i].play++;
		}
		if (x2 >= board[i].x && x2 <= board[i].len + board[i].x
			&& y2 >= board[i].y - Board::V * FRAME / 4 && y2 <= board[i].y + Board::V * FRAME / 4)
		{
			this->y = board[i].y - h;
			ob = i;
			if (board[i].type == normaltype)
			{
				if (board[i].stay == 0)
				{
					board[i].stay++;
					PlaySound("./sound/wav/land.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				if (board[i].have_item == true)
				{
					if (board[i].item_type == 0)
					{
						health = 3;
						board[i].have_item = false;
					}
					else if (board[i].item_type == 1)
					{
						if (have_armo == false)
						{
							board[i].have_item = false;
							have_armo = true;
						}
					}
					else if (board[i].item_type == 2)
					{
						board[i].have_item = false;
						Rank::score += 500;
						score += 500;
					}
				}
			}
			if (board[i].type == 1 && board[i].used == false)
			{
				if (have_armo == true)
				{
					have_armo = false;
				}
				else
				{
					PlaySound("./sound/wav/hurt 8bit.wav", NULL, SND_FILENAME | SND_ASYNC);
					health--;
				}
				board[i].used = true;
				break;
			}
			else if (board[i].type == faketype)
			{
				board[i].stay++;
				if (board[i].stay > 10)
				{
					y += Board::V * FRAME / 4;
					board[i].play++;
					//break;
				}
				if (board[i].play == 4)
				{
					PlaySound("./sound/wav/fake.wav", NULL, SND_FILENAME | SND_ASYNC);
				}

				board[i].play++;
			}
			else if (board[i].type == lefttype)
			{
				if (board[i].stay == 0)
				{
					board[i].stay++;
					PlaySound("./sound/wav/land.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				if (x > 0)
				{
					x -= SPEED * gap * conveyer_ratio;
				}
				break;
			}
			else if (board[i].type == righttype)
			{
				if (board[i].stay == 0)
				{
					board[i].stay++;
					PlaySound("./sound/wav/land.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				if (x < 900)
					x += SPEED * gap * conveyer_ratio;
				break;
			}
			else if (board[i].type == trampolinetype)
			{
				board[i].stay++;
				if (board[i].stay == 5 && board[i].type == trampolinetype)
				{
					jump = 30 - Board::V / 2;
					PlaySound("./sound/wav/springboard.wav", NULL, SND_FILENAME | SND_ASYNC);
					//y -= 400/Board::V;
					y -= (Board::V * FRAME / 2);//*FRAME;
				}
				break;
			}
			break;


		}
		else
		{
			ob = -1;
			board[i].stay = max(0, --board[i].stay);
			board[i].play = 0;//max(0, --board[i].play);
		}
	}
	if (jump)
	{
		//y -= 10;
		y = max(0, y - 10);
		jump--;
		//return 0;
	}
	if (ob == -1)
	{
		y += (G += 0.5);
	}
	else
	{
		G = FALL_INCREASE;
	}
	if (y <= 0 && roof.used == false)
	{
		if (have_armo == true)
		{
			have_armo = false;
		}
		else
		{
			PlaySound("./sound/wav/hurt 8bit.wav", NULL, SND_FILENAME | SND_ASYNC);
			health--;
		}
		roof.used = true;
	}
	if (y > 720)
	{
		health = 0;
	}
	if (y > 0)
	{
		roof.used = false;
	}
	static double prevy = y;
	getv[0] = "left:" + to_string(lspeed == SPEED ? 0 : lspeed / 10) + "  right:" + to_string(rspeed == SPEED ? 0 : rspeed / 10);
	getv[1] = "falling:" + to_string(abs((y - prevy)) * 20000 / FRAME);//(abs(G- FALL_INCREASE)<1e-6?0: FALL_INCREASE*FRAME);
	getv[2] = "(" + to_string(x) + "," + to_string(y) + ")";
	prevy = y;
	return pre;

}
void flip(Atlas* s, Atlas* d)
{
	for (int i = 0; i < s->get_size(); i++)
	{
		IMAGE* src = s->get_image(i);
		IMAGE* des = d->get_image(i);
		int h = src->getheight();
		int w = src->getwidth();
		if (des->getwidth() != w || des->getheight() != h)
		{
			des->Resize(w, h);
		}
		DWORD* des_ = GetImageBuffer(des);
		DWORD* src_ = GetImageBuffer(src);
		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++)
				des_[y * w + w - x] = src_[y * w + x];
	}
	return;
}


void filp(IMAGE* src, IMAGE* des)
{
	int h = src->getheight();
	int w = src->getwidth();
	if (des->getwidth() != w || des->getheight() != h)
	{
		des->Resize(w, h);
	}
	DWORD* des_ = GetImageBuffer(des);
	DWORD* src_ = GetImageBuffer(src);
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			des_[y * w + w - x] = src_[y * w + x];
	return;
}
bool Character::is_dead()
{
	if (health <= 0)
	{
		PlaySound("./sound/wav/death.wav", NULL, SND_FILENAME | SND_ASYNC);
		return true;
	}
	return false;
}
#include<graphics.h>
#include<easyx.h>
Character::Character(const char* name, int n, int standing_size, Picset* img)
{
	//images = img.pic;//new Atlas(name, "未标题-", runsize, ROLEW, ROLEH);
	//rimages = img.rpic;//new Atlas(runsize);
	change_app(img);
	this->runsize = img->run;
	this->standing_size = img->stand;
	this->standing_frame = 0;
	set_sta(board[0]);
	return;
}
void draw_lucency(Character& role, int direct);
void draw_lucency(int x, int y, int w, int h, IMAGE* ori, IMAGE* mask);

int co = 0;
#include<functional>
#include"Anime.h"
int Character::exhibit(int direct, Start* ptr)
{
	ExMessage msg;
	Atlas* temp = direct == RIGHT ? images : rimages;
	BeginBatchDraw();
	cleardevice();
	Anime::draw_back_img(ptr);
	//putimage(0, 0, back);
	draw_lucency(MAINW / 2, MAINH / 2, temp->get_image(0), temp->get_mask_image(0));
	++co;
	cout << "co" << co << endl;
	while (1)
	{
		while (peekmessage(&msg, EX_KEY) | 1)
		{
			for (int i = 0; 1; i++)
			{
				peekmessage(&msg, EX_KEY);
				if (msg.vkcode == VK_RETURN)
				{
					return 1;
				}
				else if (msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT)
				{
					ExMessage m = {};
					msg = m;
					return 0;
				}
				static int picfp = i / PICGAP / 3;
				picfp = i / PICGAP / 3;
				i = picfp >= runsize + standing_size - 1 ? 0 : ++i;
				BeginBatchDraw();
				cleardevice();
				Anime::draw_back_img(ptr);
				//putimage(0, 0, back);
				draw_lucency(MAINW / 2, MAINH / 2, temp->get_image(picfp), temp->get_mask_image(picfp));
				outtextxy(0, 0, "按enter键选择角色");
				EndBatchDraw();
				Timer::endkeep(FRAME);
			}
		}
	}
	return 0;
}
