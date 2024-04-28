#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include"all.h"
using namespace std;

void GameStart(ExMessage& msg)
{

	/*while (1)
	{
		peekmessage(&msg, EX_SHOWCONSOLE | EX_DBLCLKS);
		BeginBatchDraw();
		short curx = msg.x, cury = msg.y;
		setfillcolor(WHITE);
		fillcircle(curx, cury, 10);
		EndBatchDraw();
	}*/
}
void GameOver()
{

}
int main(void)
{
	//Widget mainWindow(1000,1000);
	//ExMessage msg;
	//GameStart(msg);
//GameOver();
	Atlas n("girl",500);
	test(n);
	return 0;

}
