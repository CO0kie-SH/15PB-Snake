#include "MyView.h"
char map[MAP_H][MAP_W];
void MAPprint()
{
    unsigned short i = MAP_W + 2, tmp, j = 0;
    while (i-- > 0)
        cout << INFOApple[0];
    cout << " ÓÎÏ·Ê±³¤£º\n";
    for (i = 0; i < MAP_H; i++)
    {
        cout << INFOApple[0];
        for (j = 0; j < MAP_W; j++)
        {
            switch (map[i][j]) {
            case MAPSHead:  tmp = 2; break;
            case MAPSBody:  tmp = 3; break;
            default:        tmp = 1; break;
            }
            cout << INFOApple[tmp];
        }
        
        switch (i)
        {
        case 0:
            cout << INFOApple[0] << " 00:00" << "\n";
            break;
        default:
            cout << INFOApple[0] << "\n";
            break;
        }
    }
    for (i = MAP_W + 2; i > 0; --i)
        cout << INFOApple[0];
    cout << endl;
}