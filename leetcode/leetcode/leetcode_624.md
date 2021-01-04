---
title: Maximum Distance in Arrays
date: 2021-01-04
---
Given m arrays, and each array is sorted in ascending order. Now you can pick up two integers from two different arrays (each array picks one) and calculate the distance. We define the distance between two integers a and b to be their absolute difference |a-b|. Your task is to find the maximum distance.

Example 1:
Input: 
[[1,2,3],
 [4,5],
 [1,2,3]]
Output: 4
Explanation: 
One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.
Note:
Each given array will have at least 1 number. There will be at least two non-empty arrays.
The total number of the integers in all the m arrays will be in the range of [2, 10000].
The integers in the m arrays will be in the range of [-10000, 10000].

#### Solutions

1. ##### straight forward

- For each array, find the difference between the cuurent `array.back()(largest)` and the lowest `front()` among `other arrays`.

```cpp
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int minv = arrays[0].front(), maxv = arrays[0].back();
        int res = INT_MIN;
        for (int i = 1; i < arrays.size(); i++) {
            auto & v = arrays[i];
            res = max(res, max(abs(maxv - v.front()), abs(v.back() - minv)));
            minv = min(minv, v.front());
            maxv = max(maxv, v.back());
        }

        return res;
    }
};
```

or find out the smallest and the second smallest value.

```cpp
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int min1st, min2nd;
        min1st = min2nd = INT_MAX;
        int mini = -1;
        for (int i = 0; i < arrays.size(); i++) {
            if (arrays[i].front() < min1st) {
                if (mini != -1)
                    min2nd = min1st;
                min1st = arrays[i].front();
                mini = i;
            }
            else if (arrays[i].front() < min2nd)
                min2nd = arrays[i].front();
        }

        int res = INT_MIN;
        for (int i = 0; i < arrays.size(); i++)
            res = max(res, arrays[i].back() - (mini != i ? min1st : min2nd));
        
        return res;
    }
};
```