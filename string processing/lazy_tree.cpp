#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9, M = ceil(log2(N)) + 1;
int n;
struct node{
	long long sum, lazy;
	void addLazy(long long val,int ns, int ne){
		lazy += val;
		sum += (ne - ns + 1ll) * val;
	}
};
node tree[1<<M];

void pushDown(int ni,int ns,int ne){
	if(ns == ne || tree[ni].lazy == 0) return;
	int lft = 2 * ni + 1;
	int rt = lft + 1;
	int mid = (ne - ns) / 2 + ns;
	tree[lft].addLazy(tree[ni].lazy, ns,mid);
	tree[rt].addLazy(tree[ni].lazy, mid+1,ne);
	tree[ni].lazy = 0;
}

void add(int qs,int qe,int qv,int ni = 0,int ns = 0,int ne = n - 1){
	if(ne < qs || ns > qe) return;
	if(ns >= qs && ne <= qe) return tree[ni].addLazy(qv,ns,ne);
	pushDown(ni,ns,ne);
	int lft = 2 * ni + 1;
	int rt = lft + 1;
	int mid = (ne - ns) / 2 + ns;
	add(qs,qe,qv,lft,ns,mid);
	add(qs,qe,qv,rt,mid+1,ne);
	tree[ni].sum = tree[lft].sum + tree[rt].sum;
	
}

long long Query(int qs,int qe,int ni = 0,int ns = 0,int ne = n - 1){
	if(ne < qs || ns > qe) return 0;
	if(ns >= qs && ne <= qe) return tree[ni].sum;
	pushDown(ni,ns,ne);
	int lft = 2 * ni + 1;
	int rt = lft + 1;
	int mid = (ne - ns) / 2 + ns;
	long long a = Query(qs,qe,lft,ns,mid);
	long long b = Query(qs,qe,rt,mid+1,ne);
	return a + b;
	
}
int main() {
	int t;
	cin>>t;
	while(t--){
		memset(tree,0,sizeof tree);
		int c;
		cin>>n>>c;
		for(int i=0;i<c;i++){
			int type,p,q,v;;
			cin>>type;
			if(!type){
				cin>>p>>q>>v;
				add(--p,--q,v);
			}else{
				cin>>p>>q;
				cout << Query(--p,--q) << endl;
			}
		}
	}/*********/
	return 0;
}