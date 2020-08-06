#include "MyView.h"
#include <cstdio>

char map[MAP_H][MAP_W];
HANDLE gOUTPUT;

void MAPprint()
{
    system("cls");
    unsigned short i = MAP_W + 2, tmp, j = 0;
    while (i-- > 0)
        cout << INFOFoods[FOODSWALL];
    cout << " 游戏时长：\n";
    for (i = 0; i < MAP_H; i++)
    {
        cout << INFOFoods[FOODSWALL];
        for (j = 0; j < MAP_W; j++)
        {
            switch (map[i][j]) {
            case MAPSHead:  tmp = FOODSHEAD; break;
            case MAPSBody:  tmp = FOODSBODY; break;
            default:        tmp = FOODSNULL; break;
            }
            cout << INFOFoods[tmp];
        }
        
        switch (i) {                            //侧边栏输出
        case 0:                                 //第0行输出时间
            cout << INFOFoods[FOODSWALL] << " 00:00\n"; break;
        case 2:
            cout << INFOFoods[FOODSWALL] << " 游戏分数：\n"; break;
        case 3:
            cout << INFOFoods[FOODSWALL] << " 000000\n"; break;
        default:
            cout << INFOFoods[FOODSWALL] << "\n";
            break;
        }
    }
    for (i = MAP_W + 2; i > 0; --i)
        cout << INFOFoods[FOODSWALL];
    cout << endl;
}

ubool InitView()
{
    gOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1,false };
    return (ubool)SetConsoleCursorInfo(gOUTPUT, &cursor);
    //return true;
}
ubool SetXY(SHORT x, SHORT y,char index)	//自定义 gotoxy 函数
{
    if (index != '\0') {
        COORD xy = { xy.X = x,xy.Y = y };
        SetConsoleCursorPosition(gOUTPUT, xy);
        cout << INFOFoods[index] << flush;
    }
    return false;
}

ubool SetXY(SHORT x, SHORT y, const char* buff)
{
    if (buff != nullptr) {
        COORD xy = { xy.X = 10,xy.Y = 10 };
        SetConsoleCursorPosition(gOUTPUT, xy);
        printf(buff);
    }
    return false;
}

ubool SetMAP(SHORT x, SHORT y, char index)
{
    if (x >= 0 && y >= 0 &&
        x <= MAP_W && y <= MAP_H)
    {
        map[y][x] = index;
    }
    return false;
}

unsigned char GetMAP(SHORT x, SHORT y)
{
    if (x >= 0 && y >= 0 &&
        x <= MAP_W && y <= MAP_H)
    {
        return map[y][x];
    }
    return '\0';
}
