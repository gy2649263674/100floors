#if 0
#include "Anime.h"
#include <ctime>
#include "board.h"
extern Board board[150];
extern IMAGE conveyor_right;
extern IMAGE conveyor_left;
extern IMAGE fake;

void Anime::anime_conveyor_right(int i)
{
	loadimage(&conveyor_right, "./picture/conveyor_right.png");
	int frame = 4;
	int speed = 200;
	int h = 16;
	int index = 0;
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		putimage(board[i].x, board[i].y, 96, h, &conveyor_right, 0, index * h);
		index = clock() / speed%frame;
		EndBatchDraw();
	}
}
void Anime::anime_conveyor_left(int i)
{
	loadimage(&conveyor_left, "./picture/conveyor_left.png");
	int frame = 4;
	int speed = 200;
	int h = 16;
	int index = 0;
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		putimage(board[i].x, board[i].y, 96, h, &conveyor_left, 0, index * h);
		index = clock() / speed % frame;
		EndBatchDraw();
	}
}
void Anime::anime_fake(int i)
{
	loadimage(&fake,"./picture/fake.png");
	int frame = 6;
	int speed = 100;
	int h = 217 / 6;
	int index = 0;
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		putimage(board[i].x, board[i].y, 96, h, &fake, 0, index * h);
		index = clock() / speed % frame;
		EndBatchDraw();
	}
}
#endif