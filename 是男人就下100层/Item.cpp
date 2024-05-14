#include "Item.h"
#include "Timer.h"
#include "Character.h"
extern Board board[150];
extern Character role;
extern IMAGE cure_img[2];
extern IMAGE gold_img[2];
extern IMAGE defend_img[2];

//type为0（血包），1（护甲），2（收藏（加分用的））
int Item::creatitem(int &index)
{
	index = rand() % 150;
	int index2 = rand() % 3;
	if(index2==0)
	{
		/*putimage(board[index].x + 4, board[index].y - 10, cure_img + 1, SRCAND);
		putimage(board[index].x + 4, board[index].y - 10, cure_img, SRCPAINT);*/
		return 0;
		//draw_lucency(board[index].x + 3, board[index].y, cure_img, cure_img + 1);
	}
	else if (index2 == 1)
	{
		/*putimage(board[index].x + 4, board[index].y - 10, defend_img + 1, SRCAND);
		putimage(board[index].x + 4, board[index].y - 10, defend_img, SRCPAINT);*/
		return 1;
		//draw_lucency(board[index].x + 3, board[index].y, defend_img, defend_img + 1);

	}
	else if (index2 == 2)
	{
		/*putimage(board[index].x + 4, board[index].y - 10, gold_img + 1, SRCAND);
		putimage(board[index].x + 4, board[index].y - 10, gold_img, SRCPAINT);*/
		return 2;
		//draw_lucency(board[index].x + 3, board[index].y, gold_img, gold_img + 1);

	}
	
}