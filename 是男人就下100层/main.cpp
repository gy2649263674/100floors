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
		if (opt == startgame)
		{
			start_scene.ChooseMap(msg);
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
	return 0;
}