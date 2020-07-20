On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

```
Example 1:

Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.

Example 2:

Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
```

#### Note:

-    cost will have a length in the range [2, 1000].
-    Every cost[i] will be an integer in the range [0, 999].


#### Solutions

1. ##### dynamic programming


- `dp[i]` represents the minimum cost need to pay when reaches `staircase[i]`.
- Note: the top of the floor is the position next to the last step.


```c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        if (cost.size() <= 2)
            return 0;
        cost.push_back(0);
        int pprev = 0, prev = 0;
        for (int i = 2; i < cost.size(); i++) {
            int cur = min(pprev + cost[i - 2], prev + cost[i - 1]);
            pprev = prev;
            prev = cur;
        }
        cost.pop_back();

        return prev;
    }
};
```


- Or thought `dp[i]` as the cost need to pay when jumping at `staircase[i]`.

```c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        if (cost.size() <= 2)
            return 0;
        int pprev = cost[0], prev = cost[1];
        for (int i = 2; i < cost.size(); i++) {
            int cur = min(pprev, prev) + cost[i];
            pprev = prev;
            prev = cur;
        }

        return min(pprev, prev);
    }
};
```


2. ##### recursion with memoization

```python
class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        from functools import lru_cache
        @lru_cache(None)
        def mincost(i):
            if i <= 1:
                return 0
            else:
                return min(mincost(i - 2) + cost[i - 2], mincost(i - 1) + cost[i - 1])
        
        return mincost(len(cost))
```