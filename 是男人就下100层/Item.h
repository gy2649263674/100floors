#pragma once
#include "board.h"
class Item
{
public:
	int x;
	int y;
	int type;	
	static int creatitem(int& index);
};

