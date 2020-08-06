#include "CFood.h"


CFood::CFood(unsigned char kind)
{
	this->kind = kind;
	this->Refresh();
}

CFood::~CFood()
{
}

void CFood::Refresh(bool IsPrint)
{
	COORD xy = GetRandomByMap();
}
