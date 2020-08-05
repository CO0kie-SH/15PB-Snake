#pragma once
#include <iostream>
using namespace std;


#define MAP_W 30
#define MAP_H 25
#define KUp 72
#define KUp 72
#define KLeft 75
#define KRight 77
#define KDown 80
#define MAPSHead 'A'
#define MAPSBody 'B'

#define GAMEWALL 'a'

const char INFOApple[][3] = { "¡ù","¡¡" ,"¡ô","¡ó","¢Ù","¢Ú","¢Û" };
const char INFOGames[][20] = { "ÄãÒÑ¾­×²Ç½ÁË£¡" };
extern char map[MAP_H][MAP_W];

typedef struct _SNKBODY {
    unsigned int i;
    unsigned short x;
    unsigned short y;
    struct _SNKBODY* NEXT;
}SNKBODY;


void MAPprint();