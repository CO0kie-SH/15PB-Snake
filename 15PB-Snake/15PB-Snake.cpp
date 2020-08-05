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
#define KRight 77
#define KDown 80
#define MAPSHead 'A'
#define MAPSBody 'B'
using namespace std;

const char apple[][3] = {"※","　" ,"◆","◇","①","②","③" };
static char map[MAP_H][MAP_W] = { 0 };

typedef struct _SNKBODY {
    unsigned int i;
    unsigned short x;
    unsigned short y;
    struct _SNKBODY* NEXT;
    struct _SNKBODY* PREV;
}SNKBODY;

class CSnake
{
public:
    CSnake();
    ~CSnake();
    void CRefresh(char cOrientatio = '\0', bool IsPrint = false);

private:
    unsigned short x;
    unsigned short y;
    unsigned char orientation;
    unsigned int bodylen;
    SNKBODY* body;
    SNKBODY* bodyEND;
};

CSnake::CSnake()
{
    cout << "实例化CSnake" << endl;
    this->x = 2;
    this->y = 0;
    this->bodylen = 2;
    this->orientation = 'D';
    this->body = new SNKBODY;
    SNKBODY* tmp = new SNKBODY;
    tmp->NEXT = nullptr;
    tmp->x = 1;
    tmp->y = 0;
    tmp->i = 1;
    this->body->NEXT = tmp;
    tmp = new SNKBODY;
    tmp->NEXT = nullptr;
    tmp->x = 0;
    tmp->y = 0;
    tmp->i = 2;
    this->body->NEXT->NEXT = tmp;
    this->CRefresh();
}

CSnake::~CSnake()
{
    delete this->body;
}

void CSnake::CRefresh(char cOrientation,bool IsPrint)
{
    int x2, y2;                                 //申请移动后的坐标
    switch (cOrientation)
    {
    case 'W':
        if (this->orientation != 'S')
            this->orientation = cOrientation;
        break;
    }
    x2 = this->x + 1; y2 = this->y;
    if (x2 >= MAP_W || y2 >= MAP_H) {           //超出地图边界
        cout << "撞墙啦！" << endl;
        return;
    }
    switch (this->orientation) {
    default:break;
    }
    SNKBODY* tmp = this->body;                  //初始化链表循环
    while (tmp->NEXT != nullptr) {              //循环链表，将地图清空
        tmp = tmp->NEXT;                        //跳过链表头并循环
        map[tmp->y][tmp->x] = '0';              //将地图数组赋值0
        if (tmp->i == this->bodylen - 1)
            this->bodyEND = tmp;                //并且将尾赋值给END
    }
    if (map[y2][x2] != '1') {
        tmp->x = this->x; tmp->y = this->y;     //将蛇尾移动至蛇头
        tmp->NEXT = this->body->NEXT;           //重定义蛇体
        this->body->NEXT = tmp;                 //重定义链表
        this->bodyEND->NEXT = nullptr;          //重定义链表尾
    }
    map[this->y][this->x] = MAPSHead;           //画蛇头
    tmp = this->body; this->bodylen = 0;        //初始化链表
    while (tmp->NEXT != nullptr) {              //循环链表，将地图赋值
        tmp = tmp->NEXT;
        tmp->i = ++this->bodylen;               //重新计算蛇身长
        map[tmp->y][tmp->x] = MAPSBody;         //将数组赋值
    }
    //if (IsPrint) ::MAPprint();                    //传入是否打印参数
}


void MAPprint()
{
    unsigned short i = MAP_W + 2, tmp, j = 0;
    while (i-->0)
        cout << apple[0];
    cout << "\n";
    for (i=0; i < MAP_H; i++)
    {
        cout << apple[0];
        for (j = 0; j < MAP_W; j++)
        {
            switch (map[i][j]){
            case MAPSHead: tmp = 2; break;
            case MAPSBody: tmp = 3; break;
            default:    tmp = 1; break;}
            cout << apple[tmp];
        }   cout << apple[0] << "\n";
    }
    for (i = MAP_W + 2; i > 0; --i)
        cout << apple[0];
    cout << endl;
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
            MAPprint();break;
        case KRight:
            cSnke.CRefresh('D', true); MAPprint(); break;
        case 224:break;
        default:
            std::cout << "键码\t"<<key << std::endl;
            break;
        }
    }
}
