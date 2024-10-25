#include <string.h>
#include <math.h>
#include "../include/playerbase.h"
int l, r;
int vis[50][50]={0};
int dir[5][2] = {{0, -1}, {1, 0}, {0, 1},{ -1, 0},{0, 0}};
struct node {
    int x, y, d, last_dir, parent;
} q[10000];

void init(struct Player *player) {
	// This function will be executed at the begin of each game, only once.
}

int if_ghost_is_near(int sx,int sy,struct Player *player) {
    int distance[2]={0};
    distance[0]=abs(player->ghost_posx[0]-sx)+abs(player->ghost_posy[0]-sy);
    distance[1]=abs(player->ghost_posx[1]-sx)+abs(player->ghost_posy[1]-sy);
    if(distance[0]==1 || distance[1]==1)
        return 2;
    if(sx==player->ghost_posx[0]&&sy==player->ghost_posy[0])
        return 1;
    if(sx==player->ghost_posx[1]&&sy==player->ghost_posy[1])
        return 1;
    return 0;
}

int in(int x, int y, struct Player *player) {
    return 0<=x && x<player->row_cnt && 0<=y && y<player->col_cnt;
}

int bfs(struct Player *player) {
    l = 0, r = 0;
    memset(vis,0,sizeof(vis));
    int sx=player->your_posx;
    int sy=player->your_posy;
    struct node t = {sx, sy, 0, -1, -1};
    q[r++] = t;
    vis[sx][sy] = 1;
    while (l < r) {
        struct node now;
find_new_dir:
        now = q[l++];
        if(player->your_status>0/*(abs(player->your_posx-player->ghost_posx[0])+abs(player->your_posy-player->ghost_posy[0]))||player->your_status>(abs(player->your_posx-player->ghost_posx[1])+abs(player->your_posy-player->ghost_posy[1]))*/) { 
            //优化:强化状态追鬼
            if((now.x==player->ghost_posx[0]&&now.y==player->ghost_posy[0])||(now.x==player->ghost_posx[1])&&now.y==player->ghost_posy[1]) {
                    while(q[now.parent].parent!=-1) {
                        now=q[now.parent];
                    }
                    return now.last_dir;
            }
        }
        //优化：非强化状态优先吃强化豆
        else if(player->your_status==0){
            if(player->mat[9][3]=='O'||player->mat[9][6]=='O') {
                if(player->mat[now.x][now.y]=='O') {
                    while(q[now.parent].parent!=-1) {
                        now=q[now.parent];
                    }
                    //优化：非强化状态躲鬼，强化状态吃鬼
                    int next_posx=player->your_posx+dir[now.last_dir][0];
                    int next_posy=player->your_posy+dir[now.last_dir][1];
                    int ghost=if_ghost_is_near(next_posx,next_posy,player);
                    if(ghost>0) //鬼在身边
                    {
                        if(ghost==1&&player->your_status>0) 
                            return now.last_dir;
                        //鬼在四周且强化状态至少还剩一个回合，吃鬼
                        else if(ghost==2&&player->your_status>1)
                            return now.last_dir;
                        //鬼在附近且强化状态至少还剩两个回合，正常走
                        else if(player->your_status==0)
                            goto find_new_dir;
                        //其他情况，躲鬼
                    } 
                    else if(ghost==0) //鬼不在身边，正常走
                    {
                        return now.last_dir; 
                    }
                }
            }
            else {
                if(player->mat[now.x][now.y]=='o') {
                    while(q[now.parent].parent!=-1) {
                        now=q[now.parent];
                    }
                    //优化：非强化状态躲鬼，强化状态吃鬼
                    int next_posx=player->your_posx+dir[now.last_dir][0];
                    int next_posy=player->your_posy+dir[now.last_dir][1];
                    int ghost=if_ghost_is_near(next_posx,next_posy,player);
                    if(ghost>0) //鬼在身边
                    {
                        if(ghost==1&&player->your_status>0) 
                            return now.last_dir;
                        //鬼在四周且强化状态至少还剩一个回合，吃鬼
                        else if(ghost==2&&player->your_status>1)
                            return now.last_dir;
                        //鬼在附近且强化状态至少还剩两个回合，正常走
                        else if(player->your_status==0)
                            goto find_new_dir;
                        //其他情况，躲鬼
                    } 
                    else if(ghost==0) //鬼不在身边，正常走
                    {
                        return now.last_dir; 
                    }
                }
            }
        
        }
        
        /*else if() {
            while(q[now.parent].parent!=-1) {
                now=q[now.parent];
            }
            //优化:强化状态可以吃鬼
            int next_posx=player->your_posx+dir[now.last_dir][0];
            int next_posy=player->your_posy+dir[now.last_dir][1];
            int ghost=if_ghost_is_near(next_posx,next_posy,player);
            if(ghost==1&&player->your_status>0) {
                return now.last_dir; 
            } 
            else if(ghost==2&&player->your_status>1) {
                return 4;
            }
            else if(ghost==0) {
                return now.last_dir;
            }
        }*/
        for (int i = 0; i < 4; i++) {
            int tx = now.x + dir[i][0];
            int ty = now.y + dir[i][1];
            if (in(tx,ty,player) && player->mat[tx][ty]!='#' && !vis[tx][ty] /*&& !if_ghost_is_near(tx,ty,player)*/) {
                vis[tx][ty] = 1;
                struct node t = {tx, ty, now.d + 1, i, l-1};
                q[r++] = t;
            }
        }
    }
    return 4;
}

struct Point walk(struct Player *player) {
	// This function will be executed in each round.
    int next;
    next=bfs(player);
    player->your_posx+=dir[next][0];
    player->your_posy+=dir[next][1];
	struct Point ret = {player->your_posx, player->your_posy};
    return ret;
}