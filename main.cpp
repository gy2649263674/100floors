#include"all.h"
#include<system.h>


int main(void)
{
	initgraph(MAINW, MAINH);
	HANDLE handle = GetHWnd();
	//HWND = find(
	MoveWindow(HWND(handle),MAINX,MAINY,MAINW, MAINH,true);
	Start start_scene;
	ExMessage msg;
	while (peekmessage(&msg, EX_MOUSE | EX_KEY))
	{
		StartOpt opt  = StartOpt (start_scene.process_command(msg));
		if (opt == startgame);
		{

		}
		if (opt == choose_map)
		{

		}
		if (opt == choose_role)
		{

		}
		if (opt == exit_game)
		{
			return 0;
		}
	}
	return 0;
}