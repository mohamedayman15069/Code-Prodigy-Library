#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
const int M = ceil(log2(N)) + 1;
const int treeSz = (1<<M); 
int arr[N], tree[treeSz],n;

int F(int left_tree, int right_tree)
{
    return left_tree + right_tree; 
}

int initalize(int arr_idx)
{
    return arr[arr_idx];
}

void build(int ni = 0,int ns = 0,int ne = n - 1){
	if(ns == ne) {
		tree[ni] =  initalize(ns);
		return;
	}
	int lft = 2 * ni + 1;
	int rt = lft + 1;
	int mid = (ne - ns) / 2 + ns;
	build(lft,ns,mid);
	build(rt,mid+1,ne);
	tree[ni] = F(arr[tree[lft]] , arr[tree[rt]]);
}

int Query(int qs,int qe,int ni = 0,int ns = 0,int ne = n -1){
	if(ne < qs || ns > qe) return n;
	if(ns >= qs && ne <= qe) return tree[ni]; 
	int lft = 2 * ni + 1;
	int rt = lft + 1;
	int mid = (ne - ns) / 2 + ns;
	int a = Query(qs,qe,lft,ns,mid);
	int b = Query(qs,qe,rt,mid+1,ne);
	return F(arr[a] , arr[b]);
}


void Update(int pos,int val,int ni = 0,int ns = 0,int ne = n -1){
	if(ne < pos || ns > pos) return;
	if(ns == ne){ 
		tree[ni] = node(val);
		return;
	}
	int lft = 2 * ni + 1;
	int rt = lft + 1;
	int mid = (ne - ns) / 2 + ns;
	Update(pos,val,lft,ns,mid);
	Update(pos,val,rt,mid+1,ne);
	tree[ni] = F(tree[lft],tree[rt]);
}

