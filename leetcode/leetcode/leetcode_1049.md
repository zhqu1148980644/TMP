---
title: Last Stone Weight II
date: 2021-01-04
---
We have a collection of rocks, each rock has a positive integer weight.

Each turn, we choose any two rocks and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:

If x == y, both stones are totally destroyed;
If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
At the end, there is at most 1 stone left.  Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)

 

Example 1:

Input: [2,7,4,1,8,1]
Output: 1
Explanation: 
We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.
 

Note:

1 <= stones.length <= 30
1 <= stones[i] <= 100

#### Solutions


1. ###### dynamic programming

- The problem can be solved by grouping stones into two groups, then plus all stones in one group and decrease for the other group, find the minimum remaining stone equals to find these two groups with minimum difference. ie: `min(+ (x1 x2 x4 x5)  - (x0 x3 x6 x7...))`
- `dp[cap]` represents the maximum sum weight of stones can be achieved with capacity(weight sum limit) `cap`. This is similar to `01 knapsack problem`.

```cpp
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        if (stones.size() <= 1) return sum;
        // sum1 + sum2 == sum, try to find min(abs(sum1 - sum2))
        // since they are mirrored, we choose to find the smaller one between sum1 and sum2
        int half = sum / 2;
        vector<int> dp(half + 1);
        for (int i = 0; i < stones.size(); i++)
            // reverse iterating capacities to avoid overwiriting
            for (int w = half; w > 0; w--) {
                if (w < stones[i]) break;
                // neither choose the current stone or not
                dp[w] = max(dp[w], stones[i] + dp[w - stones[i]]);
            }

        return abs(sum - dp[half] - dp[half]);
    }
};
```