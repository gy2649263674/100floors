#include "Item.h"
#include "Timer.h"
#include "Character.h"
extern deque<Board>  board;
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
		return 0;
	}
	else if (index2 == 1)
	{
		return 1;
	}
	else if (index2 == 2)
	{
		return 2;
	}
}