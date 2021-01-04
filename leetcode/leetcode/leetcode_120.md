---
title: Triangle
date: 2021-01-04
---
#### Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

```
For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
```

#### Note:

- Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.


#### Solutions

1. ##### top-down dynamic programming

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (!triangle.size()) return 0;
        vector<int> dp(triangle.size());
        dp[0] = triangle[0][0];

        for (int i = 1; i < triangle.size(); i++) {
            int prel = dp[0];
            dp[0] += triangle[i][0];
            for (int j = 1; j < i; j++) {
                int up = dp[j];
                dp[j] = min(prel, up) + triangle[i][j];
                prel = up;
            }
            dp[i] = prel + triangle[i][i];
        }

        return *min_element(dp.begin(), dp.end());
    }
};
```

2. ##### bottom-up dynamic programming


```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> minpath(triangle.back());

        for (int i = triangle.size() - 2; i >= 0; i--)
            for (int j = 0; j <= i; j++)
                minpath[j] = min(minpath[j], minpath[j + 1]) + triangle[i][j];

        return minpath[0];
    }
};
```


Or a inplace version

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {

        for (int i = triangle.size() - 2; i >= 0; i--) {
            for (int j = 0; j < i + 1; j++)
                triangle[i][j] = min(triangle[i + 1][j], triangle[i + 1][j + 1])
                                 + triangle[i][j];
        }

        return triangle[0][0];
    }
};
```