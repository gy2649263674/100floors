#include"all.h"
int Start::process_command(ExMessage& msg)
{
	if (start_button->in_area(msg))
	{
		return startgame;
	}
	else if (map_button->in_area(msg))
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

void Start::ChooseMap(ExMessage& msg)
{
	while (peekmessage(&msg, EX_KEY))
	{
		if (msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT)
		{
			cleardevice();
			int delt = (msg.vkcode) - (VK_LEFT + VK_RIGHT) / 2;//正负绝对左右移动
			cur_back = (cur_back * delt + back_ground->get_size()) % back_ground->get_size();
			putimage(0, 0, (*back_ground)[cur_back]);
			outtextxy(WORDX, (MAINH - 30), &map_explain[cur_back][0]);
		}
		else if (msg.vkcode == VK_RETURN)
		{
			return;
		}
	}
}


void ChooseRole(ExMessage)
{

}