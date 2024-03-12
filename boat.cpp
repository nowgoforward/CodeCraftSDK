//
// Created by stx on 2024/3/10.
//

#include "boat.h"
void BoatLoad()
{

}
void BoatControl()
{
    for (int i = 0; i < 5; i++)
    {
        if (boat[i].cnt == boat_capacity)
        {
            boat[i].target = -1;
            berth[i].state = 0;
            // 发船指令
        }
        else if (boat[i].state = 1 && boat[i].target == -1) // 运输完成，返回
        {
            int Imax = 0, choice;
            for (int j = 0; j < 10; j++)
            {
                if (berth[i].state == 1 || berth[i].state == 2)
                    continue;
                int sum = 0;
                int x = berth[j].x, y = berth[j].y;
                for (int m = x; m <= m + 3; m++)
                    for (int n = y; n <= n + 3; n++)
                    {
                        sum += cell[m][n].value;
                    }
                if (sum > Imax)
                {
                    Imax = sum;
                    choice = j;
                }
            }
            berth[choice].state = 2;
            boat[i].state = 1;
            // 返航指令
        }
    }
}