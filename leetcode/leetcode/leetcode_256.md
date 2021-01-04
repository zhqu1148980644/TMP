---
title: Paint House
date: 2021-01-04
---
#### There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

#### Note:
All costs are positive integers.

```
Example:

Input: [[17,2,17],[16,16,5],[14,3,19]]
Output: 10
Explanation: Paint house 0 into blue, paint house 1 into green, paint house 2 into blue. 
             Minimum cost: 2 + 5 + 3 = 10.
```

#### Solutions

1. ##### dynamic programming

```cpp
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (!costs.size()) return 0;
        vector<int> dp(3);
        for (auto & c : costs){
            vector<int> dp1(3);
            dp1[0] = min(dp[1], dp[2]) + c[0];
            dp1[1] = min(dp[0], dp[2]) + c[1];
            dp1[2] = min(dp[0], dp[1]) + c[2];
            dp = move(dp1);
        }
        return min(dp[0], min(dp[1], dp[2]));
    }
};
```