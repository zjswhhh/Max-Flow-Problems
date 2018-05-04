#include<stdio.h>
#include<iostream>
//#define LOCAL
using namespace std;

const int infinite = 1e9;
const int max_edge = 20000*300;
const int max_node = 1000*3000;

int node, edge, s, t;
int ver[max_edge], flow[max_edge], nt[max_edge], input[max_edge][2];
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

    //printf("%d %d\n",u,v);
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
    int kase=0;
    scanf("%d", &kase);
    while(kase){
        kase--;
        int n,m,source,terminate,k;
        scanf("%d %d", &n, &m);
        scanf("%d %d %d", &source, &terminate, &k);
        if(k>n) {
            printf("NO\n");
            continue;
        }
        for(int j=0;j<m;j++){
            scanf("%d %d", &input[j][0],&input[j][1]);
        }
        int low=0, high=n+1,level;
        int ans = infinite;
        while(low<=high){
            level = (low+high)/2;
            //To build the graph
            prepare(n*level+2, 0, n*level+1);
            for(int j=0;j<m;j++){
                int u = input[j][0];
                int v = input[j][1];
                for(int l=0;l<level-1;l++){
                    addedge(u+l*n, v+(l+1)*n, 1);
                }
            }
            addedge(s,source,infinite);
            for(int l=0;l<level;l++) addedge(terminate+l*n,t,infinite);


        //calculate the max_flow;
            int max_flow=0,delta;
            while(bfs()){
                for(int i=0;i<node;i++) work[i] = head[i];
                while(delta = dfs(s, infinite)) max_flow += delta;
            }
            if(max_flow<k) {
                low = level+1;
            } else if(max_flow>=k){
                high = level-1;
                ans = level-1;
            }
        }
        if(ans<infinite) printf("%d\n", ans);
        else printf("NO\n");
    }
}
