#include "MyView.h"

char map[MAP_H][MAP_W];
HANDLE gOUTPUT;
CFood* gCFood[APPLE_NUM];

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

void DelView()
{
}


ubool InitMap(int difficu)
{
    memset(map, 0, MAP_H * MAP_W);              //重置地图MAP
    unsigned short n = INFODifficu[difficu][0] - '0', i = 0;
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPPASS);
    }
    n += (INFODifficu[difficu][1] - '0');
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPFOOD1);
    }
    MAPprint();
    return true;
}
void DelMap()
{
    for (unsigned char i = 0; i < APPLE_NUM; i++)
    {
        if (gCFood != nullptr) {
            delete gCFood[i];
            gCFood[i] = nullptr;
        }
    }
}
ubool SetXY(SHORT x, SHORT y,char index)
{
    if (index != '\0') {
        COORD xy = { xy.X = x,xy.Y = y };
        SetConsoleCursorPosition(gOUTPUT, xy);
        cout << INFOFoods[index] << ends;
        return true;
    }
    return false;
}

ubool SetXY(SHORT x, SHORT y, const char* buff)
{
    if (buff != nullptr) {
        COORD xy = { xy.X = x,xy.Y = y };
        SetConsoleCursorPosition(gOUTPUT, xy);
        cout << buff << ends;
        return true;
    }
    return false;
}

ubool SetMAP(SHORT x, SHORT y, char index)
{
    if (x >= 0 && y >= 0 &&
        x <= MAP_W && y <= MAP_H)
    {
        map[y][x] = index;
        return true;
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

COORD GetRandomByMap()
{
    COORD xy = { xy.X = 0,xy.Y = 0 };
    return xy;
}
