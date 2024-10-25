#include "state.h"
#include<string.h>
#include<stdlib.h>
#define maxn 5010
#define maxm 30060
#define min(a,b) (a < b ? a : b)

const int inf = 0x3f3f3f3f;
int q[maxn], tol = 0, d[maxn], visit[maxn];
int dist1[maxn], dist2[maxn];//���·�������� 

typedef struct queue{
    int arr[maxm];
    int head; //��¼��ǰ���������ڵ��±�
    int tail; //��¼���һ����Ч���ֵ���һ������
                //���������һ������û�еĻ�head=tail
} queue;

int judge(struct PXL *p)
{
    if (p->red == 255 && p->green == 255 && p->blue == 255)
        return 1;      //��
    else if (p->red == 0 && p->green == 0 && p->blue == 0)
        return 2;      //��
    else 
        return 0;
}

void init_State(struct State *s) {
    for(int i=0; i<maxn; i++)
    {
        s->e[i].v=0;
        s->e[i].next=-1;
        s->e[i].w=0;
    }
}
void delete_State(struct State *s) {
 //   delete_PNG(k);
 //  free(k); 
}

int num = 1;     //��ʾ����ĵڼ����ڵ�
void insert(int x, int y, int w, struct State *s) 
{
	s->e[tol].v = x;
	s->e[tol].next = q[y];
	s->e[tol].w = w;
	q[y] = tol++;
}

void parse(struct State *s, struct PNG *k) {
    memset(q, -1, sizeof(q));
    
    int x = 0, y = 0;    //x��ʾ�У�y��ʾ��
    int i = 6, j = 1;
    int w;
    struct PXL *p = NULL;      // = (struct PXL*)malloc(sizeof(struct PXL));
    p = get_PXL(k, j, i);
    while (p != NULL && judge(p) != 1)
    {
    x++;
    y = 0;
    while (p != NULL && judge(p) == 0)  
    {
        //printf("\n���µĵ�22   ");
            y++;
            //j++;
        while (p != NULL && judge(p) == 0)
            {
                w = 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;
                p = get_PXL(k, j, i);
                j++;
            }

            if (x % 2 == 1)   //������
            {
                if (y - 1 >= 1)      //��
                {
                    insert(num, num - 1, w, s);
                    //insert(num-1,num,w);
                //    printf(" (%d,%d) ", num - 1, num);
                }
                if (y + 1 <= (k->width - 1) / 8)      //��
                {
                    insert(num, num + 1, w, s);
                    // insert(num+1,num,w);
               //     printf(" (%d,%d) ", num + 1, num);
                }
                if (x - 1 >= 1 && y - 1 >= 1)      //����
                {
                	insert(num, num - (k->width - 1) / 8, w, s);
               //     printf(" (%d,%d) ", num - (k->width - 1) / 8, num);
                }
                if (x - 1 >= 1 && y + 1 <= (k->width - 1) / 8)        //����
                {
                    insert(num, num - (k->width - 1) / 8 + 1, w, s);
                //    printf(" (%d,%d) ", num - (k->width - 1) / 8 + 1, num);
                }
                if (x + 1 <= (k->height - 5) / 8 && y - 1 >= 1)        //����
                {
                	insert(num, num + (k->width - 1) / 8 - 1, w, s);
                //    printf(" (%d,%d) ", num + (k->width - 1) / 8 - 1, num);
                    
                }
                if (x + 1 <= (k->height - 5) / 8 && y + 1 <= (k->width - 1) / 8)         //����
                {
                    insert(num, num + (k->width - 1) / 8, w, s);
               //     printf(" (%d,%d) ", num + (k->width - 1) / 8, num);
                    
                }
                
            }
            if (x % 2 == 0)     //ż����
            {
                if (y - 1 >= 1)      //��
                {
                    insert(num, num - 1, w, s);
                 //   printf(" (%d,%d) ",num-1,num);
                }
                if (y + 1 < (k->width - 1) / 8)      //��
                {
                    insert(num, num + 1, w, s);
                // insert(num+1,num,w);
                //    printf(" (%d,%d) ",num+1,num);
                }
                if (x - 1 >= 1)        //����
                {
                    insert(num, num - (k->width - 1) / 8, w, s);
                //    printf(" (%d,%d) ", num - (k->width - 1) / 8, num);
                    
                }
                if (x - 1 >= 1)      //����
                {
                	insert(num, num - (k->width - 1) / 8 + 1, w, s);
                 //   printf(" (%d,%d) ", num - (k->width - 1) / 8 + 1, num);
                    
                }
                if (x + 1 <= (k->height - 5) / 8)         //����
                {
                    insert(num, num + (k->width - 1) / 8 - 1, w, s);
                  //  printf(" (%d,%d) ", num + (k->width - 1) / 8 - 1, num);
                }
                if (x + 1 <= (k->height - 5) / 8)       //����
                {
                	insert(num, num + (k->width - 1) / 8, w, s);
                 //   printf(" (%d,%d) ", num + (k->width - 1) / 8, num);
                    
                }
            }
        j++;
        p = get_PXL(k, j, i);
        num++;
    }
    
    i = i + 8;      //ת����һ��
    if (x % 2 == 1)
        j = 5; 
    else
        j = 1;
    p = get_PXL(k, j, i);
    }
    /*
   for (int j = 1; j < num; j++)
    {
        for (int i = q[j]; ~i; i = s->e[i].next)
        {
            printf("i : %d\n", i);
            int a = s->e[i].v;
            printf("%d->%d ", j, a);
        }
    }  
    printf("\n num= %d \n",num - 1); */
}

int u;
int solve1(struct State *s) 
{
    int n = num-1;
    struct queue que;
    que.head=0;
    que.tail=0;
	memset(visit,0,sizeof(visit));
    memset(dist1, 0x3f, sizeof(dist1));
	dist1[1]=0;
	visit[1]=1;
    que.arr[que.tail]=1;    //q.push(u=1);
    que.tail=(que.tail+1)%maxm;
	int v, w;
	while(que.tail-que.head!=0){
        u=que.arr[que.head];   // u=q.front();  q.pop();
        que.head=(que.head+1)%maxm;
		visit[u]=1;
       // printf("u:%d\n",u);
		for(int i=q[u];i!=-1;i=s->e[i].next){//�ڽӱ�ֻҪnext��Ϊ-1����û��ͷ�ڵ� 
			v=s->e[i].v;
			w=s->e[i].w;
         //   printf("v:%d,i:%d\n",v,i);
         //   printf("w:%d,i=%d\n",w,i);
			if(dist1[v]>dist1[u]+w)
			{
				dist1[v]=dist1[u]+w;
             //   printf("����if %d,v=%d\n",dist1[v],v);
				if(visit[v]==0)
				{
					visit[v]=1;
                    que.arr[que.tail]=v;   //q.push(to)
                    que.tail=(que.tail+1)%maxm;
				}
			}
		}
	}
    //printf("%d\n",dist1[n]);
	return dist1[n];
}
void solve11(struct State *s) {
    int n = num-1; 
    struct queue que;   //init(que);
    que.head=0;
    que.tail=0;   
	memset(visit,0,sizeof(visit));
    memset(dist2, 0x3f, sizeof(dist2));
	dist2[n]=0;
	visit[n]=1;
    que.arr[que.tail]=n;   //q.push(u);
    que.tail=(que.tail+1)%maxm;
	int v, w;
	while(que.tail-que.head!=0){
        u=que.arr[que.head];   // u=q.front();  q.pop();
        que.head=(que.head+1)%maxm;
		visit[u]=0;
		for(int i=q[u];i!=-1;i=s->e[i].next){//�ڽӱ�ֻҪnext��Ϊ-1����û��ͷ�ڵ� 
			v=s->e[i].v;
			w=s->e[i].w;
            
			if(dist2[v]>dist2[u]+w)
			{
				dist2[v]=dist2[u]+w;
				if(visit[v]==0)
				{
					visit[v]=1;
                    que.arr[que.tail]=v;   //q.push(to)
                    que.tail=(que.tail+1)%maxm;
				}
			}
		}
	}
}

int solve2(struct State *s) {
    int n = num-1;
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
			temp=dist1[i]+dist2[v]+w;//����һ���߽��бȽ� 
			if(temp>dist1[n] && temp<ans)
				ans=temp;
		}
	}
	return ans;	
}

