#include <bits/stdc++.h>

using namespace std;
#define VAR(X) ((X)*2)
#define NOT(X) ((X)^1)



const int N = 1e5;
vector<vector<int> > adj;
stack<int> stk;
int n, tim, low[N], ind[N], compId[N], ncomp;
int ans[N];
bool vis[N];


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

void AddOr(int x, int y){

	adj[NOT(x)].push_back(y);
	adj[NOT(y)].push_back(x);
	
}

void AddXor(int x, int y){

	AddOr(x, y);
	AddOr(NOT(x), NOT(y));	
	
}
// cId represents a couple
int getPersonId(int cId, bool isHusband){
	
	return (2*cId) + isHusband;
	
}

void dfs(int u){
	
	if(vis[u]) return;
	
	vis[u] = true;
	
	for (int v : adj[u]){
		dfs(v);
	}
	if (ans[compId[u]]==-1){
		ans[compId[u]] = true;
		ans[compId[NOT(u)]] = false;
	}
}





int main() {
	
	int c, m;
	while (cin>>c>>m , c||m){
		
		adj.clear();
		n = 4*c;
		adj.resize(n);
		
		int w0= VAR(getPersonId(0, 0));
		AddOr(w0, w0); // make sure the wife is sitting at the true side
		
		for (int i=0; i<c;++i){
			int h= VAR(getPersonId(i, 1));
			int w= VAR(getPersonId(i, 0));
			
			AddXor(h, w);
			
		}
		
		int c1, c2; // couple one, two
		char t1, t2; //type one, two 
		while(m--){
			cin>> c1>>t1;
			cin>> c2>>t2;
			
			int p1 = VAR(getPersonId(c1, t1 =='h'));
			int p2 = VAR(getPersonId(c2, t2 =='h'));
			AddOr(p1, p2);
			// the graph is constructed
		}
		scc();	
		
		bool badLuck = false;
		
		for (int i = 0; i<n; i+=2){
			if (compId[i]==compId[NOT(i)]) {badLuck= true; break;}
		}
		
		if (badLuck){
			cout << "bad luck\n";
			continue;
		}
		
		memset (ans, -1, ncomp* sizeof(ans[0]));
		memset (vis, 0, n* sizeof(vis[0]));

		for (int i=0; i<n; ++i){
			if (ans[compId[i]] == -1){
				dfs(i);
			}
		}
		string s="";
		for (int i=1; i<c; ++i){
			for (int t = 0; t<2; t++){
				int p = VAR(getPersonId(i, t));
				if (ans[compId[p]]){
					cout<< s << i << "wh"[t];
					s=" ";
				}
			}
		}
		cout << endl;
		
	}
	
    return 0;
}
