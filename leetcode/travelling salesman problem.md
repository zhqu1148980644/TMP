From wikipedia

The travelling salesman problem (also called the travelling salesperson problem[1] or TSP) asks the following question: "Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city and returns to the origin city?


Inputs:
- the first digit is the number of cities and the rest are pairwise distand in matrix format.

```
4
0 2 6 5
2 0 4 4
6 4 0 2
5 4 2 0

# should output
13
```


#### Solutions


1. ##### dynamic programming O(2^n * n2)

```c++
#include <bits/stdc++.h>
using namespace std;

int solve(vector<vector<int>> & dis, int n) {
    int maxs = 1 << n, INF = 0x3f3f3f3f;
    // visited is a set represented as a bitmap
    // dp[vsited][end] represents the minimum cost path ended at `end` with `visited` being visited.
    vector<vector<int>> dp(maxs, vector<int>(n, INF));
    dp[1][0] = 0;
    // iterating all sates in ascending order to makre sure former states are being calculated
    for (int s = 1; s < maxs; s++) {
        // the path must starting from `0`
        if (!(s & 1)) continue;
        // adding new cities into the set
        for (int cur = 1; cur < n; cur++) {
            // do not visit again
            if (s & (1 << cur)) continue;
            for (int prev = 0; prev < n; prev++) {
                // prev must be already within the path
                if (prev == cur || !(s & (1 << prev)))
                    continue;
                auto & mindis = dp[s | (1 << cur)][cur];
                // dp[visited + cur][cur] = dp[visited][prev] + dis[prev][cur]
                mindis = min(mindis, dp[s][prev] + dis[prev][cur]);
            }
        }
    }
    
    // mincost = dp[all being visited][end] + dis[end][0] for all possible end
    int mincost = INF;
    for (int end = 1; end < n; end++)
        mincost = min(mincost, dp[maxs - 1][end] + dis[end][0]);

    return mincost;
}

int main(int argc, const char * argv[]) {
    int n, w; cin >> n;
    vector<vector<int>> dis(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> w;
            dis[i][j] = w;
        }
    cout << solve(dis, n) << endl;
}

```