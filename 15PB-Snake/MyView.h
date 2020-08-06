#pragma once

#include <iostream>
#include <windows.h>
#include "CFood.h"
using namespace std;

typedef unsigned short ushort;
typedef unsigned char ubool;

//定义地图长宽
#define MAP_W 30
#define MAP_H 27

//定义方向键
#define KUp 72
#define KLeft 75
#define KRight 77
#define KDown 80

//定义地图索引
#define MAPSHead 'H'
#define MAPSBody 'B'
#define MAPPASS  'P'
#define MAPFOOD1 '1'
#define MAPFOOD2 '2'
#define MAPFOOD3 '3'

//定义果实索引
#define FOODSWALL 1
#define FOODSNULL 2
#define FOODSHEAD 3
#define FOODSBODY 4
#define FOODSERR  8
#define FOODSPASS 9

//定义游戏状态
#define GAMEWALL 'a'
#define GAMEOVER "游戏结束"
#define OVERWALL 0

//定义地图中的内容
const char INFOFoods[][3] = { "空","※","　" ,"◆","◇","①","②","③" ,"×","㊣"};
const char INFOGames[][42] = { "你已经撞墙了！游戏结束！按ESC返回上一层！" };

//定义全局map、OutPut句柄
extern char map[MAP_H][MAP_W];
extern HANDLE gOUTPUT;
extern CFood* gCFood[10];

//定义蛇身结构体
typedef struct _SNKBODY {
    unsigned int i;
    unsigned short x;
    unsigned short y;
    struct _SNKBODY* NEXT;
}SNKBODY;

//定义地图打印函数
void MAPprint();

//定义初始化程序视图
ubool InitView();
ubool InitMap();
ubool SetXY(SHORT x, SHORT y, char index = '\0');
ubool SetXY(SHORT x, SHORT y, const char* buff = nullptr);
ubool SetMAP(SHORT x, SHORT y, char index = '\0');
ubool GetMAP(SHORT x, SHORT y);