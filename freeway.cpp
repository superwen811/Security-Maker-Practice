#include "state.h"
#include<string.h>
#include<stdlib.h>
#define maxn 5010
#define maxm 30060
#define min(a,b) (((a)<(b))?(a):(b))

const int inf = 0x3f3f3f3f;
int q[maxn], tol = 1, d[maxn], visit[maxn];
int dist1[maxn], dist2[maxn];//最短路辅助数组 

typedef struct quene{
    int arr[maxm];
    int head; //记录最前面数字所在的下标
    int tail; //记录最后一个有效数字的下一个坐标
                //如果队列里一个数都没有的话head=tail
} queue;

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
 //   struct PXL *k=(struct PXL*)malloc(sizeof(struct PXL));
    
}
void delete_State(struct State *s) {
 //   delete_PNG(k);
 //  free(k); 
}

int num = 1;     //表示插入的第几个节点
void insert(int x, int y, int w, struct State *s) 
{
	s->e[tol].v = x;
	s->e[tol].next = q[y];
	s->e[tol].w = w;
	q[y] = tol++;
}

void parse(struct State *s, struct PNG *k) {
    memset(q, -1, sizeof(q));
    
    int x = 0, y = 0;    //x表示行，y表示列
    int i = 6, j = 1;
    int w;
    struct PXL *p = NULL;      // = (struct PXL*)malloc(sizeof(struct PXL));
    p = get_PXL(k, j, i);
    while (p != NULL && panduan(p) != 1)
    {
    x++;
    y = 0;
    while (p != NULL && panduan(p) != 1)  
    {       
     //   printf("\n读新的点22   ");
            y++;
            j++;
        while (p != NULL && panduan(p) == 0)
            {
                w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;
                p = get_PXL(k, j, i);
                j++;
            } 
              
            
            if (x % 2 == 1)   //奇数行
            {
                if (y - 1 >= 1)      //左
                {
                    insert(num, num - 1, w, s);
                    //insert(num-1,num,w);
               //     printf(" (%d,%d) ", num - 1, num);
                }
                if (y + 1 <= (k->width - 1) / 8)      //右
                {
                    insert(num, num + 1, w, s);
                    // insert(num+1,num,w);
                //    printf(" (%d,%d) ", num + 1, num);
                }
                if (x - 1 >= 1 && y - 1 >= 1)      //左上
                {
                	insert(num, num - (k->width - 1) / 8, w, s);
                //    printf(" (%d,%d) ", num - (k->width - 1) / 8, num);
                }
                if (x - 1 >= 1 && y + 1 <= (k->width - 1) / 8)        //右上
                {
                    insert(num, num - (k->width - 1) / 8 + 1, w, s);
                //    printf(" (%d,%d) ", num - (k->width - 1) / 8 + 1, num);
                }
                if (x + 1 <= (k->height - 5) / 8 && y - 1 >= 1)        //左下
                {
                	insert(num, num + (k->width - 1) / 8 - 1, w, s);
               //     printf(" (%d,%d) ", num + (k->width - 1) / 8 - 1, num);
                    
                }
                if (x + 1 <= (k->height - 5) / 8 && y + 1 <= (k->width - 1) / 8)         //右下
                {
                    insert(num, num + (k->width - 1) / 8, w, s);
               //     printf(" (%d,%d) ", num + (k->width - 1) / 8, num);
                    
                }
                
            }
            if (x % 2 == 0)     //偶数行
            {
                if (y - 1 >= 1)      //左
                {
                    insert(num, num - 1, w, s);
                //    printf(" (%d,%d) ",num-1,num);
                }
                if (y + 1 < (k->width - 1) / 8)      //右
                {
                    insert(num, num + 1, w, s);
                // insert(num+1,num,w);
                //    printf(" (%d,%d) ",num+1,num);
                }
                if (x - 1 >= 1)        //左上
                {
                    insert(num, num - (k->width - 1) / 8, w, s);
              //      printf(" (%d,%d) ", num - (k->width - 1) / 8, num);
                    
                }
                if (x - 1 >= 1)      //右上
                {
                	insert(num, num - (k->width - 1) / 8 + 1, w, s);
               //     printf(" (%d,%d) ", num - (k->width - 1) / 8 + 1, num);
                    
                }
                if (x + 1 <= (k->height - 5) / 8)         //左下
                {
                    insert(num, num + (k->width - 1) / 8 - 1, w, s);
                //    printf(" (%d,%d) ", num + (k->width - 1) / 8 - 1, num);
                }
                if (x + 1 <= (k->height - 5) / 8)       //右下
                {
                	insert(num, num + (k->width - 1) / 8, w, s);
                 //   printf(" (%d,%d) ", num + (k->width - 1) / 8, num);
                    
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
   
    for (int j = 1; j < num; j++)
    {
        printf("000\n");
        for (int i = q[j]; ~i; i = s->e[i].next)
        {
            printf("i : %d\n", i);
            int a = s->e[i].v;
            printf("%d->%d  %ld  001\n", j, a, s->e[i].w);
        }
    }   
}

//队列的初始化函数
void queue_init(queue *p_queue) {
    p_queue->head = 0;
    p_queue->tail = 0;
}
void destroyQueue(queue *PQueue)
{
    free(PQueue);  //释放队列数组指针指向的内存
    PQueue = NULL; //队列数组指针重新指向NULL,避免成为野指针
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
int solve1(struct State *s) {
    queue *que = (queue *) malloc(sizeof(queue) * n);
    queue_init(que);
	memset(visit,0,sizeof(visit));
    memset(dist1, 0x3f, sizeof(dist1));
	dist1[1]=0;
	visit[1]=1;
	queue_push(que, 1);//q.push(u);
	int v, w;
	while(!queue_empty(que)){
		queue_pop(que, &u);// u=q.front();  q.pop();
		visit[u]=0;
		for(int i=q[u];i!=-1;i=s->e[i].next){//邻接表，只要next不为-1，即没到头节点 
			v=s->e[i].v;
			w=s->e[i].w;
            printf("v:%d,i:%d\n",v,i);
            printf("w:%d,i=%d\n",w,i);
			if(dist1[v]>dist1[u]+w)
			{
				dist1[v]=dist1[u]+w;
                printf("进入if %d\n",dist1[v]);
				if(visit[v]==0)
				{
					visit[v]=1;
					queue_push(que, v);//q.push(to)
				}
			}
		}
	}
	destroyQueue(que);
    printf("%d\n",dist1[n]);
	return dist1[n];
}
void solve11(struct State *s) {
    queue *que = (queue *) malloc(sizeof(queue) * n);
    queue_init(que);
	memset(visit,0,sizeof(visit));
    memset(dist2, 0x3f, sizeof(dist2));
	dist2[u]=0;
	visit[u]=1;
	queue_push(que, u);//q.push(u);
	int v, w;
	while(!queue_empty(que)){
		queue_pop(que, &u);// u=q.front();  q.pop();
		visit[u]=0;
		for(int i=q[u];i!=-1;i=s->e[i].next){//邻接表，只要next不为-1，即没到头节点 
			v=s->e[i].v;
			w=s->e[i].w;
            
			if(dist2[v]>dist2[u]+w)
			{
				dist2[v]=dist2[u]+w;
				if(visit[v]==0)
				{
					visit[v]=1;
					queue_push(que, v);//q.push(to)
				}
			}
		}
	}
	destroyQueue(que);
}
int solve2(struct State *s) {
	//solve1(s);
    u = n;
    solve11(s);
	int ans=inf;
	int temp=inf;
	int v, w;
	for(int i=1;i<=n;i++){
		for(int j=q[i];j!=-1;j=s->e[j].next){
			v=s->e[j].v;
			w=s->e[j].w;
			temp=dist1[i]+dist2[v]+w;//加入一条边进行比较 
			if(temp>dist1[n] && temp<ans)
				ans=temp;
		}
	}
	return ans;	
}
