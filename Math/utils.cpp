#include<bits/stdc++.h>
using namespace std;
using ll = long long; 
const int MAXN = 1e7+8;


//Is Prime 
bool prime(int n) {
    if (n < 2) return false;
    for (int x = 2; x*x <= n; x++) {
        if (n%x == 0) return false;
    }
    return true;
}

// Get Prime Factors
vector<int> primeFactors(int n) {
    vector<int> f;
    for (int x = 2; x*x <= n; x++) {
        while (n%x == 0) {
        f.push_back(x);
        n /= x;
        }
    }
    if (n > 1)f.push_back(n);
    return f;
}


// Sieve of Eratosthenes
int primes[MAXN];
void sieve(int n)
{
    primes[1] = 1;
    for (int x = 2; x <= n; x++) {
        if (primes[x]) continue;
        // prime = 0 otherwise is composite
        for (int u = x; u <= n; u += x) {
            primes[u] = x;
        }
    }
}
// Factors not prime Factors
int sp[MAXN] = {};
void CalcSP()
{   
    sp[1] = 1; 
    for(int i = 2 ; i <= MAXN; i++)
    {
        if(i%2 == 0)sp[i] = 2; 
        else
        sp[i] = i; 
    }
    for(int i = 3 ; i * i <= MAXN ; i+=2)
    {
        if(sp[i] == i)
        {
            for(int j = i * i ; j <= MAXN ; j+=i)
            {
                if(sp[j] == j)
                sp[j] = i; 
            }
        }
    }
}


// vector<int> getFactorization(int x)
// {   CalcSP();
//     vector<int> ret;
//     while (x != 1)
//     {
//         ret.push_back(sp[x]);
//         x = x / sp[x];
//     }
//     return ret;
// }

int fact[MAXN];
void getFactorization(int x)
{
    unordered_set<int>st;
    for(int i = 1 ; i * i <= x ; i++)
    {
        if(x%i == 0 )
        {   if(st.find(i) == st.end())
            {
//                ans.push_back(i);
                  fact[i]++;
                st.insert(i);
            }
            if(i *i != x && st.find(x/i) == st.end()){

                fact[x/i]++;
                st.insert(x/i);
            }
        }
    }
}



// EXTENDED GCD

void moveOneStepInSeq(ll &r0, ll &r1, ll q)
{
    ll r2 = r0 - q* r1;
    r0 = r1;
    r1 = r2;
}

ll egcd(ll r0, ll r1 , ll &x0, ll &y0)
{
    ll y1 = x0 = 1;
    ll x1 = y0 = 0;
    while(r1)
    {
        int q = r0/r1;
        moveOneStepInSeq(r0,r1,q);
        moveOneStepInSeq(x0,x1,q);
        moveOneStepInSeq(y0,y1,q);
    }
    return r0;
}
bool solveLDE(ll a,ll b,ll c, ll &x, ll &y, ll &g){
    g = egcd(a,b,x,y);
    ll m = c / g;
    x *= m;
    y *= m;
    return !(c % g);
}

ll modInv(ll a,ll m){
	ll x,y;
	ll g = egcd(a,m,x,y);
	if(g!=1) throw string ("Number are Not Co-PRIMES !!!!!!!");
	return (x % m + m) % m;
}