#pragma once
#include "MyView.h"


class CSnake
{
public:
    CSnake();
    ~CSnake();
    void Refresh(unsigned char cOrientatio = '\0', bool IsPrint = false);
    bool SetOrientation(unsigned char cOrientatio);
    
private:
    unsigned short x;
    unsigned short y;
    unsigned char orientation;
    unsigned char buff[50];
    unsigned short bodylen;
    SNKBODY* body;
    SNKBODY* bodyEND;

    void GameOver(unsigned char cOrientatio);
};