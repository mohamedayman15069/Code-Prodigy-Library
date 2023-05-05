#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
using ll = long long;
const int M = 1e6 + 5, N = 1e6 + 5;
const int MOD = 1e9 + 7;
int tc = 1;

int n,m,x;
bool vis_1[N],vis_2[N];
vector<vector<int>>adjList;
int deg[N];
int sz;
int tour[N];
multiset<int>sorted_adj[N];
void prepare_data()
{
    memset(vis_1, 0, sizeof(vis_1[0]) * (n+2));
    memset(vis_2, 0, sizeof(vis_2[0]) * (n+2));
    memset(deg, 0, sizeof(deg[0]) * (n+2));
    memset(tour, 0, sizeof(tour[0])*(n+2));
    sz = 0;
    adjList.clear();

    for(int i = 1 ; i<= n; i++)sorted_adj[i].clear();

    adjList.resize(n+2);
}

void dfs(int node)
{
    vis_1[node] = 1;
    for(auto it : adjList[node])
        if(!vis_1[it])
            dfs(it);
}

void euler(int node)
{
    vis_2[node] = 1;
    for(;sorted_adj[node].size() > 0 ; )
    {
        int v = *sorted_adj[node].begin();
        // delte the two directions
        sorted_adj[node].erase(sorted_adj[node].begin());
        sorted_adj[v].erase(sorted_adj[v].lower_bound(node));
        euler(v);
    }
    tour[sz++] = node;
}
void printing()
{
    vector<int>res;

    for(int i = 0 ; i < x; i++)
    {
        for(int j = 0 ; j < sz ;j++)
            res.push_back(tour[j]);
        reverse(tour, tour + sz );
    }
    int idx = 0;
    for(auto it= 0 ; it <  res.size(); it++){
        if(it != 0 && res[it] == res[it-1])
            continue;
        cout << res[it] << ' ';
    }
    cout <<'\n';

}

void solve() {
    //Do the same thing with x exactly as 1 but with a minor change in the results
    cin >> n >> m >> x;
    prepare_data();
    for(int i = 0 ; i< m; i++)
    {   int u,v; cin >> u >>v ;
        adjList[u].push_back(v);
        deg[u]++;
        deg[v]++;
        sorted_adj[u].insert(v);
        sorted_adj[v].insert(u);
    }

    /*
     * Multiple Conditions:
     * 1. DO DFS : check the connectivity -> Not sufficient !!
     * 2. Check whether it is circuit or tour -> DEG is odd with 2 only or 0
     * 3. If circuit -> do euler
     * 4. If tour   -> Start euler with node having deg of 1
     * 5. Print answer anyways with a help of sorted_adj!
     */
    // dfs
    dfs(1);
    for(int i = 1 ; i<= n ;i++) {
        if (!vis_1[i] &&deg[i] != 0) // if deg[i] = 0 -> it is disconnected city without any sort of edges which is good !
            return void(cout << "-1\n");
    }
    int oddNodes = 0;
    int theoddNode = 0;
    for(int i = 1 ; i <=n ; i++)
    {
        if(deg[i]%2 !=0)
        {
            oddNodes++;
            theoddNode = i;
        }
    }
    if(oddNodes != 0 && oddNodes != 2)
        return void(cout <<"-1\n");
    if(oddNodes == 0){
        //Circuit!
        euler(1);
        printing();
    }
    else
    {
        // normal Tour
        euler(theoddNode);
        printing();
    }

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; cin >>T;
    for(int t = 1 ; t <= T ; t++)
    {
        solve();tc++;
    }
}