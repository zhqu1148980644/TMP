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

- For each column, we can thought the number of continuous `1` left to each item as the height of each bar, then this problem is converted to `problem 84`.
- In `problem 84`, we can fetch the maximum area within a histogram in `O(n)` time, thus the complexity of this problem can reach `O(n2)`. ie: `O(ncol * O(nrow))`.

1. ##### straight forward O(n3)

- This solution uses the brute-force method in `problem 84` after we transformed the input matrix into bars.


```c++
// treat as  horizontal bars.
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

```c++
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
    - streches up untill meets a 0 cell which represents the top edge of the rectangle.
    - streches left/right to find the left/right edge.
- `left[j] = coln` means the leftmost column that can be covered for the largest rectangle extended from `matrix[i][j]`.

```c++
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(); if (!m) return 0;
        int n = matrix[0].size();
        int height[n] = {0}, left[n] = {0}, right[n] = {0};
        for (int j = n - 1; j >= 0; j--)
            right[j] = n - 1;
        int res = 0;
        for (int i = 0; i < m; i++) {
            int curleft = 0, curright = n - 1;

            for (int j = n - 1; j >= 0; j--) {
                if (matrix[i][j] == '1')
                    right[j] = min(right[j], curright);
                else {
                    // right[j] = n - 1 means the next row doest not depends on the current row
                    right[j] = n - 1;
                    curright = j - 1;
                }
            }
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    height[j] = i ? height[j] + 1 : 1;
                    left[j] = max(left[j], curleft);
                }
                else {
                    // left[j] = 0 means the next row donesn't depends in the current row
                    height[j] = left[j] = 0;
                    curleft = j + 1;
                }
                res = max(res, (right[j] - left[j] + 1) * height[j]);
            }
        }

        return res;
    }
};
```

- Python version bit bit operation.
- reference: https://leetcode-cn.com/problems/maximal-rectangle/comments/65610