const int N = 2e5 + 9, M = 21;
int arr[N], P[N][M], C[N][M], lv[N];
int n;
vector<vector<pair<int,int>>>adjList;

void dfs(int node, int parent)
{
    lv[node] = lv[parent] + 1;
    P[node][0] = parent;
    for(auto it : adjList[node])
    {
        if(it.first != parent)
        {
            C[it.first][0] = it.second;
            dfs(it.first, node);
        }
    }
}

void build_lca()
{
    for(int j = 1 ; j <= 20 ; j++)
    {
        for(int i = 1 ; i <= n ; i++)
        {
            if(P[i][j-1] > 0)
            {
                P[i][j] = P[P[i][j-1]][j-1];
                C[i][j] = C[P[i][j-1]][j-1] + C[i][j-1];
            }
        }
    }
}
int lca(int x, int y)
{
    if(lv[x] < lv[y])swap(x,y);
    for(int i = 17 ; i>=0 ; i--)
        if(lv[x] - (1<<i) >= lv[y])
            x = P[x][i];

    if (x == y)return x;

    for(int i = 17 ; i>=0 ; i--)
        if(P[x][i] > 0 && P[x][i] != P[y][i])
            x = P[x][i] , y = P[y][i];

    return P[x][0];
}
int get(int x, int parent)
{
    int temp = x; int cur = 0;
    for(int i = 17 ; i>= 0 ; i--)
        if(lv[temp] - (1<<i) >= lv[parent])
            cur += C[temp][i], temp = P[temp][i];

    return cur;
}