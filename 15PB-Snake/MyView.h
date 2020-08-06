#pragma once

#include <iostream>
#include <windows.h>
#include <random>
#include "CFood.h"

using std::cout; using std::endl; using std::flush;

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
#define FOODS1    5
#define FOODS2    6
#define FOODS3    7

//������Ϸ״̬
#define GAMEWALL 'w'
#define GAMEPASS 'p'
#define GAMEBODY 'b'
#define GAMEOVER "��Ϸ����"
#define OVERWALL 0
#define OVERPASS 1
#define OVERBODY 2

//�����ͼ�е�����
const char INFOFoods[][3] = { "��","��","  " ,"��","��","��","��","��" ,"��","��"};
const char INFOGames[][25] = { "ײ��ǽ�ˣ�������Ϸ������","ײ���ϰ����Ϸ������" ,"ײ���Լ�����Ϸ������" };
const char INFOMenu[][29] = {
    {"��ӭʹ��CO0Kieؼ����̰���ߡ�"},
    {"�ٵ�����Ϸ"},
    {"��˫����Ϸ"},
    {"�۶�ȡ��Ϸ"},
    {"�ܱ༭��ͼ"},
    {"�� �� ��"}
};
const char INFODifficu[][5] = { {'5','1','2','2'},{'5','2','2','1'},{'7','2','1','0'} };

#define �� 0
#define ��ͨ 1
#define ���� 2
#define ������Ϸ 1
#define ˫����Ϸ 2
#define �˳� 5

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
//��ӡ�˵�
void MENUprint(int index);

//�����ʼ��������ͼ
BOOL InitView();
void   DelView();
ubool InitMap(int difficu);
void   DelMap();
ubool SetXY(SHORT x, SHORT y, char index = '\0');
ubool SetXY(SHORT x, SHORT y, const char* buff = nullptr, WORD color = NULL);
ubool SetMAP(SHORT x, SHORT y, char index = '\0');
ubool GetMAP(SHORT x, SHORT y);

//ʳ�����
ubool FindFoodRef(unsigned short x, unsigned short y);

//�ṩ���ߺ���=>ȡ����ͼ�ڵĿհ�����
ubool GetRandomByMap(COORD& xy, unsigned int minx = 0, unsigned int miny = 0);
void SetScore(unsigned int iscore);