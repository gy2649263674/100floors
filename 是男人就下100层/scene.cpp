#include"all.h"

Atlas::Atlas(const char* rootdir, const char* name, int w, int h, int n, const char* mask)
{
	add_image(rootdir, name, w, h, n, ".png");
	if (mask != "")
		add_image(rootdir, name, w, h, n, ".png", MASK);
}
int Start::process_command(ExMessage& msg)
{
	int com = -1;
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->in_area(msg))
		{
			com = buttons[i]->react(msg) ? i : com;
			enter_scene();
			return com;
		}
	}
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
		settextstyle(50, 0, "consola");
		outtextxy(WORDX, (MAINH - 100), "就决定是你了");
		while (peekmessage(&msg, EX_KEY | EX_MOUSE))
		{
			if ((msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT) && msg.message == WM_KEYUP)
			{
				cleardevice();
				int delt = (msg.vkcode) - (VK_LEFT + VK_RIGHT) / 2;//正负绝对左右移动
				cur_back = (cur_back + 1 * delt + back_ground->get_size()) % back_ground->get_size();
				putimage(0, 0, (*back_ground)[cur_back]);
			}
			else if (msg.vkcode == VK_RETURN)
			{
				enter_scene();
				return;
			}
		}
	}

}


Button::Button(const char* filename, const char* text_)
{
	this->images->add_image(BTDIR, filename, BTW, BTH, 1, ".ico");
	this->images->add_image(BTDIR, filename, BTW, BTH, 1, ".ico", MASK);
	text = string(text_);
}
int Button::react(ExMessage& msg)
{
	while (in_area(msg))
	{
		draw_words(HANGON);
		draw_lucency(x + wordsw + gap * 1.5, y, arrow, arrow + 1);
		peekmessage(&msg, EX_MOUSE);
		if (msg.lbutton)
		{
			draw_words(HANGON);
			draw_lucency(msg.x - 20, msg.y - 20, cursor, cursor + 1);
			while (msg.message != WM_LBUTTONUP)
			{
				peekmessage(&msg, EX_MOUSE);
			}
			if (in_area(msg))
			{
				draw_words(CLICKED);
				return true;
			}
			else
			{
				draw_words(UNIN);
				continue;
			}
		}
	}
}
