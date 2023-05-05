#include <bits/stdc++.h>
using namespace std; 


vector<vector<pair<int,int>>>adj;
int dis[128];
int n = 128;
void Dijkstra(int src){
  memset(dis,0x3f,n*sizeof(dis[0]));
  dis[src] = 0;
  priority_queue < pair <int,int> >PQ;
  PQ.emplace(0,src);
  while(PQ.size()){
    int d,u;
    tie(d,u) = PQ.top(),PQ.pop();
    d = -d;
    if(dis[u] != d) continue; //To avoid Calc. same node twice
    for(auto &P:adj[u]){
      int v,c;
      tie(v,c) = P;
      int nd = d + c;
      if(nd < dis[v]){
        dis[v] = nd;
        PQ.emplace(-nd,v);
      }
    }
  }
}