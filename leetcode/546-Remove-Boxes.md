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

1. ##### dynamic programming

- reference: the official answer
- See this promblem in a top-down perspective can make it more understandable.
- The most trivial thought about the problem is that the solution can be solved using a 2d table where `dp[i, j]` represents the maximum points we can get in the subarray `s[i:j]`. Howevever the maximum points of this subarray doesn't only depends on itself. For example:

    - `[1, 3, 2, 2, 2, 3, 2, 2]` `dp[0:4]` changes depending on whether `3` has been erased.
    - The dp table needs another dimension to records the number of continous elements with the same color as the last element of the current subarray.
    - `dp[i][j][k]` denotes the maximum points in subarray `s[i:j]` with `k` number of continous elements right to `s[j]` with value equal to `s[j]` after the last merge operation.
    - Thus, the dp transition formula is:
    - `dp[i][j][k] = max(dp[i][mid][k + 1] + dp[mid + 1, j - 1][0]) for mid in range(i, j) if s[mid] == s[j]`. ie: Firstly erases the middle parts, then leaves `k + 1` continous elements after `s[mid]` and merge the this remaining parts.


```c++
class Solution {
public:
    int solve(int dp[100][100][100], vector<int> & boxes, int i, int j, int k) {
        if (i > j) return 0;
        if (dp[i][j][k]) return dp[i][j][k];
        while (j > i && boxes[j] == boxes[j - 1]) {
            k++;
            j--;
        }
        dp[i][j][k] = solve(dp, boxes, i, j - 1, 0) + (k + 1) * (k + 1);
        for (int mid = i; mid < j; mid++) {
            if (boxes[mid] != boxes[j])
                continue;
            dp[i][j][k] = max(
                dp[i][j][k], 
                solve(dp, boxes, mid + 1, j - 1, 0) + solve(dp, boxes, i, mid, k + 1)
            );
        }
        return dp[i][j][k];
    }
    int removeBoxes(vector<int>& boxes) {
        int dp[100][100][100];
        for (auto & v1 : dp)
            for (auto & v2 : v1)
                for (auto & num : v2)
                    num = 0;
        return solve(dp, boxes, 0, boxes.size() - 1, 0);
    }
};
```