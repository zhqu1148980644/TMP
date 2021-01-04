---
title: Insert Interval
date: 2021-01-04
---
### Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

```
Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
```

### NOTE: 
input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.


### Solutions

1. #### straight forward

- Collect intervals don't overlap with the newInterval.
    - collect intervals whose end is smaller than inserted interval' start.
    - collect intervals whose start is larger than inserted interval's end.
- Merge overlapping intervals by finding the minimum start and the maximum end among them.
    - Choose the smallest between inserted intervals's start and the first overlapped interval's start as the start.
    - The same for choosing the end as the end.
    - Finally build a new interval with the start and end.
- Concatenate these three parts.

```cpp
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<int> left, merged, right;
        for (int i = 0; i < intervals.size(); i++) {
            if (intervals[i][1] < newInterval[0])
                left.push_back(i);
            else if (intervals[i][0] > newInterval[1])
                right.push_back(i);
            else
                merged.push_back(i);
        }

        vector<vector<int>> res;
        for (int i : left)
            res.push_back(intervals[i]);
        int st = newInterval[0], ed = newInterval[1];
        if (merged.size()) {
            st = min(intervals[merged.front()][0], st);
            ed = max(intervals[merged.back()][1], ed);
        }
        res.push_back({st, ed});
        for (int i : right)
            res.push_back(intervals[i]);
        
        return res;
    }
};
```

```python
class Solution(object):
    def insert(self, intervals, newInterval):
        """
        :type intervals: List[List[int]]
        :type newInterval: List[int]
        :rtype: List[List[int]]
        """
        alls = merged, left, right = [], [], []
        s, e = newInterval
        for i in intervals:
            alls[(i[1] < s) - (i[0] > e)].append(i)
        if merged:
            s = min(merged[0][0], s)
            e = max(merged[-1][1], e)
        return left + [[s, e]] + right
```