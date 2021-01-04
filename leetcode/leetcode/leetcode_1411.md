---
title: Number of Ways to Paint N × 3 Gri
date: 2021-01-04
---
You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colours: Red, Yellow or Green while making sure that no two adjacent cells have the same colour (i.e no two cells that share vertical or horizontal sides have the same colour).

You are given n the number of rows of the grid.

Return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 10^9 + 7.

![](https://assets.leetcode.com/uploads/2020/03/26/e1.png)

```
Example 1:

Input: n = 1
Output: 12
Explanation: There are 12 possible way to paint the grid as shown:

Example 2:

Input: n = 2
Output: 54
Example 3:

Input: n = 3
Output: 246
Example 4:

Input: n = 7
Output: 106494
Example 5:

Input: n = 5000
Output: 30228214
```
 

Constraints:

n == grid.length
grid[i].length == 3
1 <= n <= 5000


#### Solutions

1. ##### dynamic programming

- To ensure that there are no two adjacent cells have the same color in horizontal side, only `12` tiles listed in the first example can be staked, and the answer of `n` rows can be calculated based on the answer of `n - 1` rows. ie: stacking new tiles that satisfy the requirement in virtical side.
- `dp[n][tile_id]` represents the number of solutions with `n` nrows that the bottom tile is `tiles[tile_id]`.

```cpp
class Solution {
public:
    vector<vector<int>> possible_stacks() {
        string vs[12] = {
            "121", "212", "312", 
            "123", "213", "313", 
            "131", "231", "321", 
            "132", "232", "323"
        };
        vector<vector<int>> res(12);
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                if (i == j) continue;
                bool valid = true;
                for (int k = 0; k < 3; k++)
                    if (vs[i][k] == vs[j][k]) {
                        valid = false;
                        break;
                    }
                if (valid) res[i].push_back(j);
            }
        }
        
        return res;
    }
    
    int numOfWays(int n) {
        vector<int> dp(12, 1);
        vector<vector<int>> change = possible_stacks();

        for (int i = 2; i <= n; i++) {
            vector<int> dp1(12);
            for (int i = 0; i < 12; i++)
                for (auto c : change[i])
                    dp1[c] = (dp1[c] + dp[i]) % 1000000007;
            dp = move(dp1);
        }

        return accumulate(dp.begin(), dp.end(), 0l) % 1000000007l;
    }
};
```

2. ##### optimized version

- More concisely, the number of states can be reduced to `2`. 
    - e.g. there are no differences among `y-r-y`, `r-y-r`, `y-g-y`......
    - `dp[n][0]` represents the number of solutions with the bottom tile containing two different colors.
    - `dp[n][1]` ...                                                     containing three different colors.
    - `dp[1][0] = 6` and `dp[1][1] = 6`.
- The dp formula can be fetched by counting the number of possible changes based on the figure in example1.

```cpp
class Solution {
public:

    int numOfWays(int n) {
        vector<long> dp(2, 6);

        for (int i = 2; i <= n; i++) {
            vector<long> dp1(12);
            dp1[0] = (dp[0] * 3 + dp[1] * 2) % 1000000007;
            dp1[1] = (dp[0] * 2 + dp[1] * 2) % 1000000007;
            dp = move(dp1);
        }

        return accumulate(dp.begin(), dp.end(), 0l) % 1000000007l;
    }
};
```