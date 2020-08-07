#include "CSnake.h"

CSnake::CSnake(unsigned short y)
{
    cout << "实例化CSnake：" << y << endl;
    this->addlen = 0; this->score = 0;
    this->x = 2; this->y = y;
    this->bodyEND = nullptr;
    this->alive = 1;
    this->bodylen = 2;
    this->orientation = 'D';
    this->body = new SNKBODY;
    SNKBODY* tmp = new SNKBODY;
    tmp->NEXT = nullptr;
    tmp->x = 1; tmp->y = y; tmp->i = 1;
    this->body->NEXT = tmp;
    tmp = new SNKBODY;
    tmp->NEXT = nullptr;
    tmp->x = 0; tmp->y = y; tmp->i = 2;
    this->body->NEXT->NEXT = tmp;
    //this->Refresh();
}

CSnake::~CSnake()
{
    delete this->body;
}

void CSnake::Refresh(unsigned char cOrientation, bool IsPrint)
{
    if (!this->alive) return;                   //如果死亡则返回
    if (cOrientation != '\0') {                 //如果非默认值，则调用Set
        if (this->SetOrientation(cOrientation)) //如果是反方向，则返回
            return;
    }
    //—————————分割线—————————//开始判断移动后的数据
    SHORT x2 = 0, y2 = 0;
    switch (this->orientation) {                //判断蛇方向
    case 'W':
        if (this->y == 0) {                     //如果当前为上边界，则撞墙
            this->GameOver(GAMEWALL); break;
        }
        x2 = this->x; y2 = this->y - 1; break;  //向↑移动>>>y-1
    case 'A':
        if (this->x == 0) {                     //如果当前为左边界，则撞墙
            this->GameOver(GAMEWALL); break;
        }
        x2 = this->x - 1; y2 = this->y; break;  //向←移动>>>x-1
    case 'S':
        x2 = this->x; y2 = this->y + 1; break;  //向↓移动>>>y+1
    case 'D':
        x2 = this->x + 1; y2 = this->y; break;  //向→移动>>>x+1
    default:
        x2 = this->x; y2 = this->y; break;
    }
    //—————————分割线—————————//判断越界
    if (x2 >= MAP_W || y2 >= MAP_H) {           //如果超出边界，则撞墙
        this->GameOver(GAMEWALL);
        return;
    }
    if (this->orientation > 'Z') return;        //再次判断蛇的状态
    //—————————分割线—————————//清空地图
    SNKBODY* tmp = this->body;                  //初始化链表循环
    while (tmp->NEXT != nullptr) {              //循环链表，将地图清空
        tmp = tmp->NEXT;                        //跳过链表头并循环
        if (tmp->i == this->bodylen - 1)
            this->bodyEND = tmp;                //并且将蛇尾赋值给END
    }
    //—————————分割线—————————//开始移动蛇身
    switch (GetMAP(x2, y2))                     //检测地图坐标
    {
    case MAPSHead:
        break;
    case MAPSBody:
        GameOver(GAMEBODY); return; break;
    case MAPPASS:                               //遇到障碍物
        GameOver(GAMEPASS); return; break;
    case MAPFOOD3:                              //遇到果实
        this->addlen += 9;  this->score += 10;  //加分，加长度
    case MAPFOOD2:
        this->addlen += 1;  this->score += 10;
    case MAPFOOD1:
        this->addlen += 1;  this->score += 10;
        SetScore(this->score);
        FindFoodRef(x2, y2); break;
    default:
        break;
    }
    //—————————分割线—————————//判断蛇头结束。
    if (this->addlen > 0)                       //判断余长，则长大
    {
        this->addlen--;                         //自减余长
        tmp = new SNKBODY;                      //新建结构体，表示长大
    }
    else {                                      //如果无余长，则移动
        tmp = this->bodyEND->NEXT;
        map[tmp->y][tmp->x] = '\0';             //将地图数组赋值0
        this->bodyEND->NEXT = nullptr;          //重定义链表尾
    }
    tmp->x = this->x; tmp->y = this->y;         //将蛇头赋给指针
    tmp->NEXT = this->body->NEXT;               //重定义蛇体
    this->body->NEXT = tmp;                     //重定义链表
    //—————————分割线—————————//移动成功，画地图
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
    if (!is) this->orientation = cOrientatio;   //如果不是反方向，则赋值
    return is;
}



void CSnake::GameOver(unsigned char cOrientation)
{
    int index = 0;
    SetXY(2 + (2 * this->x), 1 + this->y, FOODSERR);
    this->alive--; this->orientation = cOrientation;
    switch (cOrientation)
    {
    case GAMEWALL:
        index = OVERWALL; break;
    case GAMEPASS:
        index = OVERPASS; break;
    case GAMEBODY:
        index = OVERBODY; break;
    default:
        break;
    }
    SetXY(MAP_W * 2 + 6, MAP_H, INFOGames[index]);
    SetXY(MAP_W * 2 + 6, MAP_H + 1, "按ESC返回上一层！");
    system("color 4f");
}
