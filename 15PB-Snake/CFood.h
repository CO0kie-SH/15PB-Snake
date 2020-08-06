#pragma once
#include "MyView.h"

class CFood
{
public:
	CFood(unsigned char kind);
	~CFood();
	void Refresh(bool IsPrint = false);
private:
	unsigned short x, y;						//定义坐标和下一个坐标
	unsigned char kind;							//定义自身种类
};

