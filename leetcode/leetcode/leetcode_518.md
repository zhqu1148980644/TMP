---
title: Coin Change 2
date: 2021-01-04
---
You are given coins of different denominations and a total amount of money. Write a function to compute the number of combinations that make up that amount. You may assume that you have infinite number of each kind of coin.

 

Example 1:

Input: amount = 5, coins = [1, 2, 5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
Example 2:

Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.
Example 3:

Input: amount = 10, coins = [10] 
Output: 1
 

Note:

You can assume that

0 <= amount <= 5000
1 <= coin <= 5000
the number of coins is less than 500
the answer is guaranteed to fit into signed 32-bit integer

#### Solutions

1. ##### dynamic programming

- Similar to unbounded knapsack problem.
- `dp[i][amount`] represents the number of combinations within `coins[:i]` with sum equals to amount.
-  Note that if we `swap` the looping order of coins and amounts, the final result is the number of permutations sums to the given amount.


```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1);
        dp[0] = 1;
        for (auto coin : coins)
            for (int i = coin; i <= amount; i++)
                dp[i] += dp[i - coin];

        return dp[amount];
    }
};
```