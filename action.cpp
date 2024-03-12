#include "action.h"


/**
 * 优先级越大的机器人越先输出指令
 */
void resetPrio() {
    for (int i = 0; i < ROBOTNUM; ++i) {
        priorityRobot[i] = 0;
    }
}
//方向,-1表示等待 0表示右移一格，1表示左移一格 ，2表示上移一格 ， 3表示下移一格
//往下为X轴正方向，往右为Y轴正方向
/**
 * 两两比较，有45种情况
 * 两个机器人下一帧位置相同 / 两个机器人互换位置
 * 还要考虑一个机器人输出顺序的问题，相邻两个机器人相邻同方向前进，前面的机器人指令先输出，因此增加一个机器人指令输出优先级的数组，这个数组每一帧重置
 * 迭代器it的更新我认为应该在frameout函数中
 */
void pump()//碰撞处理,每帧都检测
{
    resetPrio();
    for (int i = 0; i < ROBOTNUM-1; ++i) {
        for (int j = i+1; j < ROBOTNUM; ++j) {
            if (pumpToEachOther(i, j)) {
                solutionToPTEO(i, j);
            } else if (pumpToSameLoc(i, j)) {
                solutionToPTSL(i, j);
            } else if (JtoILoc(i, j)) {//后一个点要占前一个点的位置，确定优先级
                priorityRobot[i] = priorityRobot[j]+1;
            } else if (JtoILoc(j, i)) {//前一个点要占后一个点的位置，确定优先级
                priorityRobot[j] = priorityRobot[i]+1;
            }
        }
    }

}

bool JtoILoc(int i, int j) {
    return robot[j].aim_x == robot[i].x && robot[j].aim_y == robot[i].y;
}

/**
 * 两个机器人下一帧位置相同
 */
void solutionToPTSL(int i, int j) {
    //i动，j停
    updateRobot(j, robot[j].x, robot[j].y, -1, -1);
    robot[i].d = *(robot[i].it);
}

/**
 * 两个机器人互换位置
 */
void solutionToPTEO(int i, int j)
{
    if (robot[i].d == -1) {
        updateRobot(j, robot[j].x, robot[j].y, -1, -1);
        return;
    } else if (robot[j].d == -1) {
        updateRobot(i, robot[i].x, robot[i].y, -1, -1);
        return;
    }
    //i往变道，j前进
    int i_x = robot[i].x;
    int i_y = robot[i].y;
    switch (robot[i].d) {
        case 0://right
            if (i_x >= 1 && cell[i_x-1][i_y].valid && !cell[i_x-1][i_y].robot) {
                //i up
                updateRobot(i, robot[i].x-1, robot[i].y, 2, 0);
                updateRbtDirect(i, 2, 3);
            } else if (i_x <= 198 && cell[i_x+1][i_y].valid && !cell[i_x+1][i_y].robot) {
                // i down
                updateRobot(i, robot[i].x+1, robot[i].y, 3, 0);
                updateRbtDirect(i, 3, 2);
            } else if (i_y >= 1 && cell[i_x][i_y-1].valid && !cell[i_x][i_y-1].robot){
                //i left
                updateRobot(i, robot[i].x, robot[i].y-1, 1, 0);
                updateRbtDirect(i, 1, 0);
            } else {
                //动不了
                updateRobot(j, robot[j].x, robot[j].y, -1, -1);
                updateRobot(i, robot[i].x, robot[i].y, -1, -1);
            }
            break;
        case 1://left
            if (i_x >= 1 && cell[i_x-1][i_y].valid && !cell[i_x-1][i_y].robot) {
                updateRobot(i, robot[i].x-1, robot[i].y, 2, 0);
                updateRbtDirect(i, 2, 3);
            } else if (i_x <= 198 && cell[i_x+1][i_y].valid && !cell[i_x+1][i_y].robot) {
                updateRobot(i, robot[i].x+1, robot[i].y, 3, 0);
                updateRbtDirect(i, 3, 2);
            } else if (i_y <= 198 && cell[i_x][i_y+1].valid && !cell[i_x][i_y+1].robot){
                updateRobot(i, robot[i].x, robot[i].y+1, 0, 0);
                updateRbtDirect(i, 0, 1);
            } else {
                updateRobot(j, robot[j].x, robot[j].y, -1, -1);
                updateRobot(i, robot[i].x, robot[i].y, -1, -1);
            }
            break;
        case 2://up
            if (i_y >= 1 && cell[i_x][i_y-1].valid && !cell[i_x][i_y-1].robot) {
                updateRobot(i, robot[i].x, robot[i].y-1, 1, 0);
                updateRbtDirect(i, 1, 0);
            } else if (i_y <= 198 && cell[i_x][i_y+1].valid && !cell[i_x][i_y+1].robot) {
                updateRobot(i, robot[i].x, robot[i].y+1, 0, 0);
                updateRbtDirect(i, 0, 1);
            } else if (i_x <= 198 && cell[i_x+1][i_y].valid && !cell[i_x+1][i_y].robot) {
                updateRobot(i, robot[i].x+1, robot[i].y, 3, 0);
                updateRbtDirect(i, 3, 2);
            } else {
                updateRobot(j, robot[j].x, robot[j].y, -1, -1);
                updateRobot(i, robot[i].x, robot[i].y, -1, -1);
            }
            break;
        case 3://down
            if (i_y >= 1 && cell[i_x][i_y-1].valid && !cell[i_x][i_y-1].robot) {
                updateRobot(i, robot[i].x, robot[i].y-1, 1, 0);
                updateRbtDirect(i, 1, 0);
            } else if (i_y <= 198 && cell[i_x][i_y+1].valid && !cell[i_x][i_y+1].robot) {
                updateRobot(i, robot[i].x, robot[i].y+1, 0, 0);
                updateRbtDirect(i, 0, 1);
            } else if (i_x >= 1 && cell[i_x-1][i_y].valid && !cell[i_x-1][i_y].robot) {
                updateRobot(i, robot[i].x-1, robot[i].y, 2, 0);
                updateRbtDirect(i, 2, 3);
            } else {
                updateRobot(j, robot[j].x, robot[j].y, -1, -1);
                updateRobot(i, robot[i].x, robot[i].y, -1, -1);
            }
            break;
    }
}

/**
 * 两个机器人下一帧位置相同
 * @param i
 * @param j
 * @return
 */
bool pumpToSameLoc(int i, int j) {
    return robot[i].aim_x == robot[j].x && robot[i].aim_y == robot[j].y && robot[j].aim_x == robot[i].x && robot[j].aim_y == robot[i].y;
}

/**
 * 两个机器人互换位置
 * @param i
 * @param j
 * @return
 */
bool pumpToEachOther(int i, int j) {
    return robot[i].aim_x == robot[j].aim_x && robot[i].aim_y == robot[j].aim_y;
}

void updateRbtDirect(int id, int direct, int reverseDirect) {
    robot[id].d = direct;
    robot[id].it = robot[id].path.insert(robot[id].it, reverseDirect);
    robot[id].it = robot[id].path.insert(robot[id].it, direct);
}

void updateRobot(int id, int aimX, int aimY, int direct, int sign) {
    robot[id].aim_x = aimX;
    robot[id].aim_y = aimY;
    robot[id].d = direct;
    if (sign == -1) {
        robot[id].it--;
    } else if (sign == 1) {
        robot[id].it++;
    }
}
