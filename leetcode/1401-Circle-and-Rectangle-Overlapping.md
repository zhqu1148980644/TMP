Given a circle represented as (radius, x_center, y_center) and an axis-aligned rectangle represented as (x1, y1, x2, y2), where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the rectangle.

Return True if the circle and rectangle are overlapped otherwise return False.

In other words, check if there are any point (xi, yi) such that belongs to the circle and the rectangle at the same time.

 

```
Example 1:



Input: radius = 1, x_center = 0, y_center = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
Output: true
Explanation: Circle and rectangle share the point (1,0) 
Example 2:



Input: radius = 1, x_center = 0, y_center = 0, x1 = -1, y1 = 0, x2 = 0, y2 = 1
Output: true
Example 3:



Input: radius = 1, x_center = 1, y_center = 1, x1 = -3, y1 = -3, x2 = 3, y2 = 3
Output: true
Example 4:

Input: radius = 1, x_center = 1, y_center = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1
Output: false
```
 

Constraints:

1 <= radius <= 2000
-10^4 <= x_center, y_center, x1, y1, x2, y2 <= 10^4
x1 < x2
y1 < y2

#### Solutions

1. ##### math

- reference: https://www.zhihu.com/question/24251545

```c++
class Solution {
public:
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
        // center of rectangle as (0, 0)
        double cx = (x2 + x1) / 2.0, cy = (y2 + y1) / 2.0;
        // transform the circle into the first quadrant
        double vx = abs(x_center - cx), vy = abs(y_center - cy);
        // vector of the top right vertex of the rectangle
        double hx = x2 - cx, hy = y2 - cy;
        //  vector v - h, with negative value omitted.
        double ux = max(0., vx - hx), uy = max(0., vy - hy);
        // check |u|2 <= radius
        return ux * ux + uy * uy <= radius * radius;
    }
};
```