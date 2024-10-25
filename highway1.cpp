#include "state.h"
#include <stdlib.h>
#include <string.h>
#define maxn 5010
#define maxm 30060
#define min(a,b) (((a)<(b))?(a):(b))
const int inf = 0x3f3f3f3f;
int q[maxn], eid = 0, d[maxn], visit[maxn], last[maxn];
int dist1[maxn], dist2[maxn];//最短路辅助数组 
//Struct State s[5010];
int tol = 0;
int num = 1;
typedef struct quene{
    int arr[maxm];
    int head; //记录最前面数字所在的下标
    int tail; //记录最后一个有效数字的下一个坐标
                //如果队列里一个数都没有的话head=tail
}queue;

//队列的初始化函数
void queue_init(queue *p_queue) {
    p_queue->head = 0;
    p_queue->tail = 0;
}
int queue_empty(const queue *p_queue) {
    return !(p_queue->tail - p_queue->head);
}
void queue_push(queue *p_queue, int val) {
        p_queue->arr[p_queue->tail] = val;
        p_queue->tail = (p_queue->tail+1) % maxm;
}
//从队列里获得数字的（会把数字从队列里删除）
void queue_pop(queue *p_queue, int *p_num) {
        *p_num = p_queue->arr[p_queue->head];//因为要删除，所以先给
        p_queue->head = (p_queue->head+1) % maxm;//将取过的数跳过去
    
}

int n = num-1;
int u;
int *dist;
int panduan(struct PXL *p)
{
    if (p->red == 255 && p->green == 255 && p->blue == 255)
        return 1;
    else if (p->red == 0 && p->green == 0 && p->blue == 0)
        return 2;
    else 
        return 0;
}

void init_State(struct State *s) {
   for(int i=0;i<maxn;i++)
   {
       s[i].next=-1;
       s[i].v=0;
       s[i].w=0;
       s[i].f=0;
   }
}
void delete_State(struct State *s) {
    return ;
} 

 //表示插入的第几个节点
void insert(int x,int y,int w) 
{
	s[tol].v=y;
	s[tol].next=q[x];
	s[tol].w=w;
	s[tol].f=0;
	q[x]=tol++;
}

void parse(struct State *s, struct PNG *k) {
    init_PNG(k);
    load(k, "pic/test1.png");
    save(k, "pic/test1.png");
    
    memset(q, -1, sizeof(q));
    
    int x = 0, y = 0;    //x表示行，y表示列
    int i = 5, j = 1;
    int w;
    struct PXL *p=NULL;// = (struct PXL*)malloc(sizeof(struct PXL));
    p = get_PXL(k, j, i);
    while (panduan(p) != 1)
    {
    x++;
    y = 0;
    while (p != NULL && panduan(p) != 1)  
    {       
            y++;
            do
            {
                j++;
                p = get_PXL(k, j, i);
            } while (p != NULL && panduan(p) == 2);
      
            if (y - 1 >= 1)      //左
            {
                w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;  
                insert(num,num-1,w);
                //insert(num-1,num,w);
               // printf(" (%d,%d) ",num-1,num);
            }
            if (y + 1 <= (k->width - 1) / 8)      //右
            {
                w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;  
                insert(num,num+1,w);
               // insert(num+1,num,w);
               // printf(" (%d,%d) ",num-1,num);
            }
            if (x - 1 >= 1)        //上
            {
                w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;  
                insert(num,num - (k->width - 1) / 8,w);
                //insert(num - (k->width - 1) / 8,num,w);
                //printf(" (%d,%d) ",num-1,num);
            }
            if (x + 1 <= (k->height - 5) / 8)         //下
            {
                w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;  
                insert(num,num + (k->width - 1) / 8,w);
                //insert(num + (k->width - 1) / 8,num,w);
                //printf(" (%d,%d) ",num-1,num);
            }
            if (x % 2 == 1)   //奇数行
            {
                if (x - 1 >= 1 && y - 1 >= 1)      //左上
                {
                    w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;  
                	insert(num,num - (k->width - 1) / 8-1,w);
                	//insert(num - (k->width - 1) / 8-1,num,w);
                    //printf(" (%d,%d) ",num-1,num);
                }
                if (x + 1 <= (k->height - 5) / 8 && y - 1 >= 1)        //左下
                {
                    w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;  
                	insert(num,num + (k->width - 1) / 8,w);
                	//insert(num + (k->width - 1) / 8,num,w);
                    //printf(" (%d,%d) ",num-1,num);
                }
            }
            if (x % 2 == 0)     //偶数行
            {
                if (x - 1 >= 1 && y + 1 <= (k->width - 1) / 8)      //右上
                {
                    w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;  
                	insert(num,num - (k->width - 1) / 8 + 1,w);
                	//insert(num - (k->width - 1) / 8 + 1,num,w);
                    //printf(" (%d,%d) ",num-1,num);
                }
                if (x + 1 <= (k->height - 5) / 8 && y + 1 <= (k->width - 1) / 8)       //右下
                {
                    w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;  
                	insert(num,num + (k->width - 1) / 8 + 1,w);
                	//insert(num + (k->width - 1) / 8 + 1,num,w);
                    //printf(" (%d,%d) ",num-1,num);
                }
            }
        j++;
        p = get_PXL(k, j, i);
        num++;
    }
    i = i + 8;      //转到下一行
    if (x % 2 == 1)
        j = 5;
    else
        j = 0;
    p = get_PXL(k, j, i);
    }
 //   free(p);
}

int solve1(struct State *s) {
    queue *que = (queue *) malloc(sizeof(queue) * n);
    queue_init(que);
	memset(visit,0,sizeof(visit));
	dist[u]=0;
	visit[u]=1;
	queue_push(que, u);//q.push(u);
	int v, w;
	while(!queue_empty(que)){
		queue_pop(que, &u);// u=q.front();  q.pop();
		visit[u]=0;
		for(int i=q[u];i!=-1;i=s[i].next){//邻接表，只要next不为-1，即没到头节点 
			v=s[i].v;
			w=s[i].w;
			if(dist[v]>dist[u]+w)
			{
				dist[v]=dist[u]+w;
				if(visit[v]==0)
				{
					visit[v]=1;
					queue_push(que, v);//q.push(to)
				}
			}
		}
	}
    free(que);
	return dist[n];
}
int solve2(struct State *s) {
    u = 1;
    dist = dist1;
	solve1(s);
    u = n;
    dist = dist2;
	solve1(s);
	int ans=inf;
	int temp=inf;
	int v, w;
	for(int i=1;i<=n;i++){
		for(int j=q[i];j!=-1;j=s[j].next){
			v=s[j].v;
			w=s[j].w;
			temp=dist1[i]+dist2[v]+w;//加入一条边进行比较 
			if(temp>dist1[n] && temp<ans)
				ans=temp;
		}
	}
	return ans;	
}

