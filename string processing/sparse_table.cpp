#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N =1e5 + 5;
const int MOD = 1e9 + 7;
const int LOG = 20;
int min_range[N][LOG];
int ar[N];
int n;
void build_sparse()
{
    for(int j = 1 ; j <= LOG ; j++)
    {
        for(int i = 0 ; i + (1 << j) - 1 < n ; i++)
        {
            min_range[i][j] = min(min_range[i][j-1], min_range[(i + (1 << (j - 1)))][j - 1]);
        }
    }
}
ll query(int L , int R)
{
    int LEN = (R - L + 1);
    int j = log2(LEN);
    return min(min_range[L][j], min_range[(R - (1 << j) + 1)][j]);
}
