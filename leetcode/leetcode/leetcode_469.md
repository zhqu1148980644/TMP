---
title: Convex Polygon
date: 2021-01-04
---
Given a list of points that form a polygon when joined sequentially, find if this polygon is convex (Convex polygon definition).

 

#### Note:

-    There are at least 3 and at most 10,000 points.
-    Coordinates are in the range -10,000 to 10,000.
-    You may assume the polygon formed by given points is always a simple polygon (Simple polygon definition). In other words, we ensure that exactly two edges intersect at each vertex, and that edges otherwise don't intersect each other.

 

Example 1:

[[0,0],[0,1],[1,1],[1,0]]

Answer: True

Explanation:

![](https://assets.leetcode.com/uploads/2018/10/13/polygon_convex.png)

Example 2:

[[0,0],[0,10],[10,10],[10,0],[5,5]]

Answer: False

Explanation:

![](https://assets.leetcode.com/uploads/2018/10/13/polygon_not_convex.png)

#### Solutions

1. ##### cross product

```cpp
class Solution {
public:
    bool isConvex(vector<vector<int>>& points) {
        long pre = 0, len = points.size();
        for (int i = 0; i < len; i++) {
            int x1 = points[(i + 1) % len][0] - points[i][0];
            int y1 = points[(i + 1) % len][1] - points[i][1];
            int x2 = points[(i + 2) % len][0] - points[i][0];
            int y2 = points[(i + 2) % len][1] - points[i][1];
            long cur = x1 * y2 - x2 * y1;
            if (cur != 0) {
                if (cur * pre < 0)
                    return false;
                else
                    pre = cur;
            }
        }

        return true;
    }

};
```