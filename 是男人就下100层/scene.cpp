#include"all.h"
int Start::process_command(ExMessage &msg)
{
	if(start_button->in_area(msg))
	{
		return startgame;
	}
	else if(map_button->in_area(msg))
	{
		return choose_map;
	}
	else if (role_button->in_area(msg))
	{
		return choose_role;
	}
	else if (exit_button->in_area(msg))
	{
		return exit_game;
	}
	return null;
}

void Start::enter_scene()
{
	cleardevice();
	draw_pic();
	return;
}