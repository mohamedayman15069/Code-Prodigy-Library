#include <bits/stdc++.h>
using namespace std; 

vector< vector<int> > adjList, comps, dagList;
vector<int> inStack, lowLink, dfn, comp, inDeg, outDeg;
stack<int> stk;
int ndfn, cntSrc, cntSnk;

void tarjan(int node) {
	lowLink[node] = dfn[node] = ndfn++, inStack[node] = 1;
	stk.push(node);

	for( auto i:  adjList[node]) {
		int ch = adjList[node][i];
		if (dfn[ch] == -1) {
			tarjan(ch);
			lowLink[node] = min(lowLink[node], lowLink[ch]);
		} else if (inStack[ch])
			lowLink[node] = min(lowLink[node], dfn[ch]);
	}

	if (lowLink[node] == dfn[node]) {
		comps.push_back(vector<int> ());
		int x = -1;
		while (x != node) {
			x = stk.top(), stk.pop(), inStack[x] = 0;
			comps.back().push_back(x);
			comp[x] = (comps.size()) - 1;
		}
	}
}

void scc() {
	int n = (adjList.size());

	inStack.clear();	inStack.resize(n);
	lowLink.clear();	lowLink.resize(n);
	dfn.clear();		dfn.resize(n, -1);
	ndfn = 0;

	comp.clear(), comp.resize(n);
	comps.clear();

	for(int i = 0 ; i < n;  i++) if (dfn[i] == -1)
		tarjan(i);
}

void computeCompGraph() {
	int csz = comps.size(), cntSrc = csz, cntSnk = csz;

	outDeg.clear();		outDeg.resize(csz);
	inDeg.clear();		inDeg.resize(comps.size());
	dagList.clear();		dagList.resize(csz);	//will contain duplicates

	for (int i = 0; i < (adjList).size(); i++)
		for (int j = 0; j < (adjList[i]).size(); j++) {
			int k = adjList[i][j];
			if (comp[k] != comp[i]) {
				dagList[comp[i]].push_back(comp[k]);	//reverse
				if (!(inDeg[comp[k]]++))		cntSrc--;
				if (!(outDeg[comp[i]]++))		cntSnk--;
			} else
				;// this edge is for a component comp[k]
		}

	/* Min edges to convert DAG to one cycle
	if (comps.size() == 1)
		cout << "0\n";
	else {
		cout << max(cntSrc, cntSnk) << "\n";
	}
	*/
}

int main() {
	// freopen("b.in", "rt", stdin);

	int cases;
	cin >> cases;

	while (cases--) {
		int n, m;
		cin >> n >> m;
		adjList.clear();
		adjList = vector<vector<int> > (n);

		for(int i = 0 ; i < n; i++) {
			int f, t;
			cin >> f >> t;
			f--, t--;
			adjList[f].push_back(t);
		}

		scc();
		computeCompGraph();

	}

	return 0;
}

	



