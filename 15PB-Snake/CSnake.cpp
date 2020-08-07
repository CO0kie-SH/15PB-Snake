#include "CSnake.h"

CSnake::CSnake(unsigned short y)
{
    cout << "ʵ����CSnake��" << y << endl;
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
    if (!this->alive) return;                   //��������򷵻�
    if (cOrientation != '\0') {                 //�����Ĭ��ֵ�������Set
        if (this->SetOrientation(cOrientation)) //����Ƿ������򷵻�
            return;
    }
    //�������������������ָ��ߡ�����������������//��ʼ�ж��ƶ��������
    SHORT x2 = 0, y2 = 0;
    switch (this->orientation) {                //�ж��߷���
    case 'W':
        if (this->y == 0) {                     //�����ǰΪ�ϱ߽磬��ײǽ
            this->GameOver(GAMEWALL); break;
        }
        x2 = this->x; y2 = this->y - 1; break;  //����ƶ�>>>y-1
    case 'A':
        if (this->x == 0) {                     //�����ǰΪ��߽磬��ײǽ
            this->GameOver(GAMEWALL); break;
        }
        x2 = this->x - 1; y2 = this->y; break;  //����ƶ�>>>x-1
    case 'S':
        x2 = this->x; y2 = this->y + 1; break;  //����ƶ�>>>y+1
    case 'D':
        x2 = this->x + 1; y2 = this->y; break;  //����ƶ�>>>x+1
    default:
        x2 = this->x; y2 = this->y; break;
    }
    //�������������������ָ��ߡ�����������������//�ж�Խ��
    if (x2 >= MAP_W || y2 >= MAP_H) {           //��������߽磬��ײǽ
        this->GameOver(GAMEWALL);
        return;
    }
    if (this->orientation > 'Z') return;        //�ٴ��ж��ߵ�״̬
    //�������������������ָ��ߡ�����������������//��յ�ͼ
    SNKBODY* tmp = this->body;                  //��ʼ������ѭ��
    while (tmp->NEXT != nullptr) {              //ѭ����������ͼ���
        tmp = tmp->NEXT;                        //��������ͷ��ѭ��
        if (tmp->i == this->bodylen - 1)
            this->bodyEND = tmp;                //���ҽ���β��ֵ��END
    }
    //�������������������ָ��ߡ�����������������//��ʼ�ƶ�����
    switch (GetMAP(x2, y2))                     //����ͼ����
    {
    case MAPSHead:
        break;
    case MAPSBody:
        GameOver(GAMEBODY); return; break;
    case MAPPASS:                               //�����ϰ���
        GameOver(GAMEPASS); return; break;
    case MAPFOOD3:                              //������ʵ
        this->addlen += 9;  this->score += 10;  //�ӷ֣��ӳ���
    case MAPFOOD2:
        this->addlen += 1;  this->score += 10;
    case MAPFOOD1:
        this->addlen += 1;  this->score += 10;
        SetScore(this->score);
        FindFoodRef(x2, y2); break;
    default:
        break;
    }
    //�������������������ָ��ߡ�����������������//�ж���ͷ������
    if (this->addlen > 0)                       //�ж��೤���򳤴�
    {
        this->addlen--;                         //�Լ��೤
        tmp = new SNKBODY;                      //�½��ṹ�壬��ʾ����
    }
    else {                                      //������೤�����ƶ�
        tmp = this->bodyEND->NEXT;
        map[tmp->y][tmp->x] = '\0';             //����ͼ���鸳ֵ0
        this->bodyEND->NEXT = nullptr;          //�ض�������β
    }
    tmp->x = this->x; tmp->y = this->y;         //����ͷ����ָ��
    tmp->NEXT = this->body->NEXT;               //�ض�������
    this->body->NEXT = tmp;                     //�ض�������
    //�������������������ָ��ߡ�����������������//�ƶ��ɹ�������ͼ
    this->x = x2; this->y = y2;                 //���жϹ�������긳����ͷ
    SetMAP(this->x, this->y, MAPSHead);         //����ͷ
    tmp = this->body; this->bodylen = 0;        //��ʼ������
    while (tmp->NEXT != nullptr) {              //ѭ����������ͼ��ֵ
        tmp = tmp->NEXT;
        tmp->i = ++this->bodylen;               //���¼�������
        map[tmp->y][tmp->x] = MAPSBody;         //�����鸳ֵ
    }
    if (IsPrint) MAPprint();                    //�����Ƿ��ӡ����
}

bool CSnake::SetOrientation(unsigned char cOrientatio)
{
    bool is = false;                            //��ʼ������
    switch (cOrientatio)                        //�жϴ���ķ���
    {
    case 'W':                                   //����������򷵻�
        is = this->orientation == 'S'; break;
    case 'A':
        is = this->orientation == 'D'; break;
    case 'S':
        is = this->orientation == 'W'; break;
    case 'D':
        is = this->orientation == 'A'; break;
    }
    if (!is) this->orientation = cOrientatio;   //������Ƿ�������ֵ
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
    SetXY(MAP_W * 2 + 6, MAP_H + 1, "��ESC������һ�㣡");
    system("color 4f");
}
