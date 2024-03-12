//
// Created by stx on 2024/3/10.
//

#ifndef CODECRAFTSDK_UTIL_H
#define CODECRAFTSDK_UTIL_H

#include "Base.h"
int Q(int robotId,Item it);//价值函数
bool star(int x,int y,int t_x,int t_y,list<int>& path);//寻路算法,起点
bool star(int s_x,int s_y,int berthid,list<int>&path);

#endif //CODECRAFTSDK_UTIL_H
