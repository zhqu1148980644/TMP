---
title: Random Point in Non overlapping Rectangles
date: 2021-01-04
---
Given a list of non-overlapping axis-aligned rectangles rects, write a function pick which randomly and uniformily picks an integer point in the space covered by the rectangles.

Note:

An integer point is a point that has integer coordinates. 
A point on the perimeter of a rectangle is included in the space covered by the rectangles. 
ith rectangle = rects[i] = [x1,y1,x2,y2], where [x1, y1] are the integer coordinates of the bottom-left corner, and [x2, y2] are the integer coordinates of the top-right corner.
length and width of each rectangle does not exceed 2000.
1 <= rects.length <= 100
pick return a point as an array of integer coordinates [p_x, p_y]
pick is called at most 10000 times.
Example 1:

Input: 
["Solution","pick","pick","pick"]
[[[[1,1,5,5]]],[],[],[]]
Output: 
[null,[4,1],[4,1],[3,3]]
Example 2:

Input: 
["Solution","pick","pick","pick","pick","pick"]
[[[[-2,-2,-1,-1],[1,0,3,0]]],[],[],[],[],[]]
Output: 
[null,[-1,-2],[2,0],[-2,-1],[3,0],[-2,-2]]
Explanation of Input Syntax:

The input is two lists: the subroutines called and their arguments. Solution's constructor has one argument, the array of rectangles rects. pick has no arguments. Arguments are always wrapped with a list, even if there aren't any.


#### Solutions

1. ##### straight forward

- Borrowed from the official answer

```cpp
class Solution {
public:
    vector<vector<int>> rects;
    vector<int> psum;
    mt19937 gen{random_device{}()};
    uniform_int_distribution<int> uni;
    Solution(vector<vector<int>>& rects) : rects(rects) {
        int totalarea = 0;
        for (auto & v : rects) {
            totalarea += (v[2] - v[0] + 1) * (v[3] - v[1] + 1);
            psum.push_back(totalarea);
        }
        uni = uniform_int_distribution<int>(0, totalarea - 1);
    }
    
    vector<int> pick() {
        int rsum = uni(gen);
        // upper bound
        int lo = 0, hi = psum.size();
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            if (rsum >= psum[mid])
                lo = mid + 1;
            else
                hi = mid;
        }
        auto & rect = rects[lo];
        int x0 = rect[0], y0 = rect[1];
        int height = rect[3] - rect[1] + 1;
        int base = lo > 0 ? psum[lo - 1] : 0;
        return {x0 + (rsum - base) / height, y0 + (rsum - base) % height};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */
```