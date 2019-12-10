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

- collect intervals whose end is smaller than inserted interval' start.
- collect intervals whose start is larger than inserted interval's end.
- Choose the smallest between inserted intervals's start and the first overlapped interval's start as the start.
- The same for choosing the end as the end.
- Finally build a new interval with the start and end.
- Concatenate.

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