#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 9;
char P[MAX],str[MAX];
int F[MAX];

int getNxtLen(int len,char c){
	while(len && P[len] != c)
		len = F[len - 1];
	len += (P[len] == c);
	return len;
}

void Find_F(){
	if(!P[0]) return;
	F[0] = 0;
	for(int i = 1;P[i];++i)
		F[i] = getNxtLen(F[i-1],P[i]);
}

vector<int> match(){
	vector<int> result;
	int len = 0;
	for(int i = 0; str[i]; ++i){
		len = getNxtLen(len,str[i]);
		if(!P[len]) result.push_back(i - len + 1);
	}
	return result;
}


vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}