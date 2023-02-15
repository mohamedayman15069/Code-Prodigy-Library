#include <bits/stdc++.h>
using namespace std; 
vector<int>vis; 
vector<int>adj[1001];


void dfs(int node)
{
    vis[node] = 1; 

    for(auto it : adj[node])
    {
        if(!vis[it])
        {
            dfs(it); 
        }
    }
}


