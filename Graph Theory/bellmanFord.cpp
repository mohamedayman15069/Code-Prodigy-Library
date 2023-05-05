struct Edge {
    int a, b, cost;
};

int n, m, v;
vector<Edge> edges;
const int INF = 1000000000;


void solve()
{
    vector<int> d(n, INF);
    d[v] = 0;
    vector<int> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges)
            if (d[e.a] < INF)
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = max(-INF, d[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = e.b;
                }
    }

    if (x == -1)
        cout << "No negative cycle from " << v;
    else {
        int y = x;
        for (int i = 0; i < n; ++i)
            y = p[y];

        vector<int> path;
        for (int cur = y;; cur = p[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());

        cout << "Negative cycle: ";
        for (int u : path)
            cout << u << ' ';
    }
}


// COACH IDEA: 
#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;

const int N = 3003;
vector<vector<pair<int, int>>> adj;
int m;
int dis[N];
int inqueue[N], vid;

bool bellman(int src){
    memset(dis, 63, sizeof(dis[0]) * adj.size());
    queue<int> q;
    q.push(src);
    inqueue[src] = ++vid;
    dis[src] = 0;
    int cnt = adj.size();
    while(cnt--){
        int sz = q.size();
        while(sz--){
            int u = q.front();
            q.pop();
            inqueue[u] = 0;
            for(auto child: adj[u]){
                int v, c;
                tie(v, c) = child;
                int d = dis[u] + c;
                if(dis[v] > d){
                    dis[v] = d;
                    if(inqueue[v] != vid){
                        q.push(v);
                        inqueue[v] = vid;
                    }
                    if(!cnt) return false;
                }
            }
        }
    }
    return true;
}