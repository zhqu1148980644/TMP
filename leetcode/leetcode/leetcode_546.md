---
title: Remove Boxes
date: 2021-01-04
---
#### Given several boxes with different colors represented by different positive numbers.
You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
Find the maximum points you can get.

```
Example 1:
Input:

[1, 3, 2, 2, 2, 3, 4, 3, 1]

Output:

23

Explanation:

[1, 3, 2, 2, 2, 3, 4, 3, 1] 
----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
----> [1, 3, 3, 3, 1] (1*1=1 points) 
----> [1, 1] (3*3=9 points) 
----> [] (2*2=4 points)
```

#### Note: The number of boxes n would not exceed 100. 

#### Solutions

1. ##### dynamic programming with memoization

- reference: the official answer
- See this promblem in a top-down perspective can make it more understandable.
- The most trivial thought about the problem is that the solution can be solved using a 2d table where `dp[i, j]` represents the maximum points we can get in the subarray `s[i:j]`. Howevever the maximum points of this subarray doesn't only depends on itself. For example:

    - `[1, 3, 2, 2, 2, 3, 2, 2]` `dp[0:4]` changes depending on whether `3` has been erased.
    - The dp table needs another dimension to records the number of continous elements with the same color as the last element of the current subarray.
    - `dp[i][j][k]` denotes the maximum points in subarray `s[i:j]` with `k` number of continous elements right to `s[j]`(not include s[j]) with value equal to `s[j]` after the last merge operation.
    - Thus, the dp transition formula is:
    - `dp[i][j][k] = max(dp[i][mid][k + 1] + dp[mid + 1, j - 1][0]) for mid in range(i, j) if s[mid] == s[j]`. ie: Firstly erases the middle parts `s[mid + 1: j - 1]`, then leaves `k + 1` continous elements after `s[j:]` and merge this trailing part with prefix `s[:mid]`if `s[mid] == s[j]`.


```cpp
class Solution {
public:
    int solve(int (&dp)[100][100][100], vector<int> & boxes, int i, int j, int len) {
        if (i > j) return 0;
        if (dp[i][j][len]) return dp[i][j][len];
        while (i < j && boxes[j] == boxes[j - 1]) {
            len++; j--;
        }
        dp[i][j][len] = solve(dp, boxes, i, j - 1, 0) + (len + 1) * (len + 1);
        for (int mid = j - 1; mid >= i; mid--)
            if (boxes[mid] == boxes[j])
                dp[i][j][len] = max(dp[i][j][len], solve(dp, boxes, i, mid, len + 1)
                                                 + solve(dp, boxes, mid + 1, j - 1, 0));
        return dp[i][j][len];
    }
    int removeBoxes(vector<int>& boxes) {
        int dp[100][100][100] = {0};
        return solve(dp, boxes, 0, boxes.size() - 1, 0);
    }
};
```

2. ##### dynamic programming with iteration


```cpp

```