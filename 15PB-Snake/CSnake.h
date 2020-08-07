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
    unsigned short x, y;
    unsigned short bodylen;
    unsigned short addlen;
    unsigned char orientation;
    unsigned int score;
    int alive;
    SNKBODY* body;
    SNKBODY* bodyEND;

    void GameOver(unsigned char cOrientation);
};