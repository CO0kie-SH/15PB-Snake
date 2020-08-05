/*  15PB-Snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
    IDE     :   Visual_Studio_2019
    Time    :   20200803-20:00
    By      :   Hongwei.Mao
    Coding  :   UTF-8
    Ver     :   V1.0
*/
//本项目开源地址 https://github.com/mhw666/15PB-Snake 本文件开源地址：
//https://github.com/mhw666/15PB-Snake/blob/master/15PB-Snake/15PB-Snake.cpp

#include <windows.h>
#include <conio.h>
#include "CSnake.h"
#pragma comment(lib,"winmm.lib")
int main()
{
    std::cout << "Hello World!\n";
    PlaySoundA("bg.wav", NULL, SND_ASYNC | SND_NODEFAULT);
    int key=0;
    CSnake cSnke;
    MAPprint();
    
    while (key!=27)
    {
        key = _getch();
        switch (key)
        {
        case KLeft:case 65:case 97:
            cSnke.Refresh('A', true); break;
        case KRight:
            cSnke.Refresh('D', true); break;
        case KDown:
            cSnke.Refresh('S', true); break;
        case KUp:
            cSnke.Refresh('W', true); break;
        case 224:break;
        default:
            std::cout << "键码\t"<<key << std::endl;
            break;
        }
    }
}
