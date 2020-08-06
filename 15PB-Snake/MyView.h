#pragma once

#include <iostream>
#include <windows.h>
using namespace std;

typedef unsigned short ushort;
typedef unsigned char ubool;

//�����ͼ����
#define MAP_W 30
#define MAP_H 27

//���巽���
#define KUp 72
#define KLeft 75
#define KRight 77
#define KDown 80

//�����ͼ����
#define MAPSHead 'A'
#define MAPSBody 'B'

//�����ʵ����
#define FOODSWALL 1
#define FOODSNULL 2
#define FOODSHEAD 3
#define FOODSBODY 4
#define FOODSERR  8

//������Ϸ״̬
#define GAMEWALL 'a'
#define GAMEOVER "��Ϸ����"

const char INFOFoods[][3] = { "��","��","��" ,"��","��","��","��","��" ,"��"};
const char INFOGames[][20] = { "���Ѿ�ײǽ�ˣ�" };
extern char map[MAP_H][MAP_W];
extern HANDLE gOUTPUT;

typedef struct _SNKBODY {
    unsigned int i;
    unsigned short x;
    unsigned short y;
    struct _SNKBODY* NEXT;
}SNKBODY;


void MAPprint();
ubool InitView();
ubool SetXY(SHORT x, SHORT y, char index = '\0');
ubool SetXY(SHORT x, SHORT y, const char* buff = nullptr);
ubool SetMAP(SHORT x, SHORT y, char index = '\0');
ubool GetMAP(SHORT x, SHORT y);