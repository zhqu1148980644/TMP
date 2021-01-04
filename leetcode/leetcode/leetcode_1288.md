---
title: Remove Covered Intervals
date: 2021-01-04
---
#### Given a list of intervals, remove all intervals that are covered by another interval in the list. Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.

After doing so, return the number of remaining intervals.

```
Example 1:

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
```
 

#### Constraints:

- 1 <= intervals.length <= 1000
- 0 <= intervals[i][0] < intervals[i][1] <= 10^5
- intervals[i] != intervals[j] for all i != j


#### Solutions

1. ##### two pointer

- sorting by starting points, when the current interval's end <= former interval's end, then the current interval is beging covered. For cases when two intervals have the same start point, make sure the longer one is positioned before.

```
normal cases
--------
  ----

special cases

------ need to be visited before
---
```

```cpp
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>> & intervals) {
        if (intervals.size() <= 1) return intervals.size();
        sort(intervals.begin(), intervals.end(), [&](auto & v1, auto & v2) {
            return v1[0] == v2[0] ? v1[1] > v2[1] : v1[0] < v2[0];
        });
        int i = 0, j = 1, count = intervals.size();
        while (j < intervals.size()) {
            if (intervals[i][1] >= intervals[j][1])
                count--;
            else
                i = j;
            j++;
        }
        return count;
    }
};
```