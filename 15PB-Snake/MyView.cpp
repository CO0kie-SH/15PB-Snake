#include "MyView.h"
#include <iomanip>
using std::default_random_engine;
using std::uniform_int_distribution;


char map[MAP_H][MAP_W];
HANDLE gOUTPUT;
CFood* gCFood[APPLE_NUM];
default_random_engine e;
unsigned int score[] = { 0,0 };
DWORD start_time;
int diff = 0;

void MAPprint(DWORD time)
{
    system("cls");
    unsigned short i = MAP_W + 2, tmp, j = 0;
    DWORD end_time, second, lay;
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
            case MAPPASS:   tmp = FOODSPASS; break;
            case MAPFOOD1:  tmp = FOODS1;    break;
            case MAPFOOD2:  tmp = FOODS2;    break;
            case MAPFOOD3:  tmp = FOODS3;    break;
            default:        tmp = FOODSNULL; break;
            }
            cout << INFOFoods[tmp];
        }
        switch (i) {                            //侧边栏输出
        case 0:                                 //第0行输出时间
            end_time = GetTickCount() - start_time;
            second = end_time / 1000;
            cout << INFOFoods[FOODSWALL] << ' ' //输出时间
                << std::setfill('0') << std::setw(2) 
                << (int)second / 60 << ':' 
                << std::setfill('0') << std::setw(2)
                << second % 60 << '\n'; break;
        case 2:
            cout << INFOFoods[FOODSWALL] << " 玩家1分数：\n"; break;
        case 3:
            cout << INFOFoods[FOODSWALL] << ' ' << score[0] << '\n'; break;
        default:
            cout << INFOFoods[FOODSWALL] << "\n";
            break;
        }
    }
    for (i = MAP_W + 2; i > 0; --i)
        cout << INFOFoods[FOODSWALL];
    cout << endl;
    lay = ((diff / 10) * 1000) + (99 - (second / 60)) * 10;
    lay = lay * (time / 10);
    Sleep(lay + 10);
}

void MENUprint(int index)
{
    system("cls");
    WORD color= NULL;
    for (int i = 0; i < 6; i++)
    {
        color = index == i ? 0x1f : 0x0f;
        SetXY(20, i + 5, INFOMenu[i],color);
    }
}
void MENUprint2(int index)
{
    system("cls");
    WORD color= NULL;
    for (int i = 0; i < 8; i++)
    {
        color = index == i ? 0x1f : 0x0f;
        SetXY(20, i + 5, INFOMenu2[i],color);
    }
}

BOOL InitView()
{
    gOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1,false };
    system("title 欢迎使用CO0Kie丶初代贪吃蛇。");
    MENUprint(1);
    return SetConsoleCursorInfo(gOUTPUT, &cursor);
}

void DelView()
{
}


ubool InitMap(int difficu)
{
    DelMap();                                       //析构食物类
    start_time = GetTickCount();                    //开启计时
    diff = difficu;                                 //记录难度
    unsigned short n = INFODifficu[difficu][0] - '0', i = 0;
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPPASS);             //增加地图障碍物
    }
    n += (INFODifficu[difficu][1] - '0');
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPFOOD1);            //增加①型食物
    }
    n += (INFODifficu[difficu][2] - '0');
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPFOOD2);            //增加②型食物
    }
    n += (INFODifficu[difficu][3] - '0');
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPFOOD3);            //增加③型食物
    }
    return true;
}
void DelMap()
{
    system("cls");
    system("color 0f");

    for (unsigned int i = 0; i < APPLE_NUM; i++)    //循环解析食物类
    {
        if (gCFood[i] != nullptr) {                 //如果不为空，则析构
            delete gCFood[i]; gCFood[i] = nullptr;
        }
    }
}
ubool SetXY(SHORT x, SHORT y,char index)            //修改画布信息
{
    if (index != '\0') {
        COORD xy = { xy.X = x,xy.Y = y };
        SetConsoleCursorPosition(gOUTPUT, xy);
        cout << INFOFoods[index] << flush;
        return true;
    }
    return false;
}
//画布重载，修改内容提示
ubool SetXY(SHORT x, SHORT y, const char* buff, WORD color)
{
    if (buff != nullptr) {
        COORD xy = { xy.X = x,xy.Y = y };
        SetConsoleCursorPosition(gOUTPUT, xy);
        if (color != NULL)
            SetConsoleTextAttribute(gOUTPUT, color);
        cout << buff << flush;
        if (color != NULL)
            SetConsoleTextAttribute(gOUTPUT, 0x0F);
        return true;
    }
    return false;
}

ubool SetMAP(SHORT x, SHORT y, char index)          //赋值地图信息
{
    if (x >= 0 && y >= 0 &&
        x <= MAP_W && y <= MAP_H)
    {
        map[y][x] = index;
        return true;
    }
    return false;
}

unsigned char GetMAP(SHORT x, SHORT y)              //取出地图信息
{
    if (x >= 0 && y >= 0 &&
        x <= MAP_W && y <= MAP_H)
    {
        return map[y][x];
    }
    return '\0';
}

ubool FindFoodRef(unsigned short x, unsigned short y)   //通过坐标找食物类
{
    for (unsigned int i = 0; i < APPLE_NUM; i++)
    {
        if (gCFood[i] == nullptr) continue;
        if (gCFood[i]->GetX() == x && gCFood[i]->GetY() == y)
        {
            gCFood[i]->Refresh();                       //并刷新坐标
            return true;
        }
    }
    return false;
}

ubool GetRandomByMap(COORD& xy, unsigned int minx, unsigned int miny)
{
    COORD tmp; char ctmp = '\0';
    for (unsigned int i = MAP_H * MAP_W; i > 0; i--)
    {
        uniform_int_distribution<unsigned> ux(minx, MAP_W-1);
        uniform_int_distribution<unsigned> uy(miny, MAP_H-1);
        tmp.X = ux(e); tmp.Y = uy(e);
        ctmp = map[tmp.Y][tmp.X];
        if (ctmp) {
            
        }
        else {
            xy.X = tmp.X; xy.Y = tmp.Y;
            return true;
        }
    }
    return false;
}

void SetScore(unsigned int iscore)
{
    score[0] = iscore;
}
