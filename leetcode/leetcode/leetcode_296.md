---
title: Best Meeting Point
date: 2021-01-04
---
A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

Example:

Input: 

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 6 

Explanation: Given three people living at (0,0), (0,4), and (2,2):
             The point (0,2) is an ideal meeting point, as the total travel distance 
             of 2+2+2=6 is minimal. So return 6.


#### Solutions


1. ##### find midians of people in two axis O(mn)

- Since mahantan distance is additive, the summing of distances in two axis are independent.
- For a certain axis, the origin with the lowest summing distance is the point(`(n-1)/2`) with the same amount of people in two sides.


```cpp
class Solution {
public:
    int dis(vector<int> & x, int origin) {
        int res = 0;
        for (auto n : x)
            res += abs(n - origin);
        return res;
    }
    int minTotalDistance(vector<vector<int>>& grid) {
        if (!grid.size()) return 0;
        vector<int> vx, vy;
        int nrow = grid.size(), ncol = grid[0].size();
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (grid[i][j])
                    vx.push_back(i);
        for (int j = 0; j < ncol; j++)
            for (int i = 0; i < nrow; i++)
                if (grid[i][j])
                    vy.push_back(j);
        // auto dis = [](vector<int> & v, int origin) {
        //     transform(v.begin(), v.end(), v.begin(), [&](int i) {return abs(i - origin);});
        //     return accumulate(v.begin(), v.end(), 0);
        // };
        return dis(vx, vx[(vx.size() - 1) / 2]) + dis(vy, vy[(vy.size() - 1) / 2]);
    }
};
```