#include <bits/stdc++.h>
using namespace std;
#define popcnt(x) __builtin_popcountll(x)
using ll = long long;
const double PI = 3.14159265359;

vector<int>adjList[2006];
int vis[2006];
int tc = 1;


int dfs(int node, int G)
{
    if(vis[node])
        return vis[node] == G;

    bool ret = 1;
    vis[node] = G;
    for(auto it : adjList[node])
    {
       ret &= dfs(it, G== 1 ? 2 : 1);
    }
    return ret;
}

