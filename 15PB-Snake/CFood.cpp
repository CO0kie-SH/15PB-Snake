#include "CFood.h"


CFood::CFood(unsigned char kind)
{
	this->kind = kind;								//赋值给自己类型
	if (!this->Refresh())							//初始化食物位置
	{
		cout << "这不科学！错误代码0x01" << endl;	//初始化不存在没有坐标可用
		system("pause");
		exit(1);
	}
}

CFood::~CFood()
{
}

bool CFood::Refresh()
{
	ubool ub = false;
	COORD xy = { xy.X = 0,xy.Y = 0 };
	ub = GetRandomByMap(xy);
	if (ub && SetMAP(xy.X, xy.Y, this->kind)) {
		this->x = xy.X; this->y = xy.Y;
		map[this->y][this->x] = this->kind;
	}
	return (bool)ub;
}