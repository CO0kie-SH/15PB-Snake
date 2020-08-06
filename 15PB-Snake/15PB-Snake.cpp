/*  15PB-Snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
    IDE     :   Visual_Studio_2019
    Time    :   20200803-20:00
    By      :   Hongwei.Mao
    Coding  :   UTF-8
    Ver     :   V1.0
*/
//本项目开源地址 https://github.com/mhw666/15PB-Snake 本文件开源地址：
//https://github.com/mhw666/15PB-Snake/blob/master/15PB-Snake/15PB-Snake.cpp

#include <conio.h>
#include "CSnake.h"
#pragma comment(lib,"winmm.lib")

int main()
{
    //PlaySoundA("bg.wav", NULL, SND_ASYNC | SND_NODEFAULT);
    InitView();
    int key = 0, SNKLen = 1, lenPass = 3, lenFood1 = 2;
    CSnake* cSnake[] = { nullptr,nullptr };
    CFood* cFood[5] = { nullptr };
    switch (SNKLen) {
    case 2:cSnake[1] = new CSnake(2); cSnake[0] = new CSnake(0); break;
    case 1:cSnake[0] = new CSnake(0); break;
    default:return 0; break;
    }
    InitMap(cFood[5],);
    while (key!=27)
    {
        key = _getch();
        if (SNKLen == 1 && cSnake[0]->GetAlive()) {
            switch (key)
            {
            case KLeft:case 'A':
                cSnake[0]->Refresh('A', true); break;
            case KRight:case 'D':
                cSnake[0]->Refresh('D', true); break;
            case KDown:case 'S':
                cSnake[0]->Refresh('S', true); break;
            case KUp:case 'W':
                cSnake[0]->Refresh('W', true); break;
            case 59:
                SetXY((cSnake[0]->GetHeadX() * 2) + 2, cSnake[0]->GetHeadY() + 1, FOODSERR);
                break;
            case 224:break;
            default:
                //std::cout << "键码\t"<<key << std::endl;
                break;
            }
        }
    }
    //结束循环，开始释放资源
    for (int i = 0; i < 5; i++)
    {

    }
}
