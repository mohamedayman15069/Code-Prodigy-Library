#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
using ll = long long;
const int M = 1e6 + 5, N = 1e6 + 5;
const int MOD = 1e9 + 7;
int tc = 1;
ll from[M], to[M], cost[M], idx[M], edges[M];
int n, m;

struct DSU{
    ll par[N], sz[N];
    void init(int n){
        memset(par, -1, n * sizeof(par[0]));
        fill(sz, sz + n, 1);
    }

    int find(int x){
        return (~par[x] ? par[x] = find(par[x]) : x);
    }

    bool join(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(sz[x] > sz[y]) swap(x, y);
        sz[y] += sz[x];
        par[x] = y;
        return 1;
    }
}dsu;

ll kruskal(){
    int sz = 0;
    dsu.init(n);
    sort(idx, idx + m, [](ll x, ll y){return cost[x] < cost[y];});
    ll ret = 0;
    for(int i = 0 ; i < m ; i++)
    {
        int j = idx[i];
        int u = from[j] , v = to[j];
        if(dsu.join(u,v))
        {
            ret += cost[j];
            sz++;
        }
    }
    if(sz == n-1)return ret;
    return 0;

}