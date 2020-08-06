#include "CSnake.h"

CSnake::CSnake()
{
    cout << "ʵ����CSnake" << endl;
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
    if (this->orientation > 'Z') {              //�ж��ߵ�״̬
        cout << INFOGames[this->orientation - 'a'] << endl;
        return;
    }
    if (cOrientation != '\0') {                 //�����Ĭ��ֵ�������Set
        if (this->SetOrientation(cOrientation)) //����Ƿ������򷵻�
            return;
    }
    //�������������������ָ��ߡ�����������������//��ʼ�ж��ƶ��������
    int x2, y2;                                 //�����ƶ��������
    switch (this->orientation) {                //�ж��߷���
    case 'W':
        if (this->y == 0) {                     //�����ǰΪ�ϱ߽磬��ײǽ
            this->GameOver(GAMEWALL);
        }
        x2 = this->x; y2 = this->y - 1; break;  //����ƶ�>>>y-1
    case 'A':
        if (this->x == 0) {                     //�����ǰΪ��߽磬��ײǽ
            this->GameOver(GAMEWALL);
        }
        x2 = this->x - 1; y2 = this->y; break;  //����ƶ�>>>x-1
    case 'S':
        x2 = this->x; y2 = this->y + 1; break;  //����ƶ�>>>y+1
    case 'D':
        x2 = this->x + 1; y2 = this->y; break;  //����ƶ�>>>x+1
    default:
        x2 = this->x; y2 = this->y; break;
    }

    if (x2 >= MAP_W || y2 >= MAP_H) {           //��������߽磬��ײǽ
        this->GameOver(GAMEWALL);
        return;
    }
    if (this->orientation > 'Z') return;        //�ٴ��ж��ߵ�״̬

    //�������������������ָ��ߡ�����������������//��ʼ�ƶ�����
    SNKBODY* tmp = this->body;                  //��ʼ������ѭ��
    while (tmp->NEXT != nullptr) {              //ѭ����������ͼ���
        tmp = tmp->NEXT;                        //��������ͷ��ѭ��
        map[tmp->y][tmp->x] = '\0';             //����ͼ���鸳ֵ0
        if (tmp->i == this->bodylen - 1)
            this->bodyEND = tmp;                //���ҽ�β��ֵ��END
    }
    if (GetMAP(x2, y2)!= MAPSHead) {
        tmp->x = this->x; tmp->y = this->y;     //����β�ƶ�����ͷ
        tmp->NEXT = this->body->NEXT;           //�ض�������
        this->body->NEXT = tmp;                 //�ض�������
        this->bodyEND->NEXT = nullptr;          //�ض�������β
    }
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
