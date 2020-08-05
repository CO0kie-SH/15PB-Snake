/*  15PB-Snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
    IDE     :   Visual_Studio_2019
    Time    :   20200803-20:00
    By      :   Hongwei.Mao
    Coding  :   UTF-8
    Ver     :   V1.0
*/
//本项目开源地址 https://github.com/mhw666/15PB-Snake 本文件开源地址：
//https://github.com/mhw666/15PB-Snake/blob/master/15PB-Snake/15PB-Snake.cpp


#include <iostream>
#include <windows.h>
#include <conio.h>

#define KEY_DOWN(key) (GetAsyncKeyState(key) == (short)0x8001) ? 1 : 0
#define MAP_W 20
#define MAP_H 3
#define KUp 72
#define KUp 72
#define KLeft 75
#define KRight 77;
#define KDown 80
#define SHead 'A'
#define SBody 'B'
using namespace std;

const char apple[][3] = {"※","　" ,"◆","◇","①","②","③" };
static char map[MAP_H][MAP_W] = { 0 };

typedef struct _SNKBODY {
    unsigned short x;
    unsigned short y;
    struct _SNKBODY* NEXT;
}SNKBODY;

class CSnake
{
public:
    CSnake();
    ~CSnake();

private:
    unsigned short x;
    unsigned short y;
    SNKBODY* body;
};

CSnake::CSnake()
{
    this->x = 2;
    this->y = 0;
    this->body = new SNKBODY;
    this->body->NEXT = nullptr;
}

CSnake::~CSnake()
{
    delete body;
}


void MAPprint()
{
    cout << apple[0]<<endl;
    for (unsigned short i = 0, tmp = 0; i < MAP_H; i++)
    {
        cout << apple[0];
        for (unsigned short j = 0; j < MAP_W; j++)
        {
            switch (map[i][j]){
            case SHead: tmp = 2; break;
            case SBody: tmp = 3; break;
            default:    tmp = 1; break;}
            cout << apple[tmp];
        }   cout << apple[0] << endl;
    }
    cout << apple[0] << endl;
}

int main()
{
    std::cout << "Hello World!\n";
    int key=0;
    CSnake cSnke;
    MAPprint();
    while (key!=27)
    {
        key = _getch();
        switch (key)
        {
        case KLeft:case 65:case 97:
            //std::cout << "左\n";
            map[1][10] = 'B';
            map[1][9] = 'A';
            MAPprint();
            break;
        default:
            std::cout << "键码\t"<<key << std::endl;
            break;
        }
    }
}
