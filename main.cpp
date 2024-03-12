//100帧15个物品 （期望）
#include "update.h"
#include "util.h"

Cell cell[MAPSIZE][MAPSIZE];
Robot robot[ROBOTNUM];
Berth berth[BERTHNUM];
Boat boat[BOATNUM];
int priorityRobot[ROBOTNUM+1];
list<Item>item_list;
char cache[2000];

int boat_capacity,frame,money;//船的容量，帧，金额，

int S::CMP::x,S::CMP::y;
//‘.’ ： 空地
//‘*’ ： 海洋
//‘#’ ： 障碍
//‘A’ ： 机器人起始位置，总共 10 个。
//‘B’ ： 大小为 4*4，表示泊位的位置,泊位标号在后泊位处初始化。
//
const char logpath[100]="/Users/stx/CLionProjects/CodeCraftSDK/test/log.txt";
std::ofstream logFile(logpath, ios::out);
int main()
{

    /*if (!logFile.is_open()) {
        std::cerr << "无法打开日志文件" << std::endl;
        return -1;
    }
    logFile<<"open\n";*/
  init();
    for(int i=1;i<=TimeLimit;i++)//帧循环
    {
       frameIn();//输入时顺便更新地图
        logFile<<"Frame:"<<frame<<"\n";
       process();
       frameOut();
    }
    logFile.close();
    return 0;
}