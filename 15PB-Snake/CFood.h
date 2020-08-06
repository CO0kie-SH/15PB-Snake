#pragma once
#include "MyView.h"

class CFood
{
public:
	CFood(unsigned char kind);
	~CFood();
	unsigned short GetX() { return this->x; };
	unsigned short GetY() { return this->y; };
	bool Refresh();

private:
	unsigned short x, y;						//定义坐标和下一个坐标
	unsigned char kind;							//定义自身种类
};

