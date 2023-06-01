#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
using ll = long long;
const int N = 3e5 + 9;
const int M = ceil(log2(N)) + 1;
const int treeSz = (1<<M);


struct node{
    int pre,suf,sum,mx;
    node(){
        pre = -1e9;
        suf = -1e9;
        mx = -1e9;
        sum = 0;
    }
    node(int x){
        pre = suf = mx = sum = x;
    }

};
node merge(node a, node b)
{
    node ret;
    ret.sum = a.sum + b.sum;
    ret.pre = max(a.pre, a.sum+b.pre);
    ret.suf = max(b.suf, a.suf + b.sum);
    ret.mx  = max({a.mx, b.mx, a.suf + b.pre});
    return ret;
}

ll arr[N],n,q;
node tree[4*N];

void build(int ni = 0,int ns = 0,int ne = n - 1){
    if(ns == ne) {
        tree[ni] =  node(arr[ns]);
        return;
    }
    int lft = 2 * ni + 1;
    int rt = lft + 1;
    int mid = (ne - ns) / 2 + ns;
    build(lft,ns,mid);
    build(rt,mid+1,ne);
    tree[ni] = merge(tree[lft] , tree[rt]);
}

node Query(int qs,int qe,int ni = 0,int ns = 0,int ne = n -1){
    if(ne < qs || ns > qe) return node();
    if(ns >= qs && ne <= qe) return tree[ni];
    int lft = 2 * ni + 1;
    int rt = lft + 1;
    int mid = (ne - ns) / 2 + ns;
    return  merge(Query(qs,qe,lft,ns,mid) , Query(qs,qe,rt,mid+1,ne));
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
    tree[ni] = merge(tree[lft],tree[rt]);
}


void solve() {
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];

    build();
    int qn;
    cin>>qn;
    while(qn--){
        int type,xi,yi;
        cin>>type;
        cin>>xi>>yi;
        if(type){
            node ret = Query(--xi,--yi);
            cout << ret.mx << endl;
        }else{
            Update(--xi,yi);
        }
    }

}

int main() {
//    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >>T;
    for(int t = 1 ; t <= T ; t++)
    {
        solve();//tc++;
    }
}