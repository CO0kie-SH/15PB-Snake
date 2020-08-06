#pragma once
#include "MyView.h"


class CSnake
{
public:
    CSnake(unsigned short y = 0);
    ~CSnake();
    //��ȡ��ͷ��XY
    unsigned short GetHeadX() { return this->x; };
    unsigned short GetHeadY() { return this->y; };
    char GetAlive() { return this->alive; };

    //������-���ƶ���
    void Refresh(unsigned char cOrientatio = '\0', bool IsPrint = false);
    //�����ߵķ���
    bool SetOrientation(unsigned char cOrientatio);
private:
    unsigned short x, y, x2, y2;
    unsigned char orientation;
    unsigned char buff[50];
    unsigned short bodylen;
    char alive;
    SNKBODY* body;
    SNKBODY* bodyEND;

    void GameOver(unsigned char cOrientation);
};