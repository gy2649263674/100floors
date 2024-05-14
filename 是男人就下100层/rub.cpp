//void trace(IMAGE* a = NULL, IMAGE* b = NULL)
//{
//	creatgame();
//	setbkcolor(WHITE);
//	int fps = 144;
//	Button ba;
//	Atlas bk;
//	ba.init("exit", "fuck");
//	while (1)
//	{
//		while (peekmessage(&msg, EX_MOUSE | EX_KEY))
//		{
//			int st = clock();
//			fillcircle(msg.x, msg.y, 5);
//			BeginBatchDraw();
//			cleardevice();
//			putimage(msg.x, msg.y, b, SRCPAINT);
//			putimage(msg.x, msg.y, a);//,SRCAND);
//			clearrectangle(msg.x, msg.y, msg.x + a->getwidth() + 1, msg.y + a->getheight() + 1);
//			draw_lucency(msg.x, msg.y, a, b);
//			EndBatchDraw();
//			getchar();
//			if (msg.vkcode == VK_BACK)
//			{
//				return;
//			}
//			int end = clock();
//			Sleep(max(0, 1000 / fps - (end - st)));
//		}
//	}
//}
//void testmask(IMAGE a[2])
//{
//	trace(&a[0], &a[1]);
//}

//void Character::exhibit(int direct)
//{
//	if (direct == RIGHT)
//	{
//		draw_lucency(x, y, images->get_image(curframe), images->get_mask_image(curframe));
//		curframe = ((++curframe) %= runsize) == 0 ? 1 : curframe;
//		//= 0->1
//	}
//	else
//	{
//		//draw_lucency(x, y, rimages->get_image(curframe), rimages->get_mask_image(curframe));
//		for (int i = 0; i <= 4; i++)
//		{
//			draw_lucency(x, y, rimages->get_image(i), rimages->get_mask_image(i));
//			i %= 4;
//		}
//		curframe = ((++curframe) %= runsize) == 0 ? 1 : curframe;
//
//	}
//}
