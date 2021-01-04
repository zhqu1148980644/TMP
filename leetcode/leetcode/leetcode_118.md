---
title: Pascal's Triangle
date: 2021-01-04
---
#### Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

![](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

```
Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
```

#### Solutions

1. ##### Straight forward

```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows < 1) return {};
        vector<vector<int>> res{{1}};

        for (int i = 1; i < numRows; i++) {
            res.push_back(vector<int>(i + 1, 0));
            auto & lastv = res[i - 1];
            auto & curv = res[i];

            curv[0] = 1;
            for (int j = 1; j < i; j++)
                curv[j] = lastv[j - 1] + lastv[j];
            curv[i] = 1;
        }

        return res;
    }
};
```