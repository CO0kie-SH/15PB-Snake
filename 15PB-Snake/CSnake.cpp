#include "CSnake.h"

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
    this->Refresh();
}

CSnake::~CSnake()
{
    delete this->body;
}

void CSnake::Refresh(unsigned char cOrientation, bool IsPrint)
{
    if (this->orientation > 'Z') {              //判断蛇的状态
        cout << INFOGames[this->orientation - 'a'] << endl;
        return;
    }
    if (cOrientation != '\0') {                 //如果非默认值，则调用Set
        if (this->SetOrientation(cOrientation)) //如果是反方向，则返回
            return;
    }
    //—————————分割线—————————//开始判断移动后的数据
    int x2, y2;                                 //申请移动后的坐标
    switch (this->orientation) {                //判断蛇方向
    case 'W':
        if (this->y == 0) {                     //如果当前为上边界，则撞墙
            this->GameOver(GAMEWALL);
        }
        x2 = this->x; y2 = this->y - 1; break;  //向↑移动>>>y-1
    case 'A':
        if (this->x == 0) {                     //如果当前为左边界，则撞墙
            this->GameOver(GAMEWALL);
        }
        x2 = this->x - 1; y2 = this->y; break;  //向←移动>>>x-1
    case 'S':
        x2 = this->x; y2 = this->y + 1; break;  //向↓移动>>>y+1
    case 'D':
        x2 = this->x + 1; y2 = this->y; break;  //向→移动>>>x+1
    default:
        x2 = this->x; y2 = this->y; break;
    }

    if (x2 >= MAP_W || y2 >= MAP_H) {           //如果超出边界，则撞墙
        this->GameOver(GAMEWALL);
        return;
    }
    if (this->orientation > 'Z') return;        //再次判断蛇的状态

    //—————————分割线—————————//开始移动蛇身
    SNKBODY* tmp = this->body;                  //初始化链表循环
    while (tmp->NEXT != nullptr) {              //循环链表，将地图清空
        tmp = tmp->NEXT;                        //跳过链表头并循环
        map[tmp->y][tmp->x] = '\0';             //将地图数组赋值0
        if (tmp->i == this->bodylen - 1)
            this->bodyEND = tmp;                //并且将尾赋值给END
    }
    if (GetMAP(x2, y2)!= MAPSHead) {
        tmp->x = this->x; tmp->y = this->y;     //将蛇尾移动至蛇头
        tmp->NEXT = this->body->NEXT;           //重定义蛇体
        this->body->NEXT = tmp;                 //重定义链表
        this->bodyEND->NEXT = nullptr;          //重定义链表尾
    }
    this->x = x2; this->y = y2;                 //将判断过后的坐标赋给蛇头
    SetMAP(this->x, this->y, MAPSHead);         //画蛇头
    tmp = this->body; this->bodylen = 0;        //初始化链表
    while (tmp->NEXT != nullptr) {              //循环链表，将地图赋值
        tmp = tmp->NEXT;
        tmp->i = ++this->bodylen;               //重新计算蛇身长
        map[tmp->y][tmp->x] = MAPSBody;         //将数组赋值
    }
    if (IsPrint) MAPprint();                    //传入是否打印参数
}

bool CSnake::SetOrientation(unsigned char cOrientatio)
{
    bool is = false;                            //初始化参数
    switch (cOrientatio)                        //判断传入的方向
    {
    case 'W':                                   //如果反方向则返回
        is = this->orientation == 'S'; break;
    case 'A':
        is = this->orientation == 'D'; break;
    case 'S':
        is = this->orientation == 'W'; break;
    case 'D':
        is = this->orientation == 'A'; break;
    }
    if (!is) this->orientation = cOrientatio;
    return is;
}

void CSnake::GameOver(unsigned char cOrientatio)
{
    switch (cOrientatio)
    {
    case GAMEWALL:
        system("color 4f");
        /*SetXY(1, 1, FOODSERR);
        SetXY(MAP_W / 2 - 6, MAP_H / 2, GAMEOVER);*/
        //cout << INFOGames[GAMEWALL - 'a'] << endl; break;
    default:
        break;
    }
}
