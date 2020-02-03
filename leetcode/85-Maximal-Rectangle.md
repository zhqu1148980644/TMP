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
class Solution {
public:
    // code in `problem 84`
    int area(vector<int> heights) {
        stack<int> s; s.push(-1);
        int res = 0, len = heights.size();
        for (int i = 0; i < len; i++) {
            while (s.top() != -1 && heights[s.top()] >= heights[i]) {
                int top = s.top(); s.pop();
                res = max(res, (i - s.top() - 1) * heights[top]);
            }
            s.push(i);
        }
        while (s.top() != -1) {
            int top = s.top(); s.pop();
            res = max(res, (len - s.top() - 1) * heights[top]);
        }
    
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