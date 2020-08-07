#pragma once
#include "MyView.h"

class CSnake
{
public:
    CSnake(unsigned short y = 0);
    ~CSnake();
    //获取蛇头的XY
    unsigned short GetHeadX() { return this->x; };
    unsigned short GetHeadY() { return this->y; };
    char GetAlive() { return this->alive; };

    //功能区-》移动蛇
    void Refresh(unsigned char cOrientatio = '\0', bool IsPrint = false);
    //设置蛇的方向
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