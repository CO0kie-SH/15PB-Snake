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
	unsigned short x, y;						//�����������һ������
	unsigned char kind;							//������������
};

