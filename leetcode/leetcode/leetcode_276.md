---
title: Paint Fence
date: 2021-01-04
---
There is a fence with n posts, each post can be painted with one of the k colors.

You have to paint all the posts such that no more than two adjacent fence posts have the same color.

Return the total number of ways you can paint the fence.

Note:
n and k are non-negative integers.

Example:

Input: n = 3, k = 2
Output: 6
Explanation: Take c1 as color 1, c2 as color 2. All possible ways are:

            post1  post2  post3      
 -----      -----  -----  -----       
   1         c1     c1     c2 
   2         c1     c2     c1 
   3         c1     c2     c2 
   4         c2     c1     c1  
   5         c2     c1     c2


#### Solutions

1. ##### dynamic programming

- `dp[i] = dp[i - 2] * (k - 1) if color[i] == color[i - 1]`
- `dp[i] = dp[i - 1] * (k - 1) else`


```cpp
class Solution {
public:
    int numWays(int n, int k) {
        if (!n) return 0;
        int pprev = k, prev = k * k;
        if (n <= 2)
            return n == 2 ? prev : pprev;
        for (int i = 3; i <= n; i++) {
            int cur = (pprev + prev) * (k - 1);
            pprev = prev; prev = cur;
        }
        
        return prev;
    }
};
```


Or

- `dp[same] = dp[diff]`
- `dp[diff] = dp[diff] * (k - 1) + dp[same] * (k - 1)`

```cpp
class Solution {
public:
    int numWays(int n, int k) {
        if (!n) return 0;
        if (n == 1) return k;
        int same = k, diff = k * (k - 1);

        for (int i = 3; i <= n; i++) {
            int prediff = diff;
            diff = (same + diff) * (k - 1);
            same = prediff;
        }
        return same + diff;
    }
};
```