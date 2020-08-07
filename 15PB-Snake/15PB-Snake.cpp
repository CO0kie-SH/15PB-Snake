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

int key = 0, lenPass = 3, lenFood1 = 2, i = 0, imenu = 1;
CSnake* cSnake[] = { nullptr,nullptr };
DWORD time = 10;

void GoGame(int people)
{
    char go = 'G';
    memset(map, 0, MAP_H * MAP_W);
    switch (people) {
    case 2:cSnake[1] = new CSnake(2); cSnake[0] = new CSnake(0); break;
    case 1:cSnake[0] = new CSnake(0); break;
    default:return; break;
    }
    InitMap(简单);
    while (go != 'X')
    {
        Sleep(1);
        if (people == 1) {
            if (_kbhit()) {
                key = _getch();
            }
            else if (go != 'P') {
                cSnake[0]->Refresh();
                if (cSnake[0]->GetAlive())
                {
                    MAPprint(time);
                }
                else {
                    go = 'E';
                    SetXY(MAP_W * 2 + 6, MAP_H + 1, "按F1返回上一层！");
                }
                continue;
            }
            switch (key)
            {
            case KLeft:case 'A':
                //cSnake[0]->Refresh('A', true); break;
                cSnake[0]->SetOrientation('A'); break;
            case KRight:case 'D':
                //cSnake[0]->Refresh('D', true); break;
                cSnake[0]->SetOrientation('D'); break;
            case KDown:case 'S':
                //cSnake[0]->Refresh('S', true); break;
                cSnake[0]->SetOrientation('S'); break;
            case KUp:case 'W':
                //cSnake[0]->Refresh('W', true); break;
                cSnake[0]->SetOrientation('W'); break;
            case 27:        //ESC
                if (go == 'G')
                {
                    go = 'P';
                    SetXY(MAP_W * 2 + 6, MAP_H, "暂停；按F2继续！");
                    SetXY(MAP_W * 2 + 6, MAP_H + 1, "按F1返回上一层！");
                    system("color 1f");
                }
                break;
            case 32:        //空格键
                time = time == 10 ? 1 : 10;
                break;
            case 59:        //F1
                go = 'X';
                break;
            case 60:        //F2
                if (go == 'P') {
                    go = 'G';
                    system("color 0f");
                }
                break;
            case 224:break;
            default:
                //std::cout << "键码\t"<<key << std::endl;
                break;
            }
        }
        else if (people == 2)
        {
            //增加玩家②
        }
    }
    //结束循环
    DelMap();
    time = 10;
    switch (people) {
    case 2: delete cSnake[1];
    case 1: delete cSnake[0]; break;
    default:return; break;
    }
}

int main()
{
    //PlaySoundA("bg.wav", NULL, SND_ASYNC | SND_NODEFAULT);
    InitView();
    while (imenu != -1)
    {
        key = _getch();
        switch (key)
        {
        case KUp:
            if (imenu > 1) {
                MENUprint(--imenu);
            }
            break;
        case KDown:
            if (imenu < 5) {
                MENUprint(++imenu);
            }break;
        case 13:
            if (imenu == 退出) imenu = -1;
            else if (imenu == 单人游戏) GoGame(单人游戏);
            else if (imenu == 双人游戏-1) GoGame(双人游戏);
            else {
                printf("\n\n%20s%s\n%20s", " ", "功能未制作，请联系管理员", " ");
                system("pause");
            }
            MENUprint(imenu);
            break;
        default: continue; break;
        }
    }
    return 0;
}
