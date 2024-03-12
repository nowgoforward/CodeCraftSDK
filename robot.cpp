#include "robot.h"

void robotControl()
{
    for(int i=0;i<ROBOTNUM;i++)
        if(!robot[i].load)
        {
            robotFind(i);
        }
    for(int i=0;i<ROBOTNUM;i++)
    {
        robot[i].op=0;
            if (robot[i].load) {
                if (robot[i].is_on_item())
                    robot[i].op = 1;
                else if (robot[i].is_in_berth())
                    robot[i].op = 2;
            }
     }
   // pump();
}