#include "Base.h"
bool isValid(int x,int y)
{
return x>=0&&y>=0&&x<MAPSIZE&&y<MAPSIZE&&cell[x][y].valid;
}

int  getDist(int x1,int y1,int x2,int y2)
{
return abs(x1-x2)+abs(y1-y2);
}

bool S::isinberth(int x,int y,int id)
{
    return x>=berth[id].x&&y>=berth[id].y&&x<berth[id].x+4&&y<berth[id].y+4;
}
