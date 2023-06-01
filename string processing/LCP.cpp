#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1e3 + 9,alpha = 128;
int suff[N],ID[N],newIDs[N],newsuff[N],strt[N],len;
char str[N];
int LCP[N];

void findLCP(){
	int cnt = 0;
	for(int i = 0;i < len - 1;++i){
		int j = suff[ID[i]-1];
		while(str[i+cnt] == str[j+cnt]) cnt++;
		LCP[ID[i]] = cnt;
		if(cnt) cnt--;
	}
}

void computeSuff(){
	int *head = newIDs, *nxt = newsuff;
	memset(head,-1,alpha*sizeof(head[0]));
	
	for(len = 0;!len || str[len - 1]; ++len){
		nxt[len] = head[str[len]];
		head[str[len]] = len;
	}
	int G = -1,j = 0;
	for(int i =0;i<alpha;++i){
		if(!~head[i]) continue;
		strt[++G] = j;
		for(int k = head[i];~k;k=nxt[k]){
			suff[j++] = k;
			ID[k] = G;
		}
	}
	newsuff[0] = suff[0];
	newIDs[0] = 0;
	for(int h = 1;;h<<=1){
		auto cmp = [h](int a, int b){
			return ID[a] < ID[b] || ID[a] == ID[b] && ID[a + h] < ID[b + h];
		};
		for(int i = 0;i<len;++i){
			j = suff[i] - h;
			if(j < 0) continue;
			newsuff[strt[ID[j]]++] = j;
			
		}
		for(int i = 1;i<len;++i){
			bool newGroup = cmp(newsuff[i-1],newsuff[i]);
			newIDs[i] = newIDs[i - 1] + newGroup;
			if(newGroup)
				strt[newIDs[i]] = i;
		}
		for(int i = 0;i<len;++i)
			ID[suff[i]=newsuff[i]] = newIDs[i];
		if(newIDs[len - 1] == len - 1) break;
	}
	
}

int main() {
	int n; cin>>n;
	cin>>str;
	str[n] = '$';
	cin>>(str+n+1);
	computeSuff();
	findLCP();
	int mx = 0,pos = 0;
	for(int i = 1;i<len;++i){
		if((suff[i] < n) != (suff[i - 1] < n)){
			if(LCP[i] > mx){
				pos = suff[i];
				mx = LCP[i];
			}
		}
	}
	str[mx + pos] = 0;
	cout << (str + pos) << endl;
	return 0;
}