#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
using ll = long long;
const int M = 1e6 + 5, N = 1e6 + 5;
const int MOD = 1e9 + 7;
int tc = 1;
vector<vector<int>>adjList;
int n, m;
int vis[N];
int inDegree[N];
vector<int>res;

void topo_bfs()
{
    priority_queue<int>q;
    for(int i  = 1 ; i <= n; i++)
        if(inDegree[i] == 0)q.push(-i);

    // I just need to check the ones with indegrees less -> decrement it
    while(!q.empty())
    {
        int node= -q.top();
        res.push_back(node);
        q.pop();
        for(auto it : adjList[node])
        {
            if(!--inDegree[it])q.push(-it);
        }
    }
}

//DFS

#define pb push_back

int N;                                // Number of nodes
vector<int> graph[100000], top_sort;  // Assume that this graph is a DAG
bool visited[100000];

void dfs(int node) {
	for (int i : graph[node]) {
		if (!visited[i]) {
			visited[i] = true;
			dfs(i);
		}
	}
	top_sort.pb(node);
}

void compute() {
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			visited[i] = true;
			dfs(i);
		}
	}
	reverse(begin(top_sort), end(top_sort));
	// The vector `top_sort` is now topologically sorted
}

int main() {
	int M;
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a - 1].pb(b - 1);
	}
	compute();
	vector<int> ind(N);
	for (int i = 0; i < N; i++) ind[top_sort[i]] = i;
	for (int i = 0; i < N; i++)
		for (int j : graph[i])
			if (ind[j] <= ind[i]) {
				cout << "IMPOSSIBLE\n";  // topological sort wasn't valid
				exit(0);
			}
	for (int i : top_sort) cout << i + 1 << " ";
	cout << "\n";
}