//
// Created by stx on 2024/3/11.
//

#ifndef CODECRAFTSDK_ACTION_H
#define CODECRAFTSDK_ACTION_H

#include "Base.h"
void pump();
bool pumpToSameLoc(int i, int j);
bool pumpToEachOther(int i, int j);
void solutionToPTEO(int i, int j);
void solutionToPTSL(int i, int j);
void resetPrio();
void updateRobot(int id, int aimX, int aimY, int direct, int sign);
void updateRbtDirect(int id, int direct, int reverseDirect);
bool JtoILoc(int i, int j);


#endif //CODECRAFTSDK_ACTION_H
