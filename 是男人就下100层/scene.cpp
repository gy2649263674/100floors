#include"all.h"

int Start::process_command(ExMessage& msg)
{
	int com = -1;
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->in_area(msg))
		{
			com = buttons[i]->react(msg) ? i : com;
			enter_scene();
			//putimage(0, 0, back_ground->get_image(0));
			//buttons[i]->draw_button();
			return com;
		}
	}
	/*if (buttons[start_bt]->in_area(msg))
	{
		com = buttons[start_bt]->react(msg) ? startgame : com;
		buttons[strtt_bt]->draw_pic();
	}
	else if (buttons[map_bt]->in_area(msg))
	{
		com = buttons[map_bt]->react(msg) ? choose_map : com;
		draw_pic();
	}
	else if (buttons[role_bt]->in_area(msg))
	{
		com = buttons[role_bt]->react(msg) ? choose_role : com;
		draw_pic();
	}
	else if (buttons[exit_bt]->in_area(msg))
	{
		com = buttons[exit_bt]->react(msg) ? exit_game : com;
		draw_pic();
	}*/
	return com;
}
void Start::enter_scene()
{
	cleardevice();
	draw_pic();
	return;
}

void Start::ChooseMap(ExMessage& msg)
{
	Button left;
	Button right;
	left.init("left");
	left.init("right");
	cleardevice();
	putimage(0, 0, (*back_ground)[cur_back]);
	while (1)
	{
		while (peekmessage(&msg, EX_KEY | EX_MOUSE))
		{
			if ((msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT) && msg.message == WM_KEYUP)
			{
				cleardevice();
				int delt = (msg.vkcode) - (VK_LEFT + VK_RIGHT) / 2;//正负绝对左右移动
				cur_back = (cur_back + 1 * delt + back_ground->get_size()) % back_ground->get_size();
				putimage(0, 0, (*back_ground)[cur_back]);
				//outtextxy(WORDX, (MAINH - 30), &map_explain[cur_back][0]);
				settextstyle(50, 0, "consola");
				outtextxy(WORDX, (MAINH - 100), "就决定是你了");
			}
			else if (msg.vkcode == VK_RETURN)
			{
				enter_scene();
				return;
			}
		}
	}

}


void ChooseRole(ExMessage)
{

}