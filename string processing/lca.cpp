#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9, M = log2(N) + 1;
int arr[N], st[M][N], LG[N];
int n;
vector<vector<int>>adj;

void fillST(){
	LG[0] = -1;
	for(int i=0;i<n;i++){
		st[0][i] = i;
		LG[i+1] = LG[i] + !(i & (i + 1));
	}
	for(int j = 1; (1 << j) <= n; j++){
		for(int i = 0; (i + (1<<j)) <= n;i++){
			int a = st[j-1][i];
			int b = st[j-1][i+(1<<(j-1))];
			st[j][i] = (arr[a] < arr[b] ? a : b);
		}
	}
}

int RMQ(int i ,int j){
	int sz = j - i + 1;
	int l = LG[sz];
	int a = st[l][i];
	int b = st[l][j - (1 << l) + 1];
	return (arr[a] < arr[b] ? a : b);
}
vector<int>nod,pos;
void printArr(int *a,int s){
	for(int i=0;i<s;i++)
		cout << a[i] << " ";
	cout << endl;
}

void dfs(int u,int prt,int lv = 0){
	pos[u] = n;
	arr[n++] = lv;
	nod.push_back(u);
	for(auto v:adj[u]){
		if(v == prt) continue;
		dfs(v,u,lv+1);
		arr[n++] = lv;
		nod.push_back(u);
	}
}
int LCA(int u,int v){
	int i = pos[u];
	int j = pos[v];
	if(i > j) swap(i,j);
	return nod[RMQ(i,j)];
}

int main() {
	int t,tc = 0;
	cin>>t;
	while(t--){
		int x;
		cin>>x;
		adj = vector<vector<int>>(x);
		vector<bool> isRoot(x,1);
		for(int u = 0; u < x; u++){
			int s;
			cin>>s;
			while(s--){
				int v;
				cin>>v;
				adj[u].push_back(--v);
				isRoot[v] = 0;
			}
		}
		n = 0;
		pos.resize(x);
		nod.clear();

/**********************/
		dfs(find(isRoot.begin(),isRoot.end(),1) - isRoot.begin(),-1);
		/*printArr(&pos[0],x);
		printArr(&nod[0],n);
		printArr(arr,n); */
		fillST();
		int nq;
		cin>>nq;
		cout << "Case " << ++tc<<":\n";
		while(nq--){
			
			int u,v;
			cin>>u>>v;
		int lca = LCA(--u,--v);
		cout << lca + 1 << endl;
		}
	
		
	}
	return 0;
}