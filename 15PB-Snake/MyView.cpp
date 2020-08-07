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
    cout << " ��Ϸʱ����\n";
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
        switch (i) {                            //��������
        case 0:                                 //��0�����ʱ��
            end_time = GetTickCount() - start_time;
            second = end_time / 1000;
            cout << INFOFoods[FOODSWALL] << ' ' //���ʱ��
                << std::setfill('0') << std::setw(2) 
                << (int)second / 60 << ':' 
                << std::setfill('0') << std::setw(2)
                << second % 60 << '\n'; break;
        case 2:
            cout << INFOFoods[FOODSWALL] << " ���1������\n"; break;
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
    system("title ��ӭʹ��CO0Kieؼ����̰���ߡ�");
    MENUprint(1);
    return SetConsoleCursorInfo(gOUTPUT, &cursor);
}

void DelView()
{
}


ubool InitMap(int difficu)
{
    DelMap();                                       //����ʳ����
    start_time = GetTickCount();                    //������ʱ
    diff = difficu;                                 //��¼�Ѷ�
    unsigned short n = INFODifficu[difficu][0] - '0', i = 0;
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPPASS);             //���ӵ�ͼ�ϰ���
    }
    n += (INFODifficu[difficu][1] - '0');
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPFOOD1);            //���Ӣ���ʳ��
    }
    n += (INFODifficu[difficu][2] - '0');
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPFOOD2);            //���Ӣ���ʳ��
    }
    n += (INFODifficu[difficu][3] - '0');
    for (; i < n; i++)
    {
        gCFood[i] = new CFood(MAPFOOD3);            //���Ӣ���ʳ��
    }
    return true;
}
void DelMap()
{
    system("cls");
    system("color 0f");

    for (unsigned int i = 0; i < APPLE_NUM; i++)    //ѭ������ʳ����
    {
        if (gCFood[i] != nullptr) {                 //�����Ϊ�գ�������
            delete gCFood[i]; gCFood[i] = nullptr;
        }
    }
}
ubool SetXY(SHORT x, SHORT y,char index)            //�޸Ļ�����Ϣ
{
    if (index != '\0') {
        COORD xy = { xy.X = x,xy.Y = y };
        SetConsoleCursorPosition(gOUTPUT, xy);
        cout << INFOFoods[index] << flush;
        return true;
    }
    return false;
}
//�������أ��޸�������ʾ
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

ubool SetMAP(SHORT x, SHORT y, char index)          //��ֵ��ͼ��Ϣ
{
    if (x >= 0 && y >= 0 &&
        x <= MAP_W && y <= MAP_H)
    {
        map[y][x] = index;
        return true;
    }
    return false;
}

unsigned char GetMAP(SHORT x, SHORT y)              //ȡ����ͼ��Ϣ
{
    if (x >= 0 && y >= 0 &&
        x <= MAP_W && y <= MAP_H)
    {
        return map[y][x];
    }
    return '\0';
}

ubool FindFoodRef(unsigned short x, unsigned short y)   //ͨ��������ʳ����
{
    for (unsigned int i = 0; i < APPLE_NUM; i++)
    {
        if (gCFood[i] == nullptr) continue;
        if (gCFood[i]->GetX() == x && gCFood[i]->GetY() == y)
        {
            gCFood[i]->Refresh();                       //��ˢ������
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
