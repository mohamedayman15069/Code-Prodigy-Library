//ACCEPTED IN ECPC: 
#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
using ll = long long;
const int M = 1e6 + 5, N = 1e6 + 5;
const int MOD = 1e9 + 7;
int tc = 1;
int n,m;
vector<vector<int>>adjList;
int vis[N];
int cycle[N];
vector<int>ans;
vector<int>temp;
bool iscycle =0;
void dfs(int node)
{
    temp.push_back(node);
    vis[node] = 1;
    cycle[node] = 1;
    for(auto it : adjList[node])
    {
        if(!vis[it])
            dfs(it);
        else
        {
            if(cycle[it] == 1 && !iscycle)
            {   temp.push_back(it);
                ans = temp;
                iscycle = 1;
            }
        }
    }
    cycle[node] = 2;
    temp.pop_back();
}

void solve() {
    cin >> n >> m;
    adjList.resize(n+1);
    for(int i = 0 ; i < m ; i++)
    {
        int u,v; cin >> u >> v;
        adjList[u].push_back(v);
    }
    for(int i = 1 ; i<= n; i++)
    {
        if(!vis[i]) {
            iscycle=0;
            temp.clear();
            dfs(i);
        }
    }
    if(ans.size() <=2 && !iscycle)
        return void(cout <<"IMPOSSIBLE\n");
    int idx =0;
    while(ans[idx] != ans.back())idx++;

    cout << ans.size() - idx << '\n';
    for( ; idx < ans.size(); idx++)
        cout << ans[idx] << ' ';
//    for(auto it : ans)
//        cout << it << ' ';
    cout << '\n';

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >>T;
    for(int t = 1 ; t <= T ; t++)
    {
        solve();tc++;
    }
}