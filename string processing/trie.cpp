#include <bits/stdc++.h>
using namespace std;

const int alpha = 128;
vector<vector<int> >child;
vector<vector<char> >childChars;
vector<bool>isEnd;

int addNode(){
	child.push_back(vector<int>(alpha,-1));
	childChars.push_back(vector<char>());
	isEnd.push_back(false);
	return isEnd.size()-1;
}

void init(){
	child.clear();
	childChars.clear();
	isEnd.clear();
	addNode();
}

void insert(const char *str){
	int cur;
	for(cur = 0; *str; str++){
		if(!~child[cur][*str]){
			childChars[cur].push_back(*str);
			int x = addNode();
			child[cur][*str] = x;
		}
		cur = child[cur][*str];
		// if(isEnd[cur]) return false;
	}
	isEnd[cur] = true;
	// return childChars[cur].empty();
}