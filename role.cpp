#include"all.h"
const char* Role::get_role_name()const
{
	return &role_name[0];
}
int  Role::get_image_num()const
{
	return image_num;
}
int  Role::getx()const
{
	return x;
}
int Role::gety()const
{
	return y;
}
const IMAGE* Role:: get_frame(int index)const
{
	//return (this->role_image)->get_image(index);
	return 0;
}
void  Role::rotate()
{
}
int Role::get_frame()
{
	return 0;
}