#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
using ll = long long;
const int MAX = 200;
const int MOD = 1e9 + 7;
int tc = 1;
//Prim -> Dense 
int adjList[MAX][MAX];
int notVis[MAX];
int dis[MAX];
int par[MAX];

int n;
int prim(int src)
{
    iota(notVis, notVis + n + 1, 0);
    memset(par, -1, sizeof(par[0]) * (n + 1));
    memset(dis, '?', sizeof(dis[0]) * (n + 1));
    dis[src] = 0;
    int sz = n;
    int ret = 0;
    int bst = 0;

    int nxt = src;

    while(~nxt)
    {
        int u = notVis[nxt];
        ret += bst;
        notVis[nxt] = notVis[--sz];

        nxt = -1;
        bst = 0x3f3f3f3f;
        for(int i = 0 ; i < sz; i++)
        {
            int v = notVis[i];

            if(dis[v] > adjList[u][v])
            {
                dis[v] = adjList[u][v];

            }
            if(bst > dis[v])
            {
                bst = dis[v];
                nxt = i;
            }
        }
    }
    return ret;
}


