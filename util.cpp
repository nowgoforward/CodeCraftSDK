//
// Created by stx on 2024/3/10.
//

#include "util.h"


int Q(int robotId,Item it)
{
    int ds=getDist(robot[robotId].x,robot[robotId].y,it.x,it.y);
    if(ds>S::robot_item_dist_threshold)
        return S::q_inf;
    return it.value*S::value_factor-getDist(robot[robotId].x,robot[robotId].y,it.x,it.y)*S::robot_item_factor-it.berth_dist*S::item_berth_factor;
}


bool star(int s_x,int s_y,int t_x,int t_y,list<int>&path)
{
    static bool vis[200][200]={};
    path.clear();
    if(s_x==t_x&&s_y==t_y)
        return true;
    S::CMP::set(t_x,t_y);
    priority_queue<S::Token*,vector<S::Token*>,S::CMP>q;
    vector<S::Token*> vec;
    vis[s_x][s_y]=true;
    S::Token* token=new S::Token(s_x,s_y),*tmp;
    vec.push_back(token);
    q.push(token);
    while(q.size())
    {
        tmp=q.top();
        q.pop();
        for(int i=0;i<4;i++)
        {
            int X=tmp->x+dir[i][0],Y=tmp->y+dir[i][1];
            if(isValid(X,Y)&&!vis[X][Y])
            {
                token=new S::Token(X,Y,i,tmp);
                vis[X][Y]=true;
                vec.push_back(token);
                q.push(token);
                if(X==t_x&&Y==t_y)
                {
                    while(token->last)
                    {
                        path.push_front(token->d);
                        token=token->last;
                    }
                    for(auto it:vec)
                    {
                        vis[it->x][it->y]=false;
                        delete it;
                        it=nullptr;
                    }
                    return true;
                }
            }

        }
    }
    logFile<<"star\n";
    for(auto it:vec)
    {
        vis[it->x][it->y]=false;
        delete it;
        it=nullptr;
    }
    return false;
}

bool star(int s_x,int s_y,int berthid,list<int>&path)
{
    static bool vis[200][200]={};
    path.clear();
    if(S::isinberth(s_x,s_y,berthid))
        return true;
    S::CMP::set(berth[berthid].x,berth[berthid].y);
    priority_queue<S::Token*,vector<S::Token*>,S::CMP>q;
    vector<S::Token*> vec;
    vis[s_x][s_y]=true;
    S::Token* token=new S::Token(s_x,s_y),*tmp;
    vec.push_back(token);
    q.push(token);
    while(q.size())
    {
        tmp=q.top();
        q.pop();
        for(int i=0;i<4;i++)
        {
            int X=tmp->x+dir[i][0],Y=tmp->y+dir[i][1];
            if(isValid(X,Y)&&!vis[X][Y])
            {
                token=new S::Token(X,Y,i,tmp);
                vis[X][Y]=true;
                vec.push_back(token);
                q.push(token);
                if(S::isinberth(X,Y,berthid))
                {
                    while(token->last)
                    {
                        path.push_front(token->d);
                        token=token->last;
                    }
                    for(auto it:vec)
                    {
                        vis[it->x][it->y]=false;
                        delete it;
                        it=nullptr;
                    }
                    return true;
                }
            }

        }
    }
    for(auto it:vec)
    {
        vis[it->x][it->y]=false;
        delete it;
        it=nullptr;
    }
    return false;
}
