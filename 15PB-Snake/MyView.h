#pragma once

#include <iostream>
#include <windows.h>
#include <random>
#include "CFood.h"




using std::cout; using std::endl; using std::ends;
using std::default_random_engine;
using std::uniform_real_distribution;

typedef unsigned short ushort;
typedef unsigned char ubool;

//�����ͼ����
#define MAP_W 30
#define MAP_H 27
#define APPLE_NUM 10

//���巽���
#define KUp 72
#define KLeft 75
#define KRight 77
#define KDown 80

//�����ͼ����
#define MAPSHead 'H'
#define MAPSBody 'B'
#define MAPPASS  'P'
#define MAPFOOD1 '1'
#define MAPFOOD2 '2'
#define MAPFOOD3 '3'

//�����ʵ����
#define FOODSWALL 1
#define FOODSNULL 2
#define FOODSHEAD 3
#define FOODSBODY 4
#define FOODSERR  8
#define FOODSPASS 9

//������Ϸ״̬
#define GAMEWALL 'a'
#define GAMEOVER "��Ϸ����"
#define OVERWALL 0

//�����ͼ�е�����
const char INFOFoods[][3] = { "��","��","  " ,"��","��","��","��","��" ,"��","�I"};
const char INFOGames[][42] = { "���Ѿ�ײǽ�ˣ���Ϸ��������ESC������һ�㣡" };
const char INFODifficu[][5] = { {'5','1','2','2'},{'5','2','2','1'},{'7','2','1','0'} };

#define �� 0
#define ��ͨ 1
#define ���� 2

//����ȫ�ֱ���
extern char map[MAP_H][MAP_W];                  //ȫ�ֵ�ͼ
extern HANDLE gOUTPUT;                          //����������

//��������ṹ��
typedef struct _SNKBODY {
    unsigned int i;
    unsigned short x;
    unsigned short y;
    struct _SNKBODY* NEXT;
}SNKBODY;

//�����ͼ��ӡ����
void MAPprint();

//�����ʼ��������ͼ
ubool InitView();
void   DelView();
ubool InitMap(int difficu);
void   DelMap();
ubool SetXY(SHORT x, SHORT y, char index = '\0');
ubool SetXY(SHORT x, SHORT y, const char* buff = nullptr);
ubool SetMAP(SHORT x, SHORT y, char index = '\0');
ubool GetMAP(SHORT x, SHORT y);

//�ṩ���ߺ���
COORD GetRandomByMap();