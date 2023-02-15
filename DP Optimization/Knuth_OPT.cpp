#include <bits/stdc++.h>
using namespace std; 


/*
This type of optimization is only applicable for Range DP problems with the following properties:
1. The recurrence relation is of the form: dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + cost(i, j, k))
2. The recurrence relation is associative: (a op b) op c = a op (b op c)
3. Further, the cost function must satisfy the following conditions (for a ≤ b ≤ c ≤ d) –
    a. It is a Monotone on the lattice of intervals (MLI) [cost(b, c) ≤ cost(a, d)]
    b. It satisfies the quadrangle inequality (QI) [cost(a, c) + cost(b, d) ≤ cost(b, c) + cost(a, d)]

What is happening is as follows: 

1. Just add a new dp transition, call it opt(i,j). 
2. opt[i][j] = argmini≤k<j(dp[i][k] + dp[k+1][j])
        If opt[i][j-1] ≤ opt[i][j] ≤ opt[i+1][j], we can use knuth's Optimization
*/
//Generic Implementation of Knuth's Optimization
int solve() {
    int N;
    //... // read N and input
    int dp[N][N], opt[N][N];

    auto C = [&](int i, int j) {
    //    ... // Implement cost function C.
        return 0; //cost of interval [i, j]
    };

    for (int i = 0; i < N; i++) {
        opt[i][i] = i;
      //  ... // Initialize dp[i][i] according to the problem
    }

    for (int i = N-2; i >= 0; i--) {
        for (int j = i+1; j < N; j++) {
            int mn = INT_MAX;
            int cost = C(i, j);
            for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k+1][j] + cost; 
                }
            }
            dp[i][j] = mn; 
        }
    }

    cout << dp[0][N-1] << endl;
}