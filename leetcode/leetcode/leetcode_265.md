---
title: Paint House II
date: 2021-01-04
---
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Example:

Input: [[1,5,3],[2,9,4]]
Output: 5
Explanation: Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5; 
             Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5. 
Follow up:
Could you solve it in O(nk) runtime?


#### Solutions


1. ###### dynamic programming

```cpp
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (!costs.size()) return 0;
        vector<int> dp(costs[0]);

        for (int i = 1; i < costs.size(); i++) {
            int min1 = INT_MAX, min2 = INT_MAX, min1i = 0;
            for (int i = 0; i < dp.size(); i++) {
                if (dp[i] < min1) {
                    min2 = min1; min1 = dp[i]; min1i = i;
                }
                else if (dp[i] < min2)
                    min2 = dp[i];
            }
            vector<int> dp1(costs[i]);
            for (int i = 0; i < dp1.size(); i++)
                if (i == min1i) dp1[i] += min2;
                else dp1[i] += min1;
            dp = move(dp1);
        }

        return *min_element(dp.begin(), dp.end());
    }
};
```