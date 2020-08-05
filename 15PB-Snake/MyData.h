#pragma once


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


typedef struct _SNKBODY {
    unsigned int i;
    unsigned short x;
    unsigned short y;
    struct _SNKBODY* NEXT;
    struct _SNKBODY* PREV;
}SNKBODY;
