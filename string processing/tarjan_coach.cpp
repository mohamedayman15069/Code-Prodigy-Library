#include <bits/stdc++.h>

using namespace std;

const int N = 1e5;
vector<vector<int> > adj;
stack<int> stk;
int n, tim, low[N], ind[N], compId[N], ncomp;

void dfsScc(int u) {
    ind[u]=low[u]=tim++;
    stk.push(u);
    for(auto v:adj[u])
        if(~ind[v]){
            if(!~compId[v])
                low[u]=min(low[u],low[v]);
        }else{
            dfsScc(v);
            low[u]=min(low[u],low[v]);
        }
    if(low[u]==ind[u]){
        int x;
        do {
            x=stk.top();
            stk.pop();
            compId[x]=ncomp;
        } while (x!=u);
        ++ncomp;
    }
}
bool Src[N],Snk[N];
void scc() {
    ncomp = 0;
    tim = 0;
    n = adj.size();
    memset(ind, -1, n * sizeof ind[0]);
    memset(compId, -1, n * sizeof compId[0]);
    memset(Src,true,n * sizeof Src[0]);
    memset(Snk,true,n * sizeof Snk[0]);
    for (int i = 0; i < n; ++i) if (!~ind[i])dfsScc(i);
    for(int u = 0; u < n; ++u){
    	for(auto v : adj[u]){
    		if(compId[v] == compId[u]) continue;
    		Snk[compId[u]] = false;
    		Src[compId[v]] = false;
    	}
    }
}

int main() {
	cin>>n;
	adj.resize(n);
	for(int i = 0;i<n;++i){
		int x;
		while(cin>>x,x--){
			adj[i].push_back(x);
		}
	}
	scc();
	int cnt1 = count(Src,Src+ncomp,true);
	int cnt2 = count(Snk,Snk+ncomp,true);
	cout << cnt1 << endl;
	if(ncomp == 1) cout << 0 << endl;
	else cout << max(cnt1,cnt2) << endl;
    return 0;
}