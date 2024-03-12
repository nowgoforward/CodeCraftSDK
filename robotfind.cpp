//
// Created by stx on 2024/3/10.
//

#include "robotfind.h"

void itemSearch(Item& it)//货物找泊位()
{
    if(it.berth_id!=-1)
        return;
    for(int i=0;i<BERTHNUM;i++)
    {
        int dist=getDist(it.x,it.y,berth[i].x,berth[i].y);
        if(dist<it.berth_dist)
        {
            it.berth_id=i;
            it.berth_dist=dist;
        }
    }
}

void robotFind(int id)//为空载的机器人规划路径
{
   auto iter=item_list.begin();
   if(iter==item_list.end())
       return;
   iter++;
   auto best=item_list.begin();
    itemSearch(*best);
   int q=Q(id,*best),tmp;
    while(iter!=item_list.end())
        if(frame-iter->time>S::REMAIN_TIME)
        {
            iter=item_list.erase(iter);
        }
    else
        {
        itemSearch(*iter);
        tmp=Q(id,*iter);
         if(tmp>q)
         {
             best=iter;
             q=tmp;
         }
        iter++;
        }
    bool ret= star(robot[id].x,robot[id].y,best->x,best->y,robot[id].path)&&
            star(best->x,best->y,best->berth_id,robot[id].ibpath);
            if(ret)
            {
                best->state = false;
                robot[id].item = *best;
                item_list.erase(best);
                robot[id].load = true;
                robot[id].path.splice(robot[id].path.end(),robot[id].ibpath);
                /*for(auto j:robot[id].path)
                    printf("%d ",j);
                printf("\n");*/
            }

}

