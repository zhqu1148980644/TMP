---
title: Largest Triangle Area
date: 2021-01-04
---
You have a list of points in the plane. Return the area of the largest triangle that can be formed by any 3 of the points.

Example:
Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
Output: 2
Explanation: 
The five points are show in the figure below. The red triangle is the largest.


Notes:

3 <= points.length <= 50.
No points will be duplicated.
 -50 <= points[i][j] <= 50.
Answers within 10^-6 of the true value will be accepted as correct.

#### Solutions

1. ##### math

- Shoelace Formula: `|x1*y2 + x2*y3 + x3*y1 - x2*y1 - x3*y2 - x1*y3| / 2`

```cpp
class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int n = points.size();
        double res = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++) {
                    int x1 = points[i][0], y1 = points[i][1];
                    int x2 = points[j][0], y2 = points[j][1];
                    int x3 = points[k][0], y3 = points[k][1];
                    res = max(res, abs(x1 * y2 + x2 * y3 + x3 * y1 
                                     - x2 * y1 - x3 * y2 - x1 * y3) * 0.5);
                }
        return res;
    }
};
```