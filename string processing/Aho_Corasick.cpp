#include <bits/stdc++.h>
using namespace std;

const int alpha = 128;
vector<vector<int> >child;
vector<vector<char> >childChars;
vector<int>id,fail,nxt;

int addNode(){
	child.push_back(vector<int>(alpha,-1));
	childChars.push_back(vector<char>());
	id.push_back(-1);
	fail.push_back(-1);
	nxt.push_back(-1);
	return id.size()-1;
}

void init(){
	child.clear();
	childChars.clear();
	id.clear();
	fail.clear();
	nxt.clear();
	addNode();
}

int insert(const char *str,int curID){
	int cur;
	for(cur = 0; *str; str++){
		if(!~child[cur][*str]){
			childChars[cur].push_back(*str);
			int x = addNode();
			child[cur][*str] = x;
		}
		cur = child[cur][*str];
	}
	if(id[cur] == -1)
		id[cur] = curID;
	
	return id[cur];
}

void compF(){
	fail[0] = nxt[0] = 0;
	queue<int>Q;
	for(int i = 0;i<alpha;i++){
		if(~child[0][i]){
			Q.push(child[0][i]);
			nxt[Q.back()] = 0;
			fail[Q.back()] = 0;
		}
		else{
			child[0][i] = 0;
		}
	}
	while(Q.size()){
		int u = Q.front();
		Q.pop();
		for(auto chr : childChars[u]){
			int v = child[u][chr];
			int f = fail[u];
			while(!~child[f][chr])
				f = fail[f];
			f = child[f][chr];
			fail[v] = f;
			nxt[v] = f;
			Q.push(v);
		}
	}
}

int nxtNode(int u){
	if(!u) return u;
	return ~id[nxt[u]] ? nxt[u] : nxt[u] = nxtNode(nxt[u]);
}

vector<vector<int>>match(char *str,int len){
	vector<vector<int>>ret(len);
	char *b = str;
	for(int cur = 0;*str;str++){
		while(!~child[cur][*str])
			cur = fail[cur];
		cur = child[cur][*str];

		for(int x = cur;x; x = nxtNode(x)){
			if(~id[x]) ret[id[x]].push_back(str-b);
		}
	}
	return ret;
}
char arr[100009],sarr[1005];


int main() {
	int t,ns;
	int ar[1009];
	cin>>t;
	while(t--){
		cin>>arr;
		cin>>ns;
		init();
		for(int i =0;i<ns;i++){
			cin>>sarr;
			ar[i] = insert(sarr,i);
		}
	compF();
	/*for(int i = 0;i < id.size();i++){
		for(auto c:childChars[i]){
			int j = child[i][c];
			printf("%d,%d %d,%d %c\n",i,id[i],j,id[j],c);
		}
		int j = fail[i];
		printf("%d,%d %d,%d\n",i,id[i],j,id[j]);
	}
	return 0;*/
	auto ret = match(arr,ns);
	int cnt = 0;
	for(int i = 0; i < ns;i++){
		cout << (ret[ar[i]].empty() ? "n" : "y" )<< endl; 
	}
}
}