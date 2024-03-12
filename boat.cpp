//
// Created by stx on 2024/3/10.
//

#include "boat.h"

void BoatControl() {
    for (int i = 0; i < 5; i++) {
        if (boat[i].cnt == boat_capacity) {
            boat[i].target = -1;
            berth[i].state = 0;
            // 发船指令 TODO
        } else if (boat[i].state = 1 && boat[i].target == -1) // 运输完成，返回
        {
            int Imax = 0, choice;
            for (int j = 0; j < 10; j++) {
                if (berth[j].state == 0) {
                    int sum = 0;
                    for (auto m: berth[j].item_value)
                        sum += m;
                    if (sum >= Imax) {
                        Imax = sum;
                        choice = j;
                    }
                }
            }
            berth[choice].state = 2;
            berth[choice].boat_id = 0;
            berth[choice].arrival_time = frame + berth[choice].transport_time;
            boat[i].state = 1;
            boat[i].target = choice;
            // 返航指令 TODO
        } else if (boat[i].state = 1 && frame == berth[boat[i].target].arrival_time) {//达到港口
            boat[i].state = 1;
            berth[boat[i].target].state = 1;
        }//感觉好像没用

    }
    printf("\nberth id frame:%d\n",frame);
    for (int i = 0; i < 10; i++)
        printf("%d ", berth[i].boat_id);
    printf("\n");//第一次船第二帧才到位？
}

void BoatLoad() {
    for (int i = 0; i < 10; i++) {
        if (berth[i].state == 1)
            if (berth[i].add > 0) {
                int add_load = min(berth[i].add, berth[i].loading_speed);
                for (int s = 1; s <= add_load; s++) {
                    berth[i].item_value.pop_front();
                }
                boat[berth[i].boat_id].cnt += add_load;
            }

    }

}