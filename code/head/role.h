#pragma once
#include"graph.h"
//class graph;
enum State {
	L = 0,
	R
};
enum Direction
{
	Up,
	Down,
	Left,
	Right
};
class Role
{
public:
	Role(const char* character_name, int image_num);
	Role(void);
	const char* get_role_name() const;
	int get_image_num() const;
	int getx() const;
	int gety() const;
	const IMAGE* get_frame(int index) const;
	void rotate();
	int get_frame();
	void add_atlas();
private:
	int pic_index = 0;
	int x = 0, y = 0;
	std::string role_name;
	int image_num;
	int speed = 0;
	int HP = 100;
	State state;
	//Atlas* role_image;
};
