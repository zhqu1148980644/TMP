#### You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

```
Example 1:

Input: coins = [1, 2, 5], amount = 11
Output: 3 
Explanation: 11 = 5 + 5 + 1

Example 2:

Input: coins = [2], amount = 3
Output: -1
```

#### Note:
You may assume that you have an infinite number of each kind of coin.


#### Solutions

1. ##### dynamic programming

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> mincom(amount + 1, amount + 1);
        mincom[0] = 0;
        for (int total = 1; total <= amount; total++) {
            for (auto & coin : coins) {
                if (coin > total) continue;
                mincom[total] = min(mincom[total], mincom[total - coin] + 1);
            }
        }
        return mincom[amount] <= amount ? mincom[amount] : -1;
    }
};
```

2. ##### recursion with memoization

```python
class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        from functools import lru_cache
        @lru_cache(None)
        def min_coin(total):
            if not total:
                return 0
            return min(
                [min_coin(total - coin) + 1
                 for coin in coins if coin <= total] or [amount + 1]
            )
        count = min_coin(amount)
        return count if count <= amount else -1

```

3. ##### backtrack or dfs

```c++

```

4. ##### bfs

```c++

```