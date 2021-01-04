---
title: Rectangle Area
date: 2021-01-04
---
#### Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Rectangle Area

![](https://assets.leetcode.com/uploads/2018/10/22/rectangle_area.png)

```
Example:

Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
Output: 45
```

#### Note:

-Assume that the total area is never beyond the maximum possible value of int.

#### Solutions

1. ##### Intersection over Union (IoU)

- borrowed from others
- IOU is used for object detection.
- Find 4 borders of overlapped area.

```cpp
class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int area1 = (C - A) * (D - B);
        int area2 = (G - E) * (H - F);

        if (H <= B || E >= C || F >= D || G <= A)
            return area1 + area2;
        else {
            int top = min(D, H);
            int left = max(A, E);
            int right = min(C, G);
            int bottom = max(B, F);
            return area1 - ((top - bottom) * (right - left)) + area2;
        }
    }
};
```