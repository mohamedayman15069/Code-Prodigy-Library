#include <bits/stdc++.h>
using namespace std;
const int N = 50 * 50;

struct DSU{
  int Par[N],sz[N];
  int n,cnt,mx;
  DSU(int n):n(n){
    memset(Par,-1,n*sizeof(Par[0]));
    fill(sz,sz+n,1);
    cnt = n;
    mx = 1;
  }
  int find(int x){
   return ~Par[x] ? Par[x] =  find(Par[x]) : x;
  }
  void merge(int x,int y){
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(sz[x] > sz[y]) swap(x,y);
    Par[x] = y;
    sz[y] += sz[x];
    cnt--;
    mx = max(mx,sz[y]);
  }
};
