---
title: Maximal Rectangle
date: 2021-01-04
---
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

```
Example:

Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
```


#### Solutions

- For a given row, we can thought the number of continuous `1` above as bars with different heights, then this problem is converted to `problem 84`.
- In `problem 84`, we can fetch the maximum area within a histogram in `O(n)` time, thus the complexity of this problem can reach `O(n2)`. ie: `O(ncol * O(nrow))`.

1. ##### straight forward O(n3)

- This solution uses the brute-force method in `problem 84` after we transformed the input matrix into bars.


```cpp
class Solution {
public:
    int area(vector<int> & nums) {
        int res = 0;
        for (int j = 0; j < nums.size(); j++) {
            int h = nums[j];
            res = max(res, h);
            for (int i = j - 1; i >= 0; i--) {
                h = min(h, nums[i]);
                res = max(res, h * (j - i + 1));
            }
        }
        return res;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(); if (!m) return 0;
        int n = matrix[0].size();
        
        int res = 0;
        vector<int> heights(n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1: 0;
            res = max(res, area(heights));
        }

        return res;
    }
};
```


or combine loops in two functions.

```cpp
// treat as horizontal bars.
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(); if (!m) return 0;
        int n = matrix[0].size();
        vector<vector<int>> width(m, vector<int>(n));
        int res = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1')
                    width[i][j] = j ? width[i][j - 1] + 1 : 1;
                int area = width[i][j], w = area;
                // w * (i + 1) > res is a pruning step
                for (int k = i - 1; w * (i + 1) > res && k >= 0; k--) {
                    w = min(w, width[k][j]);
                    area = max(area, w * (i - k + 1));
                }
                res = max(area, res);
            }
        }
        
        return res;
    }
};
```


2. ##### stack O(n2)

- The same as the optimized stack solution in `problem 84`.

```cpp
// treat as vertical bars
class Solution {
public:
    // code in problem 84
    int area(vector<int> & heights) {
        stack<int> s; s.push(-1);
        heights.push_back(-1);
        int res = 0;
        for (int i = 0; i < heights.size(); i++) {
            while (s.top() != -1 && heights[s.top()] > heights[i]) {
                int h = heights[s.top()]; s.pop();
                res = max(res, (i - s.top() - 1) * h);
            }
            s.push(i);
        }
        heights.pop_back();
        return res;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(); if (!m) return 0;
        int n = matrix[0].size();
        vector<int> heights(n);
        int res = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
            res = max(res, area(heights));
        }
        return res;
    }
};
```


3. ##### dynamic programming

- See official answer for details.
- The maximum rectangle extened from a given position(at the bottom of the rectangle) can be fetched by:
    - streches up untill meets a `0` cell which represents the top edge of the rectangle.
    - streches left/right to find the left/right edge.
    - The rectangle after streching contains only `1` cells.
- `left[j] = coln` means the leftmost column that can be streched to when extending from `matrix[i][j]`(as the bottom of the rectangle).

```cpp
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(); if (!m) return 0;
        int n = matrix[0].size();

        vector<int> height(n), left(n), right(n, n - 1);

        int res = 0;
        for (int i = 0; i < m; i++) {
            int curl = 0, curr = n - 1;
            for (int j = n - 1; j >= 0; j--) {
                // if the current cell is 1, then the right bound will be constrained by both rows(the current row and the above row)
                // as the stretching may reach the above row.
                if (matrix[i][j] == '1')
                    right[j] = min(curr, right[j]);
                // else, the stretching in the current column will not reach this row, the right bound is freed
                else {
                    right[j] = n - 1;
                    curr = j - 1;
                }
            }

            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1')
                    left[j] = max(curl, left[j]);
                // the same, the left bound in the next row will not depend on the current row
                else {
                    left[j] = 0;
                    curl = j + 1;
                }
            }
            // This for loop can be combined with the previous one.
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1')
                    res = max(res, ++height[j] * (right[j] - left[j] + 1));
                else
                    height[j] = 0;
            }
        }
        return res;
    }
};
```

- Python version with bit operation.
- reference: https://leetcode-cn.com/problems/maximal-rectangle/comments/65610