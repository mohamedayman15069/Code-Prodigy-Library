#include <bits/stdc++.h>
using namespace std;

#define all(v)			((v).begin()), ((v).end())
#define sz(v)			((int)((v).size()))
#define clr(v, d)		memset(v, d, sizeof(v))
#define rep(i, v)		for(int i=0;i<sz(v);++i)
#define lp(i, n)		for(int i=0;i<(int)(n);++i)
#define lpi(i, j, n)	for(int i=(j);i<(int)(n);++i)
#define lpd(i, j, n)	for(int i=(j);i>=(int)(n);--i)
typedef long long ll;

// Switch between even odd: (0, 1), (2, 3)..
#define NOT(x)    (1^(x))


int n, m, ndfn;
vector< vector<int> > adjList, comps, dagList;
vector<int> inStack, lowLink, dfn, comp, assigned_val, cmp_root_node;
stack<int> stk;

void tarjan(int node) {
	lowLink[node] = dfn[node] = ndfn++, inStack[node] = 1;
	stk.push(node);

	rep(i, adjList[node]) {
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
			comp[x] = sz(comps) - 1;
		}
		cmp_root_node[ comp[node] ] = node;		// ***
	}
}

void scc() {
	int n = sz(adjList);

	inStack.clear();		inStack.resize(n);
	lowLink.clear();		lowLink.resize(n);
	assigned_val.clear();	assigned_val.resize(n);
	cmp_root_node.clear();		cmp_root_node.resize(n);
	dfn.clear();			dfn.resize(n, -1);
	ndfn = 0;

	comp.clear(), comp.resize(n);
	comps.clear();

	lp(i, n) if (dfn[i] == -1)
		tarjan(i);
}

// acceptable values: (0, 1), (1, 0), (1, 1)
void add_or(int a, int b)
{
	adjList[NOT(a)].push_back(b);
	adjList[NOT(b)].push_back(a);
}

// acceptable values: (0, 1), (1, 0)
void add_or_not_both(int a, int b)
{
	// CNF: (a v b) & (!a v !b)  ==> E.g. can't be true for (1, 1) / (0, 0)
	add_or(a, b);
	add_or(NOT(a), NOT(b));
}

void force_value(int i, bool b)
{
	if(b)
		adjList[NOT(i)].push_back(i);
	else
		adjList[i].push_back(NOT(i));
}

bool is_solvable()
{
    for(int i = 0 ; i < n ; i += 2)
        if( comp[i] == comp[NOT(i)] )
                return false;
    return true;
}

void assign_values()
{
	vector<int> comp_assigned_value(comps.size(), -1);

	lp(i, comps.size()) {
		if (comp_assigned_value[i] == -1){
			comp_assigned_value[i] = 1;
			int not_ithcomp = comp[ NOT(cmp_root_node[i]) ];
			comp_assigned_value[ not_ithcomp ] = 0;
		}
	}

	lp(i, n)
		assigned_val[i] = comp_assigned_value[ comp[i] ];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("test.txt", "rt", stdin);
#endif

	while(cin>>n>>m && (n+m))
	{
		adjList.clear();
		adjList.resize(n);
        int a,b;
		lp(i, m)
		{
			cin>>a>>b;
			
			add_or(a, b);
		}

		scc();

		if (!is_solvable())
		{
			cout<<"no solution\n";
			continue;
		}

		assign_values();	// solution in assign_values array
	}

	return 0;
}