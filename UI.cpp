#include"all.h"

Widget::Widget(int x, int y, int w, int h)
{
	initgraph(x, y, EX_SHOWCONSOLE | EX_DBLCLKS);
}
Widget::Widget(int x, int y)
{
	initgraph(x, y, EX_SHOWCONSOLE | EX_DBLCLKS);
}
