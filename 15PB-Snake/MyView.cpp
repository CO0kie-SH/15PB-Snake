#include "MyView.h"

char map[MAP_H][MAP_W];
void MAPprint()
{
    unsigned short i = MAP_W + 2, tmp, j = 0;
    while (i-- > 0)
        cout << INFOApple[0];
    cout << " 游戏时长：\n";
    for (i = 0; i < MAP_H; i++)
    {
        cout << INFOApple[0];
        for (j = 0; j < MAP_W; j++)
        {
            switch (map[i][j]) {
            case MAPSHead:  tmp = 2; break;
            case MAPSBody:  tmp = 3; break;
            default:        tmp = 1; break;
            }
            cout << INFOApple[tmp];
        }
        
        switch (i) {                            //侧边栏输出
        case 0:                                 //第0行输出时间
            cout << INFOApple[0] << " 00:00\n"; break;
        case 2:
            cout << INFOApple[0] << " 游戏分数：\n"; break;
        case 3:
            cout << INFOApple[0] << " 000000\n"; break;
        default:
            cout << INFOApple[0] << "\n";
            break;
        }
    }
    for (i = MAP_W + 2; i > 0; --i)
        cout << INFOApple[0];
    cout << endl;
}

bool InitView()
{

    return true;
}
void gotoxy(int x, int y)	//自定义 gotoxy 函数
{
    COORD c;
    c.X = x; c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}