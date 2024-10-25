int u;
int solve1(struct State *s) {
    int n = num-1;
    struct queue que;
    que.head=0;
    que.tail=0;
	memset(visit,0,sizeof(visit));
    memset(dist1, 0x3f, sizeof(dist1));
	dist1[1]=0;
	visit[1]=1;
    que.arr[que.head]=1;    //q.push(u=1);
    que.tail=(que.tail+1)%maxm;
	int v, w;
	while(que.tail-que.head!=0){
        u=que.arr[que.head];   // u=q.front();  q.pop();
        que.head=(que.head+1)%maxm;
		visit[u]=1;
        printf("u:%d\n",u);
		for(int i=q[u];i!=-1;i=s->e[i].next){//邻接表，只要next不为-1，即没到头节点 
			v=s->e[i].v;
			w=s->e[i].w;
            printf("v:%d,i:%d\n",v,i);
            printf("w:%d,i=%d\n",w,i);
			if(dist1[v]>dist1[u]+w)
			{
				dist1[v]=dist1[u]+w;
                printf("进入if %d,v=%d\n",dist1[v],v);
				if(visit[v]==0)
				{
					visit[v]=1;
                    que.arr[que.tail]=v;   //q.push(to)
                    que.tail=(que.tail+1)%maxm;
				}
			}
		}
	}
    printf("%d\n",dist1[n]);
	return dist1[n];
}
void solve11(struct State *s) {
    int n = num-1;
    struct queue que;   //init(que);
    que.head=0;
    que.tail=0;   
	memset(visit,0,sizeof(visit));
    memset(dist2, 0x3f, sizeof(dist2));
	dist2[u]=0;
	visit[u]=1;
    que.arr[que.tail]=u;   //q.push(u);
    que.tail=(que.tail+1)%maxm;
	int v, w;
	while(que.tail-que.head!=0){
        u=que.arr[que.head];   // u=q.front();  q.pop();
        que.head=(que.head+1)%maxm;
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
			temp=dist1[i]+dist2[v]+w;//加入一条边进行比较 
			if(temp>dist1[n] && temp<ans)
				ans=temp;
		}
	}
	return ans;	
}
