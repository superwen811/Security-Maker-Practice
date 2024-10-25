#include <string.h>
#include "../include/playerbase.h"

void init(struct Player *player) {
	// This function will be executed at the begin of each game, only once.
}

int if_ghost_is_near(int sx,int sy,struct Player *player) {
    int distance[2];
    distance[0]=(player->ghost_posx[0]-sx)+(player->ghost_posy[0]-sy);
    distance[1]=(player->ghost_posx[1]-sx)+(player->ghost_posy[1]-sy);
    if((distance[0]==1 && distance[1]==1)||(sx==player->ghost_posx[0]&&sy==player->ghost_posy[0])||(sx==player->ghost_posx[1]&&sy==player->ghost_posy[1]))
        return 1;
    else
        return 0;
}

int l, r;
int vis[100][100];
int dir[5][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1},{0, 0}};
int in(int x, int y, struct Player *player) {
    return 0<=x && x<player->row_cnt && 0<=y && y<player->col_cnt;
}

struct node {
    int x, y, d, last_dir, parent;
} q[10000];

int bfs(struct Player *player) {
    l = 0, r = 0;
    memset(vis,0,sizeof(vis));
    int sx=player->your_posx;
    int sy=player->your_posy;
    struct node t = {sx, sy, 0, -1, -1};
    q[r++] = t;
    vis[sx][sy] = 1;
    while (l < r) {
find_new:
        struct node now = q[l++];
        if (player->mat[now.x][now.y]=='o'||player->mat[now.x][now.y]=='O') {
            while(q[now.parent].parent!=-1) {
                now=q[now.parent];
            }
            //????????б└??ик
            int next_posx=player->your_posx+dir[now.last_dir][0];
            int next_posy=player->your_posy+dir[now.last_dir][1];
            if(if_ghost_is_near(next_posx,next_posy,player)) {
                goto find_new;
            } else {
                return now.last_dir; 
            }
        }
        for (int i = 0; i < 4; i++) {
            int tx = now.x + dir[i][0];
            int ty = now.y + dir[i][1];
            if (in(tx,ty,player) && player->mat[tx][ty]!='#' && !vis[tx][ty] && !if_ghost_is_near(tx,ty,player)) {
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






#include <string.h>
#include "../include/playerbase.h"

void init(struct Player *player) {
	// This function will be executed at the begin of each game, only once.
}

int if_ghost_is_near(int sx,int sy,struct Player *player) {
    int distance[2];
    distance[0]=(player->ghost_posx[0]-sx)+(player->ghost_posy[0]-sy);
    distance[1]=(player->ghost_posx[1]-sx)+(player->ghost_posy[1]-sy);
    if( (distance[0]==1) || (distance[1]==1) || (sx==player->ghost_posx[0]&&sy==player->ghost_posy[0]) || (sx==player->ghost_posx[1]&&sy==player->ghost_posy[1]) )
        return 1;
    else
        return 0;
}

int l, r;
int vis[100][100];
int dir[5][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1},{0, 0}};
int in(int x, int y, struct Player *player) {
    return 0<=x && x<player->row_cnt && 0<=y && y<player->col_cnt;
}

struct node {
    int x, y, d, last_dir, parent;
} q[10000];

int bfs(struct Player *player) {
    l = 0, r = 0;
//re_find:
    memset(vis,0,sizeof(vis));
    int sx=player->your_posx;
    int sy=player->your_posy;
    struct node t = {sx, sy, 0, -1, -1};
    q[r++] = t;
    vis[sx][sy] = 1;
    while (l < r) {
find_new:
        struct node now = q[l++];
        if (player->mat[now.x][now.y]=='o'||player->mat[now.x][now.y]=='O') {
            while(q[now.parent].parent!=-1) {
                now=q[now.parent];
            }
            //??????
            int next_posx=player->your_posx+dir[now.last_dir][0];
            int next_posy=player->your_posy+dir[now.last_dir][1];
            if(if_ghost_is_near(next_posx,next_posy,player)) {
                goto find_new;
            } else {
                return now.last_dir; 
            }
        }
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
    //goto re_find;
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



#include <string.h>
#include "../include/playerbase.h"
int l, r;
int vis[1000][1000];
int dir[5][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1},{0, 0}};

void init(struct Player *player) {
	// This function will be executed at the begin of each game, only once.
}

int if_ghost_is_near(int sx,int sy,struct Player *player) {
    if(sx==player->ghost_posx[0]&&sy==player->ghost_posy[0])
        return 1;
    if(sx==player->ghost_posx[1]&&sy==player->ghost_posy[0])
        return 1;
    int distance[2]={0};
    distance[0]=abs(player->ghost_posx[0]-sx)+abs(player->ghost_posy[0]-sy);
    distance[1]=abs(player->ghost_posx[1]-sx)+abs(player->ghost_posy[1]-sy);
    if(distance[0]==1||distance[1]==1)
        return 1;
    return 0;
}

int in(int x, int y, struct Player *player) {
    return 0<=x && x<player->row_cnt && 0<=y && y<player->col_cnt;
}

struct node {
    int x, y, d, last_dir, parent;
} q[100000];

int bfs(/*int sx, int sy, */struct Player *player) {
    l = 0, r = 0;
    memset(vis,0,sizeof(vis));
    //memset(q,0,sizeof(q));
    int sx=player->your_posx;
    int sy=player->your_posy;
    struct node t = {sx, sy, 0, -1, -1};
    q[r++] = t;
    vis[sx][sy] = 1;
    while (l < r) {
        struct node now = q[l++];
        if (player->mat[now.x][now.y]=='o'||player->mat[now.x][now.y]=='O') {
            while(q[now.parent].parent!=-1) {
                 now=q[now.parent];
            }
            return now.last_dir;
        }
        for (int i = 0; i < 4; i++) {
            int tx = now.x + dir[i][0];
            int ty = now.y + dir[i][1];
            if (in(tx,ty,player) && player->mat[tx][ty]!='#' && !vis[tx][ty]) {
                if(if_ghost_is_near(tx,ty,player)) continue;
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
    next=bfs(/*player->your_posx,player->your_posy,*/player);
    player->your_posx+=dir[next][0];
    player->your_posy+=dir[next][1];
	struct Point ret = {player->your_posx, player->your_posy};
    return ret;
}
