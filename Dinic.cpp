#include<stdio.h>
#include<iostream>
//#define LOCAL
using namespace std;

const int infinite = 1e9;
const int max_edge = 20000;
const int max_node = 1000;

int node, edge, s, t;
int ver[max_edge], flow[max_edge], nt[max_edge];
int head[max_node], work[max_node], dis[max_node], q[max_node];

void prepare(int _node, int _s, int _t){
    node = _node;
    s = _s;
    t = _t;
    for(int i=0;i<node;i++){
        head[i] = -1;
    }
    edge = 0;
}

void addedge(int u, int v, int c){
    ver[edge] = v;
    flow[edge] = c;
    nt[edge] = head[u];
    head[u] = edge++;

    ver[edge] = u;
    flow[edge] = 0;
    nt[edge] = head[v];
    head[v] = edge++;
}

bool bfs(){
    int i, u, v, l, r=0;
    for(i=0; i<node; i++){
        dis[i] = -1;
    }
    dis[q[r++]=s] = 0;
    for(l=0;l<r;l++){
        for(i = head[u=q[l]];i>=0;i=nt[i]){
            if(flow[i]&&dis[v=ver[i]]<0){
                dis[q[r++]=v] = dis[u]+1;
                if(v==t) return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int exp){
    if(u==t) return exp;
    for(int &i=work[u],v,tmp;i>=0;i=nt[i]){
        if(flow[i]&&dis[v=ver[i]]==dis[u]+1&&(tmp=dfs(v,min(exp,flow[i])))>0){
            flow[i]-=tmp;
            flow[i^1]+=tmp;
            return tmp;
        }
    }
    return 0;
}

int main(){
    #ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    #endif
    int k=0;
    scanf("%d", &k);
    while(k){
        k--;
        int i,ans=0,delta;
        int n,m,source,terminate;
        scanf("%d %d", &n, &m);
        scanf("%d %d", &source, &terminate);
        prepare(n, source-1, terminate-1);
        for(int j=0;j<m;j++){
            int u,v,c;
            scanf("%d %d %d",&u,&v,&c);
//            printf("%d %d %d\n",u,v,c);
            addedge(u-1, v-1, c);
        }

//        printf("%d\n", head[1]);
//        printf("%d\n", bfs());
        while(bfs()){
            for(i=0;i<node;i++) work[i] = head[i];
            while(delta = dfs(s, infinite)) ans += delta;
        }
        printf("%d\n", ans);
    }


}
