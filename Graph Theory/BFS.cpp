#include <bits/stdc++.h>
using namespace std; 

vector<vector<int>> adj; 


void BFS()
{
    int n; // number of nodes
    int s; // source vertex

    queue<int> q;
    vector<bool> used(n);
    vector<int> d(n), p(n);

    q.push(s);
    used[s] = true;
    p[s] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (!used[u]) {
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
        }
    }

}


// Implement 0-1BFS

void BFS_0_1(int s, int n)
{

    vector<pair<int,int>> adj[n];

    const int INF = 0x3f;
    vector<int> d(n, INF);
    d[s] = 0;
    deque<int> q;

    q.push_front(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (auto edge : adj[v]) {
            int u = edge.first;
            int w = edge.second;
            if (d[v] + w < d[u]) {
                d[u] = d[v] + w;
                if (w == 1)
                    q.push_back(u);
                else
                    q.push_front(u);
            }
        }
    }
}
void bfs_1_k(int start, int k, int n, int INF)
{
    vector<queue<int>> bfs(k + 1);
    vector<bool> used(n);
    vector<int> d(n, INF);
    vector<pair<int,int>> g[n];
    bfs[0].push(start);
	d[start] = 0;
	int pos = 0, num = 1; // I recommend to define a variable num - the number of vertexes that are in the queues
	while (num > 0)
	{
		while (bfs[pos % (k + 1)].empty())
		{
			++pos;
		}
		int u = bfs[pos % (k + 1)].front(); 
		bfs[pos % (k + 1)].pop();
		--num;
		if (used[u]) // used vertex can be in other queues
		{
			continue;
		}
		used[u] = true;
		for (pair<int, int> edge : g[u])
		{
			int cost = edge.first, w = edge.second;
			if (d[u] + cost < d[w])
			{
				d[w] = d[u] + cost;
				bfs[d[w] % (k + 1)].push(w);
				++num;
			}
		}
	}
}

//Complexity is O(V+E+maxd)(bounded by O(V⋅lim+E)).
template<typename Graph>
vector<int> SmallDijkstra(Graph& graph, int src, int lim) {
  vector<vector<int>> qs(lim);
  vector<int> dist(graph.size(), -1);

  dist[src] = 0; qs[0].push_back(src);
  for (int d = 0, maxd = 0; d <= maxd; ++d) {
    for (auto& q = qs[d % lim]; q.size(); ) {
      int node = q.back(); q.pop_back();
      if (dist[node] != d) continue;
      for (auto [vec, cost] : graph[node]) {
        if (dist[vec] != -1 && dist[vec] <= d + cost) continue;
        dist[vec] = d + cost;
        qs[(d + cost) % lim].push_back(vec);
        maxd = max(maxd, d + cost);
      }
    }
  }
  return dist;
}


void print_path(int u, vector<int>p, vector<bool>used)
{
    if (!used[u])
        cout << "No path!";
    else {
        vector<int> path;
        for (int v = u; v != -1; v = p[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        cout << "Path: ";
        for (int v : path)
            cout << v << " ";
    }
}