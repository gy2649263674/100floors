#pragma once 
#include"Atlas.h"
extern const double  v0;
enum Boardtype
{
	normaltype = 0,
	nailtype,
	righttype,
	lefttype,
	faketype,
	trampolinetype,
};
class Board
{
public:
	Board()
	{}
	int x;
	int y;
	int len = 100;
	int type = normaltype;
	bool exist = true;
	bool used = false;
	int stay = 0;
	int play;
	bool have_item = false;
	int item_type = 0;
	static double V;
	static void reset()
	{
		V = v0;
	}
private:
};