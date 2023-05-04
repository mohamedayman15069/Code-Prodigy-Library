#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
using ll = long long;
const int N = 1e5+7;
const int MOD = 1e9 + 7;
const int K = N;

ll factorial[K] , inv[K];
ll binpow(ll a, ll b)
{
    if (b == 0)
        return 1;
    ll res = binpow(a,b/2)%MOD;
    if(b%2)
        return (res%MOD * res%MOD * a%MOD)%MOD;
    else return (res%MOD * res%MOD)%MOD;
}
void fact()
{
    factorial[0] = inv[0] = 1;
    for(int i = 1; i < K ; i++)
    {
        factorial[i] = factorial[i-1] * i %MOD;
        inv[i] = inv[i-1] * binpow(i,MOD-2)%MOD;
    }
}
ll C(int n ,int m)
{
    return factorial[n] * inv[n-m]%MOD * inv[m]%MOD;
}