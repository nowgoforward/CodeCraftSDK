#ifndef CODECRAFTSDK_BASE_H
#define CODECRAFTSDK_BASE_H


#ifndef HUAWEI_BASE_H
#define HUAWEI_BASE_H
#include <iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include<string>
#include<cstring>
#include<stack>
#include<queue>
#include<cmath>
#include<fstream>
#include<bitset>
#include<ctime>
#include<deque>
#include<functional>
#include<list>
#include<numeric>
#include<cassert>
#include<algorithm>
#include<sstream>
#include<iomanip>
using namespace std;

bool isValid(int x,int y);

int  getDist(int x1,int y1,int x2,int y2);

namespace S
{
    const int REMAIN_TIME=1800;
    const int robot_item_factor=5;
    const int item_berth_factor=2;
    const int value_factor=1;
    const int robot_item_dist_threshold=50;
    const int q_inf=-10000;
    const int berth_dist_inf=1000;
    struct Token
    {
        int x,y;
        int d;
        Token *last;
        Token(){}
        Token(int x,int y,int d=-1,Token*l= nullptr):x(x),y(y),d(d),last(l){}
    };
    struct CMP
    {
        static int x,y;
        static void set(int x_,int y_){x=x_;y=y_;}
        bool operator() (S::Token*a,S::Token*b)
        {
            return getDist(a->x,a->y,x,y)>getDist(b->x,b->y,x,y);
        }
    };
    bool isinberth(int x,int y,int id);
}

struct Item
{
    int time;
    int value;
    bool state;//1等待，0过期
    int x,y;
    void place(int t,int v,int x_,int y_){time=t;value=v;x=x_;y=y_;state= true;}
    void pick(){state=false;}

    //S新增的部分
    int berth_id;
    int berth_dist;
    Item():state(true),berth_id(-1),berth_dist(1000){}
    //
};

struct Cell
{
    bool valid;//是否是空地
    bool item;//是否有物体
    bool robot;//是否有机器人
    bool nxt_robot;//移动后是否有机器人
    bool park;
    int time;
    int value;
    void place(int t,int v){time=t;value=v;item= true;}
    void pick(){item=false;}
};

struct Robot
{
    int x,y;
    int aim_x,aim_y;
    int d;//方向 -1表示等待
    //机器人路径存储(vector)
    bool load; //1装，0空
    bool state; //0 表示恢复状;1 表示正常运行状态
    Item item;
    list<int>path;//总路径
    list<int>ripath;//规划出的路径(机器人到物品）
    list<int>ibpath;//物品到港口
    int berthid;
    list<int>::iterator it;
    int op;//，1表示取，2表示放，否则为0
    Robot():op(0),d(-1){}
    bool is_on_item(){return item.x==x&&item.y==y;}
    bool is_in_berth(){return S::isinberth(x,y,item.berth_id);}
    void update(int state_item, int now_x, int now_y, int state_run)
    {
        x = now_x;
        y = now_y;
        load = state_item;
        state = state_run;
    }
};

struct Berth
{
    int x,y;
    int transport_time;
    int loading_speed;
    int add;
    int boat_id;
    //考虑机器人同时达到
    int state;        // 0表示无船，1表示有船，2表示即将有船
    int arrival_time; // state=2的条件下，船达到的帧
    list<int> item_value;
};

struct Boat
{
    int target; //-1表示向虚拟点
    int aim_time;
    int state;
    int cnt; // 装载物体个数，从0开始记
    bool op; // 表示是否需要输出指令，target=-1为go指令
    void update(int state_now, int target_now)
    {
        state = state_now;
        target = target_now;
    }
    Boat() : op(false), cnt(0) {}
};


const int MAPSIZE=200;
const int ROBOTNUM=10;
const int BOATNUM=5;
const int BERTHNUM=10;
const int TimeLimit=15000;
const int TIME=2000;
extern Cell cell[MAPSIZE][MAPSIZE];
extern Robot robot[ROBOTNUM];
extern Berth berth[BERTHNUM];
extern Boat boat[BOATNUM];
extern list<Item>item_list;
extern char cache[2000];
extern int priorityRobot[ROBOTNUM+1];
extern std::ofstream logFile;
extern int boat_capacity,frame,money;//船的容量，帧，金额，
const int dir[4][2]={{0,1},{0,-1},{-1,0},{1,0}};//（x向下,y向右)

#endif

#endif //CODECRAFTSDK_BASE_H
