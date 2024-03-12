//
// Created by stx on 2024/3/10.
//

#include "update.h"

//‘.’ ： 空地
//‘*’ ： 海洋
//‘#’ ： 障碍
//‘A’ ： 机器人起始位置，总共 10 个。
//‘B’ ： 大小为 4*4，表示泊位的位置,泊位标号在后泊位处初始化。
//
void init() // 读入，初始化，//轮船泊点初始化
{
    for (int i = 0; i < MAPSIZE; i++) {
        scanf("%s", cache);
        for (int j = 0; j < MAPSIZE; j++) {
            cell[i][j].valid = (cache[j] == '.' || cache[j] == 'A' || cache[j] == 'B');
            cell[i][j].robot = (cache[j] == 'A');
            cell[i][j].park = (cache[j] == 'B');
        }
    }
    int id=0;
    for (int  i = 0; i < 10; i++) {
        scanf("%d%d%d%d%d", &id, &berth[i].x, &berth[i].y, &berth[i].transport_time, &berth[i].loading_speed);
    }
    scanf("%d", &boat_capacity);
    scanf("%s",cache);//OK
    puts("OK");
    for (int i = 0; i < BOATNUM; i++) {
        int Imin = INT_MAX, tag[BERTHNUM], choice = 0;
        for (int j = 0; j < BERTHNUM; j++)
            if (tag[j] == 0 && berth[j].transport_time < Imin) {
                Imin = berth[j].transport_time;
                choice = j;
            }
        boat[i].target = choice;
        boat[i].state=1;//
        berth[choice].state = 2;
        berth[choice].arrival_time = Imin;
        tag[choice] = 1;
    }
    // 初始船队分配,最快到泊位原则
    //输出指令，这个应该放到第一帧交互里
    puts("OK");
    //fflush(stdout);
}

void frameIn() // 读入，
{
    int K;
    scanf("%d%d%d", &frame, &money, &K);
    Item new_item;
    for (int i = 1; i <= K; i++) {
        scanf("%d%d", &new_item.x, &new_item.y);
        new_item.time = frame;
        scanf("%d", &new_item.value);
        cell[new_item.x][new_item.y].place(frame, new_item.value);
        item_list.push_back(new_item);
    }//物品生成
    for (int i = 0; i < ROBOTNUM; i++) {
        int state_item, x, y, state_run;
        scanf("%d%d%d%d", &state_item, &x, &y, &state_run);
        robot[i].update(state_item, x, y, state_run);
    }
    for (int i = 0; i < BOATNUM; i++) {
        int state, berth_id;
        scanf("%d%d", &state, &berth_id);
        boat[i].update(state, berth_id);
    }//同步
    scanf("%s", cache);
    robotControl();//路径更新

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {

        }//机器人下一步更新
}

void error() {
    //错误处理
}

void process() {
    robotControl();
}

void frameOut() // 输出
{
    for (int i = 0; i < ROBOTNUM; i++) {
        if (robot[i].d != -1)
            printf("move %d %d\n", i, robot[i].d);
        if (robot[i].op == 1)
            printf("get %d\n", i);
        else if (robot[i].op == 2)
            printf("pull %d\n", i);
    }
    for (int i = 0; i < BOATNUM; i++)
        if (boat[i].op) {
            if (boat[i].target == -1)
                printf("go %d\n", i);
            else printf("ship %d %d\n", i, boat[i].target);
        }
    puts("OK");
    fflush(stdout);
}
