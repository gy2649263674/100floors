#include"all.h"
int winx = 300, winy = 300;
int main(void)
{
	setorigin(winx, winy);
	initgraph(MAINW, MAINH);
	Start start_scene;
	ExMessage msg;
	while (peekmessage(&msg, EX_MOUSE | EX_KEY))
	{
		start_scene.process_command(msg);
	}
	return 0;
}