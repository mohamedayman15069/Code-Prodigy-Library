#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;

unordered_map<int, int> ids;
int n;
int mat[100][100];

int get_id(int x){
	return ids.emplace(x, ids.size()).first -> second;
}

void floyd(){
	for(int k = 0; k < n; ++k)	
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
}

// ids.clear();
// 		do{
// 			mat[get_id(u)][get_id(v)] = 1;
// 		}while(cin >> u >> v, u || v);
