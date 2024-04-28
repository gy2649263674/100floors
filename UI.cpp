#include"all.h"

Widget::Widget(int x, int y, int w, int h)
{
	initgraph(x, y,0 | EX_DBLCLKS);
}
Widget::Widget(int x, int y)
{
	initgraph(x, y, 0 | EX_DBLCLKS);
}
