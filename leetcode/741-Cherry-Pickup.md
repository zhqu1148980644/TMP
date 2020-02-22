In a N x N grid representing a field of cherries, each cell is one of three possible integers.

 

-    0 means the cell is empty, so you can pass through;
-    1 means the cell contains a cherry, that you can pick up and pass through;
-    -1 means the cell contains a thorn that blocks your way.

 

Your task is to collect maximum number of cherries possible by following the rules below:

 

-    Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
-    After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
-    When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
-    If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.

 

 

```
Example 1:

Input: grid =
[[0, 1, -1],
 [1, 0, -1],
 [1, 1,  1]]
Output: 5
Explanation: 
The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
```

 

#### Note:

-    grid is an N by N 2D array, with 1 <= N <= 50.
-    Each grid[i][j] is an integer in the set {-1, 0, 1}.
-    It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1.


#### Solutions

1. ##### dynamic programming with memoization O(n3) S(n3)

- `dp[x1][y1][x2][y2]` represents the maximum number of cherries can be fetched when two people starting at `(x1, y1)` and `(x2, y2)` and go right/down untill they arrived at the right bottom of the grid. ie: `grid[n - 1][n - 1]`. 
- Since two people are moving synchronously, `y2` can be calculated based on `x1, y1, x2`. ie:
 `y2 = x1 + y1 - x2`.

```c++
class Solution {
public:
    vector<vector<vector<int>>> memo;
    int solve(vector<vector<int>> & grid, int x1, int y1, int x2) {
        int y2 = x1 + y1 - x2, n = grid.size();
        if (x1 >= n || y1 >= n || x2 >= n || y2 >= n)
            return -1;
        if (memo[x1][y1][x2] != INT_MIN)
            return memo[x1][y1][x2];
        if (grid[x1][y1] == -1 || grid[x2][y2] == -1)
            return memo[x1][y1][x2] = -1;
        // 4 paths
        int ans = max(max(solve(grid, x1 + 1, y1, x2 + 1), solve(grid, x1 + 1, y1, x2)), 
                      max(solve(grid, x1, y1 + 1, x2 + 1), solve(grid, x1, y1 + 1, x2)));
        // pick two times if two positions are different
        if (ans >= 0)
            ans += grid[x1][y1] + (x1 != x2 ? grid[x2, y2] : 0);

        return memo[x1][y1][x2] = ans;

    }

    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        memo = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        memo[n - 1][n - 1][n - 1] = grid[n - 1][n - 1];

        return max(0, solve(grid, 0, 0, 0));
    }
};
```


2. ##### dynamic programming with iteration O(n3) S(n2)

- reference: https://leetcode.com/problems/cherry-pickup/discuss/109903/Step-by-step-guidance-of-the-O(N3)-time-and-O(N2)-space-solution
- In the first solution, we can see that `dp[x1][y1][x2][y2]` only depends on states in `(x1 + x2) - 1`.

```c++
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));

        dp[0][0] = grid[0][0];
        int rcsum = n - 1 + n - 1;
        // rc denotes the sum of row index and column index. Increment 1 in each step.
        for (int rc = 1; rc <= rcsum; rc++) {
            // if we start from 0 to n - 1, we need an additional dp temporary matrix to store dp[rc - 1]
            for (int x1 = n - 1 ; x1 >= 0; x1--)
                for (int x2 = n - 1; x2 >= 0; x2--) {
                    int y1 = rc - x1, y2 = rc - x2;
                    if (y1 < 0 || y2 < 0 || y1 >= n || y2 >= n || grid[x1][y1] < 0 || grid[x2][y2] < 0) {
                        dp[x1][x2] = -1;
                        continue;
                    }
                    // four situations: rc is the sum of row1 and column1
                    // dp[rc - 1][r1][r2], dp[rc - 1][r1 - 1, r2], dp[rc - 1][r1, r2 - 1], dp[rc - 1][r1 - 1, r2 - 1].
                    if (x1 > 0) dp[x1][x2] = max(dp[x1][x2], dp[x1 - 1][x2]);
                    if (x2 > 0) dp[x1][x2] = max(dp[x1][x2], dp[x1][x2 - 1]);
                    if (x1 > 0 && x2 > 0)
                        dp[x1][x2] = max(dp[x1][x2], dp[x1 - 1][x2 - 1]);
                    if (dp[x1][x2] >= 0)
                        dp[x1][x2] += grid[x1][y1] + (x1 != x2 ? grid[x2][y2] : 0);
                }
        }
        return max(0, dp[n - 1][n - 1]);
    }
};
```