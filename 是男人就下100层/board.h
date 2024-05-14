#pragma once 
#include"scene.h" 
class Board 
{ public: 
int x; int y;
int len; int type;
bool exist; bool used;
int stay; bool have_item; 
int item_type;
private: Atlas* images; };