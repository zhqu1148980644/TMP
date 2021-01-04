---
title: Spiral Matrix II
date: 2021-01-04
---
#### Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

```
Example:

Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
```

#### Solutions

1. ##### Straight forward

- Follow the strategy used in problem 54.
- Knowning the resulting matrix is square makes this problem much easier.

```cpp
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int i = 0, j = 0, cur = 1, num = n, step;
        while (true) {
            if (num <= 0) break;
            res[i][j] = cur++;
            // Break here otherwise the program will enter the 4'th while loop(-1 is true).
            if (num == 1) break;
            step = num; while (--step) res[i][++j] = cur++;
            step = num; while (--step) res[++i][j] = cur++;
            step = num; while (--step) res[i][--j] = cur++;
            // Do not move the last step otherwise the first item in this layer will be overitten.
            step = num - 1; while (--step) res[--i][j] = cur++;
            j++; num -= 2;
        }
        return res;
    }
};
```
