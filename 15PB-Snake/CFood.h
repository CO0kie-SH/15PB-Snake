#pragma once
#include "MyView.h"

class CFood
{
public:
	CFood(unsigned char kind);
	~CFood();
	void Refresh(bool IsPrint = false);
private:
	unsigned short x, y;						//�����������һ������
	unsigned char kind;							//������������
};

