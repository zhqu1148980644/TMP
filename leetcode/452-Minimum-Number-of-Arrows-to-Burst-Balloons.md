#### There are a number of spherical balloons spread in two-dimensional space. For each balloon, provided input is the start and end coordinates of the horizontal diameter. Since it's horizontal, y-coordinates don't matter and hence the x-coordinates of start and end of the diameter suffice. Start is always smaller than end. There will be at most 104 balloons.

An arrow can be shot up exactly vertically from different points along the x-axis. A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. There is no limit to the number of arrows that can be shot. An arrow once shot keeps travelling up infinitely. The problem is to find the minimum number of arrows that must be shot to burst all balloons.

```
Example:

Input:
[[10,16], [2,8], [1,6], [7,12]]

Output:
2
```

#### Explanation:
One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).


#### Solutions

- Check `problem 435` which is solved by greedy method too.

1. ##### greedy method

- Sort by start of each balloon.

```c++
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (!points.size()) return 0;
        sort(points.begin(), points.end());

        int arrow = 1, prevend = points[0][1];
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > prevend) {
                arrow++;
                prevend = points[i][1];
            }
            else
                prevend = min(prevend, points[i][1]);
        }

        return arrow;
    }
};
```

- Or sort by end, then there is no need to update the minimum end of intervals.

```c++
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (!points.size()) return 0;
        sort(points.begin(), points.end(), [](vector<int> & v1, vector<int> & v2) {
            return v1[1] <= v2[1];
        });

        int arrow = 1, prevend = points[0][1];
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > prevend) {
                arrow++;
                prevend = points[i][1];
            }
        }

        return arrow;
    }
};
```