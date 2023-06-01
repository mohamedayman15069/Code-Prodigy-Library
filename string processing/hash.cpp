#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using namespace __gnu_cxx;

int MOD = 1e9 + 7;

struct mul{
  int operator()(int a,int b)const{
    return a * 1ll * b % MOD;
  }
}m;

struct add{
  int operator()(int a,int b)const{
    return (a + b) % MOD;
  }
}a;

struct sub{
  int operator()(int a,int b)const{
    return (a + (MOD-b)) % MOD;
  }
}s;


int identity_element(const mul&){
  return 1;
}

int modInv(int x){
  return power(x,MOD-2,m);
}

const int base = 128, baseInv = modInv(base);

char str[30009];
int main() {
	int h1 = 0, h2 = 0, p = 1,k;
	cin>>k>>str;
	
	for(int i = 0,j = k - 1; i < k ; i++ , j--){
		h1 = m(h1,base);
		h1 = a(h1,str[i]);
		h2 = m(h2,base);
		h2 = a(h2,str[j]);
		if(i) p = m(p,base);
	}
	int res = 0;
	for(int i = 0, j = k; str[j - 1]; i++, j++){
		res += h1 == h2;
		h1 = s(h1,m(p,str[i]));
		h1 = m(h1,base);
		h1 = a(h1,str[j]);
		
		h2 = s(h2,str[i]);
		h2 = m(h2,baseInv);
		h2 = a(h2,m(p,str[j]));
	}
	cout << res << endl;
	return 0;
}