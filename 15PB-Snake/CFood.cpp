#include "CFood.h"


CFood::CFood(unsigned char kind)
{
	this->kind = kind;								//��ֵ���Լ�����
	if (!this->Refresh())							//��ʼ��ʳ��λ��
	{
		cout << "�ⲻ��ѧ���������0x01" << endl;	//��ʼ��������û���������
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